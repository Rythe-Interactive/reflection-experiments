#include <clang-c/Index.h>
#include <direct.h> 
#include <iostream>
#include <filesystem>
#include "rsl/containers"
#include "spdlog/fmt/bundled/base.h"

struct depth_data {
    int depth;
};

CXChildVisitResult visitor(CXCursor current_cursor, CXCursor parent, CXClientData client_data) {
    auto* data = static_cast<depth_data*>(client_data);

    CXString current_display_name = clang_getCursorDisplayName(current_cursor);
    const char* char_display_name = clang_getCString(current_display_name);
    if (strcmp(char_display_name, "")) {
        for (int i = 0; i < data->depth; i++) std::cout << "  ";
        std::cout << "Visiting element: " << char_display_name << "\n";

        if (parent.kind == CXCursor_FunctionDecl) {}
    
        clang_disposeString(current_display_name);
        depth_data child{ data->depth + 1 };
        clang_visitChildren(current_cursor, visitor, &child);
    }
    return CXChildVisit_Continue;
}

void parseFileAST(const std::string filePath, CXIndex index) {
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

    depth_data depth_data_var{0};
    
    clang_visitChildren(
      cursor, //Root cursor
      visitor, //CXCursorVisitor: a function pointer
      &depth_data_var //client_data
      );
}


int main() {
    CXIndex index = clang_createIndex(0, 0); //Create index

    rsl::dynamic_string string;
    string = "../../applications/reflection-experiments/src";
    
    for (const auto& entry : std::filesystem::recursive_directory_iterator(string.data())) {
        if (!entry.is_regular_file()) continue;
        
        std::filesystem::path path = entry.path();
        if (path.extension() == ".cpp" || path.extension() == ".hpp" ||
            path.extension() == ".h"   || path.extension() == ".c") {
            parseFileAST(path.string().c_str(), index);
        }
    }
    
    return 0;
}
