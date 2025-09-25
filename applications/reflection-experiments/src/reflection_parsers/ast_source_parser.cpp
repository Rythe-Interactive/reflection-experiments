#include "ast_source_parser.h"



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

CXChildVisitResult reflection_parsers::ast_source_parser::visitor_from_file(
    CXCursor     current_cursor,
    CXCursor     parent_cursor,
    CXClientData client_data)
{
    auto* parent_file = static_cast<compile_reflected_file*>(client_data);

    CXCursorKind kind = clang_getCursorKind(current_cursor);
    std::cout << kind << '\n';
    switch(kind)
    {
        case CXCursor_ClassDecl:
            compile_reflected_class& reflected_class = parent_file->add_class_from_cursor(current_cursor);
            clang_visitChildren(current_cursor, visitor_from_class, &reflected_class);
            break;
        case CXCursor_FieldDecl:
            compile_reflected_variable& reflected_variable = parent_file->add_variable_from_cursor(current_cursor);
            break;
        case CXCursor_FunctionDecl:
            std::cout << "Indeed a function" << '\n';
            break;
        default:
            break;
    }
    return CXChildVisit_Continue;
}

CXChildVisitResult reflection_parsers::ast_source_parser::visitor_from_class(
    CXCursor     current_cursor,
    CXCursor     parent_cursor,
    CXClientData client_data)
{
    auto*        parent_class = static_cast<compile_reflected_class*>(client_data);
    CXCursorKind kind = clang_getCursorKind(current_cursor);

    std::cout << kind << std::endl;

    switch(kind)
    {
        case CXCursor_ClassDecl:
            compile_reflected_class& reflected_class = parent_class->add_class_from_cursor(current_cursor);
            clang_visitChildren(current_cursor, visitor_from_class, &reflected_class);
            break;
        case CXCursor_FieldDecl:
            compile_reflected_variable& variable = parent_class->add_variable_from_cursor(current_cursor);
            break;
        case CXCursor_FunctionDecl:
            std::cout << "Indeed a function" << '\n';
            break;

        default:
            break;
    }
    return CXChildVisit_Continue;
}


void reflection_parsers::ast_source_parser::ast_parse_file(const rsl::dynamic_string filePath, CXIndex index)
{
    CXTranslationUnit unit = clang_parseTranslationUnit(
        index,
        filePath.data(),
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

    auto reflected_file = std::make_unique<compile_reflected_file>(filePath);
    all_files.emplace(filePath, std::move(reflected_file));

    clang_visitChildren(cursor, visitor_from_file, &context);
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
