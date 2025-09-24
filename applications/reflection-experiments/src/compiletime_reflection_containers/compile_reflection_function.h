#pragma once
#include "rsl/impl/containers/string.hpp"

class compile_reflection_function
{
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    compile_reflection_function();
    ~compile_reflection_function();
};
