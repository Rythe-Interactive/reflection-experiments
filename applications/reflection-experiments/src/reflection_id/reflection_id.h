#pragma once
#include "rsl/impl/containers/string.hpp"

struct reflection_id {
public:
    reflection_id(const rsl::dynamic_string name):type(name){}
    
    rsl::dynamic_string type;

    rsl::dynamic_string get_type() const {
        return type.data;
    }
};
