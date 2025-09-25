#pragma once
#include "compile_reflected_class_container.h"
#include "compile_reflected_variable_container.h"
#include "compile_reflection_function_container.h"

#include <rsl/string>

class compile_reflected_class
    : public compile_reflected_class_container,
      public compile_reflected_function_container,
      public compile_reflected_variable_container
{
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    compile_reflected_class();
    compile_reflected_class(const compile_reflected_class&);
    compile_reflected_class(compile_reflected_class&&);
    ~compile_reflected_class();
};
