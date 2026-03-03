#pragma once
#include <rsl/containers>
#include <rsl/string>

#include "../reflection_properties/access_modifier.h"
#include "../reflection_id/reflection_id.h"

struct runtime_reflected_function
{
public:
    runtime_reflected_function();
    runtime_reflected_function(
        rsl::dynamic_string&&                     name,
        reflection_id&&                           id,
        rsl::dynamic_string&&                     return_type_spelling,
        rsl::dynamic_array<rsl::dynamic_string>&& parameter_types_spelling,
        rsl::dynamic_array<reflection_id>&&       parameter_types,
        rsl::dynamic_array<rsl::dynamic_string>&& parameter_names,
        bool                                      is_const,
        bool                                      is_static);

    rsl::dynamic_string name;
    reflection_id       id;

    rsl::dynamic_string                     return_type_spelling;
    rsl::dynamic_array<reflection_id>       parameter_types;
    rsl::dynamic_array<rsl::dynamic_string> parameter_names;
    rsl::dynamic_array<rsl::dynamic_string> parameter_types_spelling;

    bool is_const;
    bool is_static;
};
