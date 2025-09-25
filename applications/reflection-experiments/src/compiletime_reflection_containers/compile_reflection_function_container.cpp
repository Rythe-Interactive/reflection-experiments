#include "compile_reflection_function_container.h"

compile_reflection_function& compile_reflected_function_container::add_function_from_cursor(CXCursor cursor)
{
    functions.emplace_back(cursor);
    return functions.back();
}

compile_reflected_function_container::compile_reflected_function_container() {}

compile_reflected_function_container::~compile_reflected_function_container() {}

compile_reflected_function_container::compile_reflected_function_container(
    const compile_reflected_function_container& other) {}

compile_reflected_function_container::compile_reflected_function_container(
    compile_reflected_function_container&& other) {}
