#pragma once
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/string.hpp"

struct runtime_reflected_class
{
public:
    
    runtime_reflected_class(
        rsl::dynamic_string&& name,
        reflection_id&&       id,
        rsl::size_type&&      offset,
        rsl::dynamic_string&& type_spelling);
    runtime_reflected_class(runtime_reflected_class&) = delete;
    runtime_reflected_class(runtime_reflected_class&&) = delete;
    ~runtime_reflected_class();

    bool runtime_reflected_class::operator==(const runtime_reflected_class& other) const;
    bool runtime_reflected_class::operator!=(const runtime_reflected_class& other) const;

    runtime_reflected_class& operator=(const runtime_reflected_class&) = delete;
    runtime_reflected_class& operator=(runtime_reflected_class&&) = delete;
private:
    rsl::dynamic_string name;
    reflection_id       id;
    rsl::size_type      offset;
    rsl::dynamic_string type_spelling;
};
