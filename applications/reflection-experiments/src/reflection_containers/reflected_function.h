#pragma once
#include <rsl/containers>
#include "../reflection_properties/access_modifier.h"
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/hashed_string.hpp"

namespace rythe::reflection_containers {
    struct reflected_function {
        rsl::hashed_string name;
        rsl::dynamic_string current_namespace;
        reflection_properties::acess_modifier access_modifier;

        bool is_static;
        bool is_const;
        
        void* memory_reference;
        
        reflection_id return_type_id;
        rsl::dynamic_array<reflection_id> parameters;

        rsl::dynamic_array<rsl::dynamic_string> attributes;
        
        template <typename T>
        reflected_function() {
        }
            
        const reflection_id& get_return_type() const {
            return return_type_id;
        }

        void* get_value_ptr(void* obj) {
            return reinterpret_cast<char*>(obj);
        }
    };
}