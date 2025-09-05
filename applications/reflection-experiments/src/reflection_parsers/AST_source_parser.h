#pragma once
#include <clang-c/Index.h>
#include <iostream>
#include <filesystem>
#include <unordered_set>

#include "rsl/containers"

class AST_source_parser {
public:

    struct visitor_context {
        AST_source_parser* self;
        int depth;
    };
    
    AST_source_parser();
    ~AST_source_parser();

    void parse_source_folders(const std::unordered_set<std::string>& folders);
    
    static CXChildVisitResult visitor_callback_wrapper(
        CXCursor cursor,
        CXCursor parent,
        CXClientData client_data);
    
private:

    CXIndex index;
    
    CXChildVisitResult visitor(
        CXCursor current_cursor,
        CXCursor parent,
        CXClientData client_data);
    
    void AST_parse_file(const std::string filePath, CXIndex index);
};
