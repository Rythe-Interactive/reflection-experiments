#pragma once
#include "compile_reflected_container.h"
#include "compile_reflected_variable_container.h"
#include "compile_reflection_function_container.h"

#include <rsl/string>

struct compile_reflected_class
    : public compile_reflected_container<compile_reflected_class>,
      public compile_reflected_container<compile_reflected_variable>,
      public compile_reflected_container<compile_reflection_function>
{
public:
    rsl::dynamic_string name;
    rsl::dynamic_string type;

    compile_reflected_class(CXCursor cursor);
    compile_reflected_class(const compile_reflected_class&) = default;
    compile_reflected_class(compile_reflected_class&&) noexcept = default;
    ~compile_reflected_class();
};
