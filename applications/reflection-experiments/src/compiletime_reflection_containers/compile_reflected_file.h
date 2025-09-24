#pragma once
#include <map>

#include "compile_reflected_variable_container.h"
#include "clang-c/Index.h"

class compile_reflected_file : public compile_reflected_variable_container
{
public:
    rsl::dynamic_string name;
    compile_reflected_file(const rsl::dynamic_string source_location);
    ~compile_reflected_file();
private:
    rsl::dynamic_string source_location;
};
