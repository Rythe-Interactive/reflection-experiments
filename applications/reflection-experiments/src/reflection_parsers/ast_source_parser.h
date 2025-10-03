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
        ast_source_parser();
        ~ast_source_parser();

        void parse_source_folders(const std::unordered_set<std::string>& folders);

        void print_all_files() const;
    private:
        reflection_code_generator code_generator;
        CXIndex                   index;

        // I'd recommend either sticking to rsl containers or std containers, I've not made my containers with STL compatibility in mind.
        // Furthermore, why do these files need to be a unique_ptr?
        std::map<std::string, compile_reflected_file> all_files;

        // If this function is a static function that is never needed outside ast_source_parser.cpp, then it would be best to keep
        // it as a translation unit local function. You do this by moving this function into ast_source_parser.cpp and either marking
        // it static, or by placing it into an anonymous namespace:
        // https://en.cppreference.com/w/cpp/language/storage_duration.html#Internal_linkage
        static CXChildVisitResult visitor_from_file(
            CXCursor     current_cursor,
            CXCursor     parent_cursor,
            CXClientData client_data);
        static CXChildVisitResult visitor_from_class(
            CXCursor     current_cursor,
            CXCursor     parent_cursor,
            CXClientData client_data);

        // You don't want to copy strings, either use a string_view if you need temporary read access or are going to copy,
        // or use a string rvalue reference (rsl::dynamic_string&&) if you want to take ownership.
        // Generally you'd want the ownership to not transfer and thus create the copy inside the function instead.
        // However, you can use rsl::dynamic_string&& in order to force the calling code to create a temporary string object.
        // The reason you'd do that is in order to make the caller aware of the allocation that will happen inside the function because
        // you expect the function to be called in a place where allocations are not in the budget.
        void ast_parse_file(const std::string&& filePath, CXIndex index);

        static std::string_view extract_file_name(const std::string_view filePath);
        
        rythe::reflection_containers::reflected_variable extract_variable(CXCursor cursor);
    };
}
