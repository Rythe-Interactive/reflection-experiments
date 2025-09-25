#pragma once
#include <clang-c/Index.h>
#include <filesystem>
#include <map>
#include <unordered_set>
#include "../code_gen/reflection_code_generator.h"
#include "../runtime_reflection_containers/reflected_variable.h"
#include  "../compiletime_reflection_containers/compile_reflected_file.h"
#include  "../compiletime_reflection_containers/compile_reflected_class.h"

#include "rsl/containers"

namespace reflection_parsers
{
    class ast_source_parser
    {
    public:
        struct visitor_context
        {
            ast_source_parser* self;
            int                depth;
        };

        ast_source_parser();
        ~ast_source_parser();

        void parse_source_folders(const std::unordered_set<std::string>& folders);
    
    private:
        reflection_code_generator code_generator;
        CXIndex                   index;

        std::map<rsl::dynamic_string, std::unique_ptr<compile_reflected_file>> all_files;

        static CXChildVisitResult visitor_from_file(
            CXCursor     current_cursor,
            CXCursor     parent_cursor,
            CXClientData client_data);
        static CXChildVisitResult visitor_from_class(
            CXCursor     current_cursor,
            CXCursor     parent_cursor,
            CXClientData client_data);
        
        void ast_parse_file(const rsl::dynamic_string filePath, CXIndex index);

        rythe::reflection_containers::reflected_variable extract_variable(CXCursor cursor);
    };
}
