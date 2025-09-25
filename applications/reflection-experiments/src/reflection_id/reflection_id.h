#pragma once
#include <iostream>

#include <rsl/string>

struct reflection_id
{
public:
    reflection_id(const rsl::dynamic_string name) : type(name) {}

    rsl::dynamic_string type;

    rsl::dynamic_string get_type() const
    {
        std::cout << type.data() << std::endl;
        return type;
    }
};
