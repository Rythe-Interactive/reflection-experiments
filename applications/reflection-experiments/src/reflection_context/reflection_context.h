#pragma once

#include <iostream> // for std::cout
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <map>

#include "../runtime_reflection_containers.h"
class reflection_context
{
public:
    static reflection_context& instance();

    reflection_context(const reflection_context&) = delete;
    reflection_context& operator=(const reflection_context&) = delete;

    runtime_reflected_class* find_class(reflection_id id);

    void add_class(runtime_reflected_class&& cls);

    void clear();
    void print_classes() const;
private:
    reflection_context() = default;
    ~reflection_context() = default;

    std::unordered_map<reflection_id, runtime_reflected_class> classes;
};
