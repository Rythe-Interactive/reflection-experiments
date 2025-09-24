#include "compile_reflection_function_container.h"

#include <functional>

void compile_reflected_function_container::add_variable(compile_reflection_function variable) { functions.push_back(variable); }

compile_reflected_function_container::compile_reflected_function_container() {}

compile_reflected_function_container::~compile_reflected_function_container() {}

compile_reflection_function::compile_reflection_function() {}

compile_reflection_function::~compile_reflection_function() {}

