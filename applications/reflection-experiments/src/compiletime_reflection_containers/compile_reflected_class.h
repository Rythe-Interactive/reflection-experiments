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
    rsl::size_type      offset;

    compile_reflected_class(const CXCursor& cursor, const CXCursor& parent);
    compile_reflected_class(const compile_reflected_class&) = default;
    compile_reflected_class(compile_reflected_class&&) noexcept = default;
    ~compile_reflected_class();

    compile_reflected_class&    add_class(CXCursor& cursor, CXCursor& parent);
    compile_reflected_variable& add_variable(CXCursor& cursor, CXCursor& parent);
    compile_reflected_function& add_function(CXCursor& cursor, CXCursor& parent);
    
    void print(int indent) const override;
private:
    rsl::id_type compute_own_structure_hash() noexcept override;
    rsl::id_type compute_container_structure_hash() noexcept override;
};
