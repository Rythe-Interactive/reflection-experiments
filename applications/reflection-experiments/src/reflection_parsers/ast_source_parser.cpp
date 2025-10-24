#include "ast_source_parser.h"

reflection_parsers::ast_source_parser::ast_source_parser()
{
    index = clang_createIndex(0, 0);

    code_generator = reflection_code_generator();
}

reflection_parsers::ast_source_parser::~ast_source_parser() {}

void reflection_parsers::ast_source_parser::parse_source_folders(const std::unordered_set<std::string>& folders)
{
    //std::cout << "reflection_parsers::ast_source_parser::parse_source_folders" << std::endl;
    index = clang_createIndex(0, 0);

    for(auto& folder : folders)
    {
        for(const auto& entry : std::filesystem::recursive_directory_iterator(folder))
        {
            if(!entry.is_regular_file()) { continue; }
            std::filesystem::path path = entry.path();
            if(path.extension() == ".hpp" || path.extension() == ".h")
            {
                ast_parse_file(path.string(), index);
            }
        }
    }
    print_all_files();
}

void reflection_parsers::ast_source_parser::print_all_files() const
{
    for(const auto& element : all_files) { element.second.print(0); }
}

CXChildVisitResult reflection_parsers::ast_source_parser::visitor_from_file(
    CXCursor     current_cursor,
    CXCursor     parent_cursor,
    CXClientData client_data)
{
    if(parent_cursor.kind) {}

    auto*        parent_file = static_cast<compile_reflected_file*>(client_data);
    CXCursorKind kind = clang_getCursorKind(current_cursor);

    /*
    CXString kind_spelling = clang_getCursorKindSpelling(kind);
    std::cout << clang_getCString(kind_spelling) << '\n';

    clang_disposeString(kind_spelling);
    */

    switch(kind)
    {
        case CXCursor_ClassDecl:
        {
            compile_reflected_class& reflected_class = parent_file->compile_reflection_container<
                compile_reflected_class>::add_element(current_cursor, parent_cursor);
            clang_visitChildren(current_cursor, visitor_from_class, &reflected_class);
            reflected_class.set_full_hash();
            break;
        }
        case CXCursor_FieldDecl:
        {
            compile_reflected_variable& variable = parent_file->compile_reflection_container<
                compile_reflected_variable>::add_element(current_cursor, parent_cursor);
            variable.set_full_hash();
            break;
        }
        case CXCursor_FunctionDecl:
        {
            /*compile_reflected_function& function = parent_file->compile_reflection_container<
                compile_reflected_function>::add_element(current_cursor, parent_cursor);
            function.set_full_hash();*/
            break;
        }
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
    if(parent_cursor.kind) {}

    auto*        parent_class = static_cast<compile_reflected_class*>(client_data);
    CXCursorKind kind = clang_getCursorKind(current_cursor);
    
    switch(kind)
    {
        case CXCursor_ClassDecl:
        {
            compile_reflected_class& reflected_class = parent_class->add_class(current_cursor, parent_cursor);
            clang_visitChildren(current_cursor, visitor_from_class, &reflected_class);
            reflected_class.set_full_hash();
            break;
        }
        case CXCursor_FieldDecl:
        {
            compile_reflected_variable& variable = parent_class->compile_reflection_container<
                compile_reflected_variable>::add_element(
                current_cursor,
                parent_cursor);
            variable.set_full_hash();
            break;
        }
        case CXCursor_FunctionDecl:
        {
            std::cout << "Indeed a function" << '\n';
            break;
        }
        default:
            break;
    }
    return CXChildVisit_Continue;
}

// Meant to pass temporary 
void reflection_parsers::ast_source_parser::ast_parse_file(const std::string&& filePath, CXIndex index)
{
    std::cout << "Parsing file path: " << filePath << '\n';
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

    auto [iterator, inserted] = all_files.emplace(
        filePath,
        compile_reflected_file(
            rsl::dynamic_string::from_string_length(extract_file_name(std::string_view(filePath)).data()),
            rsl::dynamic_string::from_string_length(filePath.c_str())));

    clang_visitChildren(cursor, visitor_from_file, &iterator->second);
}

std::string_view reflection_parsers::ast_source_parser::extract_file_name(const std::string_view file_path)
{
    size_t           last_slash_position = file_path.rfind('\\');
    std::string_view file_name;
    if(last_slash_position != std::string::npos)
    {
        file_name = file_path.substr(last_slash_position + 1, file_path.size() - last_slash_position);
    }
    else { std::cerr << "File name is empty.\n"; }
    return file_name;
}
