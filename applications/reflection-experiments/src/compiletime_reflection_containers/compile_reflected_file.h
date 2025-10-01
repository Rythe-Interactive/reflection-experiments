#pragma once
#include <map>

#include "compile_reflected_class.h"
#include "compile_reflected_variable.h"
#include "compile_reflection_function.h"
#include "clang-c/Index.h"

struct compile_reflected_file
    : public compile_reflected_container<compile_reflected_variable>,
      public compile_reflected_container<compile_reflection_function>,
      public compile_reflected_container<compile_reflected_class>
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
