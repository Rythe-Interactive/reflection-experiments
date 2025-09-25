#include "compile_reflected_variable_container.h"

compile_reflected_variable_container::compile_reflected_variable_container() {}

compile_reflected_variable_container::~compile_reflected_variable_container() {}

compile_reflected_variable& compile_reflected_variable_container::add_variable_from_cursor(CXCursor cursor)
{
    variables.emplace_back(cursor);
    return variables.back();
}
