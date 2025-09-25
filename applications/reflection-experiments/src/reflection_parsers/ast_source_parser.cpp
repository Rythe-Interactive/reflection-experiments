#include "ast_source_parser.h"

#include "../runtime_reflection_containers/reflected_function.h"
#include "../runtime_reflection_containers/reflected_variable.h"

reflection_parsers::ast_source_parser::ast_source_parser()
{
    index = clang_createIndex(0, 0);

    code_generator = reflection_code_generator();
}

reflection_parsers::ast_source_parser::~ast_source_parser() {}

void reflection_parsers::ast_source_parser::parse_source_folders(const std::unordered_set<std::string>& folders)
{
    index = clang_createIndex(0, 0);

    for(auto folder : folders)
    {
        for(const auto& entry : std::filesystem::recursive_directory_iterator(folder))
        {
            if(!entry.is_regular_file()) { continue; }
            std::filesystem::path path = entry.path();
            if(path.extension() == ".hpp" || path.extension() == ".h")
            {
                ast_parse_file(rsl::dynamic_string::from_string_length(path.string().c_str()), index);
            }
        }
    }
}

CXChildVisitResult reflection_parsers::ast_source_parser::visitor_callback_wrapper(
    CXCursor     cursor,
    CXCursor     parent,
    CXClientData client_data)
{
    auto self = static_cast<reflection_parsers::ast_source_parser*>(client_data);
    return self->visitor(cursor, parent, client_data);
}

CXChildVisitResult reflection_parsers::ast_source_parser::visitor(
    CXCursor     current_cursor,
    CXCursor     parent,
    CXClientData client_data)
{
    auto* data = static_cast<visitor_context*>(client_data);

    CXString    current_display_name = clang_getCursorDisplayName(current_cursor);
    const char* char_display_name = clang_getCString(current_display_name);
    if(char_display_name && char_display_name[0] != '\0')
    {
        for(auto i = 0; i < data->depth; i++) { std::cout << "  "; }
        std::cout << "Visiting element: " << char_display_name << "\n";

        CXSourceLocation location = clang_getCursorLocation(current_cursor);
        CXFile           file;
        unsigned int     line, column, offset;

        clang_getSpellingLocation(location, &file, &line, &column, &offset);

        CXString    file_name = clang_getFileName(file);
        const char* file_name_spelling = clang_getCString(file_name);

        rsl::dynamic_string file_name_string = rsl::dynamic_string::from_string_length(file_name_spelling);
        auto                it = all_files.find(file_name_string);

        if(it == all_files.end())
        {
            all_files[file_name_string] = std::make_unique<compile_reflected_file>(file_name_string);
        }

        if(clang_getCursorKind(parent) == CXCursor_FunctionDecl) {}

        if(CXCursor_FieldDecl == clang_getCursorKind(current_cursor))
        {
            compile_reflected_variable reflected_variable = extract_compile_variable(current_cursor);

            CXCursor    parent_cursor = clang_getCursorSemanticParent(current_cursor);
            CXString    parent_usr = clang_getCursorUSR(parent_cursor);
            const char* parent_usr_spelling = clang_getCString(parent_usr);

            all_files[file_name_string]->add_variable_to_file(
                rsl::dynamic_string::from_string_length(parent_usr_spelling),
                reflected_variable);

            //code_generator.generate_reflected_variable_file(reflected_variable, "reflected_variable.generated");
            std::cout << "indeed true" << std::endl;

            clang_disposeString(parent_usr);
        }

        clang_disposeString(current_display_name);
        visitor_context child{.self = data->self, .depth = data->depth + 1};

        clang_visitChildren(current_cursor, visitor_callback_wrapper, &child);
    }
    return CXChildVisit_Continue;
}

void reflection_parsers::ast_source_parser::ast_parse_file(const rsl::dynamic_string filePath, CXIndex index)
{
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        filePath.c_str(),
        nullptr,
        0,
        nullptr,
        0,
        CXTranslationUnit_None);

    if(unit == nullptr)
    {
        std::cerr << "Unable to parse translation unit. Quitting.\n";
        return;
    }
    CXCursor cursor = clang_getTranslationUnitCursor(unit); //Obtain a cursor at the root of the translation unit

    visitor_context context = {.self = this, .depth = 0};

    auto  reflected_file = std::make_unique<compile_reflected_file>(filePath);
    auto& file_ref = *reflected_file;

    all_files.emplace(filePath, std::move(reflected_file));

    clang_visitChildren(cursor, visitor_callback_wrapper, &context);
}

void reflection_parsers::ast_source_parser::ast_parse_cursor_from_class(
    CXCursor                 cursor,
    compile_reflected_class& reflected_class)
{
    CXCursorKind kind = clang_getCursorKind(cursor);
    std::cout << kind << std::endl;
    switch(kind)
    {
        case CXCursor_ClassDecl:
            //ast_parse_cursor_from_class(cursor, reflected_class);
            break;
        case CXCursor_FieldDecl:
            compile_reflected_variable& variable = reflected_class.add_variable_from_cursor(cursor);
            break;
        case CXCursor_FunctionDecl:
            break;

        default:
            break;
    }
}

rythe::reflection_containers::reflected_variable reflection_parsers::ast_source_parser::extract_variable(
    CXCursor cursor)
{
    CXString field_name = clang_getCursorSpelling(cursor);

    CXCursor parent = clang_getCursorSemanticParent(cursor);
    CXString parent_name = clang_getCursorSpelling(parent);

    reflection_properties::acess_modifier access = {};
    switch(clang_getCXXAccessSpecifier(cursor))
    {
        case CX_CXXPublic:
            access = reflection_properties::acess_modifier::public_access;
            break;
        case CX_CXXProtected:
            access = reflection_properties::acess_modifier::protected_access;
            break;
        case CX_CXXPrivate:
            access = reflection_properties::acess_modifier::private_access;
            break;
        case CX_CXXInvalidAccessSpecifier:
            // Debug something bad
            break;
        default:
            break;
    }

    CXType type = clang_getCursorType(cursor);

    bool is_const = clang_isConstQualifiedType(type);

    // Not sure how to do that yet
    auto is_static = true;

    auto is_array = false;
    auto array_size = 0;

    if(type.kind == CXType_ConstantArray)
    {
        is_array = true;
        array_size = static_cast<int>(clang_getArraySize(type));
    }

    size_t size = clang_Type_getSizeOf(type);
    size_t align = clang_Type_getAlignOf(type);

    auto offset = (int)clang_Cursor_getOffsetOfField(cursor);

    rsl::dynamic_array<rsl::dynamic_string> attributes = {};

    const char* field_cstr = clang_getCString(field_name);
    const char* parent_cstr = clang_getCString(parent_name);

    CXType      cursor_type = clang_getCursorType(cursor);
    CXString    type_spelling = clang_getTypeSpelling(cursor_type);
    const char* type_cstr = clang_getCString(type_spelling);

    clang_disposeString(type_spelling);
    clang_disposeString(field_name);
    clang_disposeString(parent_name);

    return rythe::reflection_containers::reflected_variable(
        rsl::hashed_string::from_string_length(field_cstr),
        rsl::dynamic_string::from_string_length(parent_cstr),
        access,
        is_static,
        is_const,
        is_array,
        array_size,
        offset,
        size,
        align,
        reflection_id(rsl::dynamic_string::from_string_length(type_cstr)),
        attributes);
}
