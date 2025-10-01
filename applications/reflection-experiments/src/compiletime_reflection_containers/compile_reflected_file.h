#pragma once
#include "compile_reflected_class.h"
#include "compile_reflected_element.h"
#include "compile_reflected_variable.h"
#include "compile_reflected_function.h"
#include "clang-c/Index.h"

struct compile_reflected_file
    : public compile_reflected_element,
      public compile_reflection_container<compile_reflected_variable>,
      public compile_reflection_container<compile_reflected_function>,
      public compile_reflection_container<compile_reflected_class>
{
public:
    compile_reflected_file(rsl::dynamic_string&& name, rsl::dynamic_string&& source_location);
    compile_reflected_file(const compile_reflected_file& other) = default;
    compile_reflected_file(compile_reflected_file&& other) noexcept = default;
    ~compile_reflected_file();

    void print(int indent) const override;
private:
    rsl::dynamic_string source_location;
};
