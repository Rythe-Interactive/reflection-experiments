#include "runtime_reflected_class.h"

runtime_reflected_class::runtime_reflected_class(
    rsl::dynamic_string&& name,
    reflection_id&&       id,
    rsl::size_type&&      offset,
    rsl::dynamic_string&& type_spelling)
    : name(std::move(name))
  , id(id)
  , offset(offset)
  , type_spelling(std::move(type_spelling)) {}

runtime_reflected_class::~runtime_reflected_class() {}

bool runtime_reflected_class::operator==(const runtime_reflected_class& other) const { return this->id == other.id; }
bool runtime_reflected_class::operator!=(const runtime_reflected_class& other) const
{
    return !this->operator==(other);
}

