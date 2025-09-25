#pragma once
#include <map>

#include "compile_reflected_class.h"
#include "compile_reflected_variable_container.h"
#include "compile_reflection_function_container.h"
#include "clang-c/Index.h"

struct compile_reflected_file
    : public compile_reflected_variable_container,
      public compile_reflected_function_container,
      public compile_reflected_class_container
{
public:
    rsl::dynamic_string name;

    compile_reflected_file(const rsl::dynamic_string source_location);
    compile_reflected_file(const compile_reflected_file& other) = default;
    compile_reflected_file(compile_reflected_file&& other) noexcept = default;
    ~compile_reflected_file();
private:
    rsl::dynamic_string source_location;
};
