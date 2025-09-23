#pragma once
#include <clang-c/Index.h>
#include <iostream>
#include <filesystem>
#include <map>
#include <unordered_set>
#include "../code_gen/reflection_code_generator.h"
#include "../runtime_reflection_containers/reflected_variable.h"
#include  "../compiletime_reflection_containers/comp_reflected_file.h"
#include "../reflection_properties/access_modifier.h"
#include "../code_gen/reflection_code_generator.h"

#include "rsl/containers"

namespace reflection_parsers {
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

        reflection_code_generator code_generator;
        CXIndex index;

        std::map<rsl::dynamic_string, std::unique_ptr<comp_reflected_file>> all_files;
        
        CXChildVisitResult visitor(
            CXCursor current_cursor,
            CXCursor parent,
            CXClientData client_data);
        
        void AST_parse_file(const std::string filePath, CXIndex index);

        rythe::reflection_containers::reflected_variable extract_variable(CXCursor cursor);
        comp_reflected_variable extract_compile_variable(CXCursor cursor);
    };
}