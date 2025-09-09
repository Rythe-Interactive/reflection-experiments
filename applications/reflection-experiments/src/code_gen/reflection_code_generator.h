#pragma once
#include "../reflection_containers/reflected_variable.h"

class reflection_code_generator {
public:
    void generate_variable(rythe::reflection_containers::reflected_variable parsed_variable);
};
