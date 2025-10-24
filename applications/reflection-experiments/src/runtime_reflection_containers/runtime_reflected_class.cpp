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
