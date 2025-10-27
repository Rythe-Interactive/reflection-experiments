#pragma once
#include "../runtime_reflection_containers/runtime_reflected_class.h"
#include "../runtime_reflection_containers/runtime_reflected_variable.h"
#include "../runtime_reflection_containers/runtime_reflected_function.h"

/* This is example of generated from this file:
class target_class
    {
public:
    int int_variable;

    void void_function(int int_parameter);
private:
    char char_variable;
};
*/
static class example_file_generated
{
public:
    static std::vector<runtime_reflected_class>& get_reflected_classes()
    {
        
        if(!is_initialized)
        
    }
private:
    static std::vector<runtime_reflected_class> reflected_classes;
};
