#include "AST_source_parser.h"

AST_source_parser::AST_source_parser() {
    index = clang_createIndex(0, 0);
}

AST_source_parser::~AST_source_parser() {
    
}

void AST_source_parser::parse_source_folders(const std::unordered_set<std::string> &folders) {
    index = clang_createIndex(0, 0);

    for (auto folder : folders) {
        
        rsl::dynamic_string string = rsl::dynamic_string::from_buffer(folder.c_str(), folder.size());
        
        for (const auto& entry : std::filesystem::recursive_directory_iterator(string.data())) {
            if (!entry.is_regular_file()) continue;
            
            std::filesystem::path path = entry.path();
            if (path.extension() == ".hpp" || path.extension() == ".h") {
                AST_parse_file(path.string().c_str(), index);
                }
        }
    }
}

void AST_source_parser::AST_parse_file(const std::string filePath, CXIndex index) {
    
    CXTranslationUnit unit = clang_parseTranslationUnit(
          index,
          filePath.c_str(), nullptr, 0,
          nullptr, 0,
          CXTranslationUnit_None); 
    
    if (unit == nullptr){
        std::cerr << "Unable to parse translation unit. Quitting.\n";
        return;
    }
    CXCursor cursor = clang_getTranslationUnitCursor(unit); //Obtain a cursor at the root of the translation unit

    visitor_context context = {.self = this, .depth = 0};
    
    clang_visitChildren(
      cursor, //Root cursor
      visitor_callback_wrapper, //CXCursorVisitor: a function pointer
      &context //client_data
      );
}

CXChildVisitResult AST_source_parser::visitor(
    CXCursor current_cursor,
    CXCursor parent,
    CXClientData client_data) {

    auto* data = static_cast<visitor_context*>(client_data);

    CXString current_display_name = clang_getCursorDisplayName(current_cursor);
    const char* char_display_name = clang_getCString(current_display_name);
    if (strcmp(char_display_name, "")) {
        for (int i = 0; i < data->depth; i++) std::cout << "  ";
        std::cout << "Visiting element: " << char_display_name << "\n";

        if (parent.kind == CXCursor_FunctionDecl) {}
    
        clang_disposeString(current_display_name);
        visitor_context child{.self = data->self, .depth = data->depth + 1 };
        
        clang_visitChildren(
            current_cursor,
            visitor_callback_wrapper,
            &child);
    }
    return CXChildVisit_Continue;
}

CXChildVisitResult AST_source_parser::visitor_callback_wrapper(
    CXCursor cursor,
    CXCursor parent,
    CXClientData client_data) {
    
    auto self = static_cast<AST_source_parser*>(client_data);
    return self->visitor(cursor, parent, client_data);
}



