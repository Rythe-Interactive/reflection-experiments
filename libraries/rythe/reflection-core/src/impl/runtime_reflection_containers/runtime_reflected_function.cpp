#include "runtime_reflected_function.h"

runtime_reflected_function::runtime_reflected_function() {}

runtime_reflected_function::runtime_reflected_function(
    rsl::dynamic_string&&                     name,
    reflection_id&&                           id,
    rsl::dynamic_string&&                     return_type_spelling,
    rsl::dynamic_array<rsl::dynamic_string>&& parameter_types_spelling,
    rsl::dynamic_array<reflection_id>&&       parameter_types,
    rsl::dynamic_array<rsl::dynamic_string>&& parameter_names,
    bool                                      is_const,
    bool                                      is_static)
    : name(std::move(name))
  , id(id)
  , return_type_spelling(return_type_spelling)
  , parameter_types(parameter_types)
  , parameter_names(parameter_names)
  , parameter_types_spelling(parameter_types_spelling)
  , is_const(is_const)
  , is_static(is_static) {}
