#include "compile_reflected_variable_container.h"

compile_reflected_variable_container::compile_reflected_variable_container() {}

compile_reflected_variable_container::~compile_reflected_variable_container() {}

void compile_reflected_variable_container::add_variable(CXCursor cursor)
{
    const auto variable = compile_reflected_variable(cursor);
    variables.push_back(variable);
}