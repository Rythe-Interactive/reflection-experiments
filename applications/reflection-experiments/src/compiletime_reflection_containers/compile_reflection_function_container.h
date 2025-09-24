#pragma once
#include <vector>

#include "compile_reflection_function.h"

class compile_reflected_function_container
{
public:
    void add_variable(compile_reflection_function function);

    compile_reflected_function_container();
    ~compile_reflected_function_container();
    compile_reflected_function_container(const compile_reflected_function_container& other);
    compile_reflected_function_container(compile_reflected_function_container&& other);
protected:
    std::vector<compile_reflection_function> functions;
};
