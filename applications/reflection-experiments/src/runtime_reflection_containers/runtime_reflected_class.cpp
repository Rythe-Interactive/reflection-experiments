#include "runtime_reflected_class.h"

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

