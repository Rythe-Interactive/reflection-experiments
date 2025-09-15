#pragma once
#include "../reflection_containers/reflected_variable.h"
#include <sstream>
#include <rsl/containers>

class reflection_code_generator {
public:
    rsl::dynamic_string generate_variable(rythe::reflection_containers::reflected_variable parsed_variable, int indent);
};
