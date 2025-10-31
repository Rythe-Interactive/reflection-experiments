#pragma once
#include "../runtime_reflection_containers/runtime_reflected_class.h"
#include "../runtime_reflection_containers/runtime_reflected_variable.h"
#include "../runtime_reflection_containers/runtime_reflected_function.h"

/* This is example of generated from this file:
namespace examle_namespace
{
    class target_class
        {
    public:
        int int_variable;

        void void_function(int int_parameter);

        class nested_class
                {
                public:
                    nested_class() : value(0) {}

                    void set_value(int v)
                    {
                        value = v;
                    }

                    int get_value() const
                    {
                        return value;
                    }

                private:
                    int value;
                };
    private:
        char char_variable;
    };
}
*/

class example_file_generated
{
public:
    void add_reflected_file()
    {
        // All defined types in this file should go in here.
        static const runtime_reflected_class classes[2] = {
            runtime_reflected_class(
                rsl::dynamic_string::from_buffer("example_namespace::target_class"),
                reflection_id(12875366372301390368, 31932944099034707, 15853025086180115556)),
            runtime_reflected_class(
                rsl::dynamic_string::from_buffer("example_namespace::target_class::nested_class"),
                reflection_id(8627741348740311923, 10691473971882747459, 3168970719907517523))
        };

        for(auto reflected_class : classes) { context.add_type(&reflected_class); }
    }
};
