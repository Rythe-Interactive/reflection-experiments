#include "comp_reflected_variable_container.h"

#include "clang-c/Index.h"

comp_reflected_variable_container::comp_reflected_variable_container() {
    variables = {};
}

comp_reflected_variable_container::~comp_reflected_variable_container() {
    
}

void comp_reflected_variable_container::addVariable(comp_reflected_variable variable) {
    variables.push_back(variable);
}

