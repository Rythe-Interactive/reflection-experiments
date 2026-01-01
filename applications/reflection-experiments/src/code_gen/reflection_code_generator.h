#pragma once
#include "../runtime_reflection_containers/runtime_reflected_variable.h"
#include <sstream>
#include <rsl/containers>
#include "../compiletime_reflection_containers/compile_reflected_file.h"

class reflection_code_generator
{
public:
    const rsl::dynamic_string generate_variable(runtime_reflected_variable parsed_variable);

    reflection_code_generator();
    ~reflection_code_generator();

    void generate_reflected_variable(
        std::ofstream&                    file,
        const compile_reflected_variable& variable,
        const std::string&                parent_name);

    void generate_reflected_function(
        std::ofstream&                    file,
        const compile_reflected_function& variable,
        const std::string&                parent_name);

    void generate_reflected_class(
        std::ofstream&                 file,
        const compile_reflected_class& variable,
        const std::string&             parent_name);

    std::string generate_reflection_id(reflection_id id, const std::string& owner) const;

    void generate_reflected_file(const compile_reflected_file& file);
    static rsl::dynamic_string get_gen_source_file(rsl::string_view source_location);
};
