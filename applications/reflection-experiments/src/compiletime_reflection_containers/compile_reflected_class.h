#pragma once
#include "compile_reflection_container.h"
#include "compile_reflected_variable.h"
#include "compile_reflected_function.h"

#include <rsl/string>

struct compile_reflected_class
    : public compile_reflected_element,
      public compile_reflection_container<compile_reflected_class>,
      public compile_reflection_container<compile_reflected_variable>,
      public compile_reflection_container<compile_reflected_function>
{
public:
    rsl::dynamic_string type_spelling;

    compile_reflected_class(CXCursor cursor);
    compile_reflected_class(const compile_reflected_class&) = default;
    compile_reflected_class(compile_reflected_class&&) noexcept = default;
    ~compile_reflected_class();

    void print(int indent) const override;
private:
    
};
