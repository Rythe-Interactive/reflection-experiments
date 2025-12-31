#pragma once
#include "runtime_reflected_function.h"
#include "runtime_reflected_variable.h"
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/string.hpp"

// In class definition case, its name is its type.
// Because we are using inheritance, name is its base class property, so cant really change that, unfortunate.

struct runtime_reflected_class
{
public:
    runtime_reflected_class(rsl::dynamic_string&& name, rsl::dynamic_string&& type_spelling, reflection_id&& id);
    runtime_reflected_class(runtime_reflected_class&) = delete;
    runtime_reflected_class(runtime_reflected_class&&) = delete;
    ~runtime_reflected_class();

    bool operator==(const runtime_reflected_class& other) const;
    bool operator!=(const runtime_reflected_class& other) const;

    runtime_reflected_class& operator=(const runtime_reflected_class&) = delete;
    runtime_reflected_class& operator=(runtime_reflected_class&&) = delete;
private:
    rsl::dynamic_string name;
    rsl::dynamic_string type_spelling;
    reflection_id       id;

    std::vector<runtime_reflected_class>    classes;
    std::vector<runtime_reflected_function> functions;
    std::vector<runtime_reflected_variable> variables;
};
