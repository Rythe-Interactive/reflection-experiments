#pragma once
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/string.hpp"

struct runtime_reflected_class
{
    runtime_reflected_class(
        rsl::dynamic_string&& name,
        reflection_id&&       id,
        rsl::size_type&&      offset,
        rsl::dynamic_string&& type_spelling);

    rsl::dynamic_string name;
    reflection_id       id;
    rsl::size_type      offset;
    rsl::dynamic_string type_spelling;
};
