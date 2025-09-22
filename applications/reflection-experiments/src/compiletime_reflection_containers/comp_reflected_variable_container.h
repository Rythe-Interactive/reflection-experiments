#pragma once
#include "../compiletime_reflection_containers/comp_reflected_variable.h"

class comp_reflected_variable_container {
public:
    void addVariable(comp_reflected_variable);

    comp_reflected_variable_container();
    ~comp_reflected_variable_container();
    
protected:  
    std::vector<comp_reflected_variable> variables;
};
