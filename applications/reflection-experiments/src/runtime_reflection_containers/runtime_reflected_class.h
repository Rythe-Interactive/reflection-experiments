#pragma once
#include "runtime_reflected_function.h"
#include "runtime_reflected_variable.h"
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/string.hpp"

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

    void add_variable(runtime_reflected_variable&& variable);
    void add_class(runtime_reflected_class&& variable);
    void add_functions(runtime_reflected_function&& variable);
private:
    rsl::dynamic_string name;
    rsl::dynamic_string type_spelling;
    reflection_id       id;

    std::vector<runtime_reflected_class>    classes;
    std::vector<runtime_reflected_function> functions;
    std::vector<runtime_reflected_variable> variables;
};
