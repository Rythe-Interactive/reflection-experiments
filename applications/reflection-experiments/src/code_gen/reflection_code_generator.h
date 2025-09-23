#pragma once
#include "../runtime_reflection_containers/reflected_variable.h"
#include <sstream>
#include <rsl/containers>

class reflection_code_generator {
public:
    rsl::dynamic_string generate_variable(rythe::reflection_containers::reflected_variable parsed_variable);

    reflection_code_generator();
    ~reflection_code_generator();

    void generate_reflected_variable_file(const rythe::reflection_containers::reflected_variable& parsed_variable, const std::string& outFile);
};
