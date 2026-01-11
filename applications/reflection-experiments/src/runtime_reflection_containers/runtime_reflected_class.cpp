#include "runtime_reflected_class.h"

runtime_reflected_class::runtime_reflected_class() {}

runtime_reflected_class::runtime_reflected_class(
    rsl::dynamic_string&& name,
    rsl::dynamic_string&& type_spelling,
    reflection_id&&       id)
    : name(std::move(name))
  , type_spelling(std::move(type_spelling))
  , id(id) {}

runtime_reflected_class::~runtime_reflected_class() {}

[[nodiscard]] bool runtime_reflected_class::operator==(const runtime_reflected_class& other) const
{
    return this->id == other.id;
}

[[nodiscard]] bool runtime_reflected_class::operator!=(const runtime_reflected_class& other) const
{
    return !this->operator==(other);
}

void runtime_reflected_class::add_variable(runtime_reflected_variable&& variable)
{
    this->variables.push_back(std::move(variable));
}

void runtime_reflected_class::add_class(runtime_reflected_class&& cls)
{
    this->classes.push_back(std::move(cls));
}

void runtime_reflected_class::add_function(runtime_reflected_function&& function)
{
    this->functions.push_back(std::move(function));
}

