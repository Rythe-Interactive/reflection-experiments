#pragma once
#include <rsl/containers>

#include "comp_reflected_element.h"

class comp_reflected_variable : public comp_reflected_element {
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    comp_reflected_variable(rsl::dynamic_string const &usr_id);
    ~comp_reflected_variable();
};
