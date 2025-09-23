#pragma once
#include "comp_reflected_variable_container.h"
#include "../runtime_reflection_containers/reflected_function.h"
#include "rsl/impl/containers/string.hpp"

class comp_reflected_element {
public:
    comp_reflected_element(const rsl::dynamic_string usr_id);
    virtual ~comp_reflected_element();

    rsl::dynamic_string get_usr_id() const;

    virtual comp_reflected_variable_container* asVariableContainer() {return nullptr;}
protected:
    const rsl::dynamic_string usr_id;
};
