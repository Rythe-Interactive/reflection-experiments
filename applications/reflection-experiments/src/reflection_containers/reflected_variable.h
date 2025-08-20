#pragma once
#include <rsl/containers>
#include "../reflection_properties/access_modifier.h"
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/hashed_string.hpp"

namespace rythe::reflection_containers {

    struct reflected_variable {
        rsl::hashed_string name;
        rsl::dynamic_string current_namespace;
        reflection_properties::acess_modifier access_modifier;
        rsl::dynamic_string attributes[];

        bool is_static;
        bool is_const;

        bool is_array;
        int array_size;
        
        size_t offset;
        size_t size;
        uint16_t alignment;

        reflection_id type_id;
        
        template <typename T>
        reflected_variable()
          : size(sizeof(T)) {
        }
        
        const reflection_id& GetType() const {
            return type_id;
        }

        void* GetValuePtr(void* obj) {
            return reinterpret_cast<char*>(obj) + offset;
        }
    };
}
