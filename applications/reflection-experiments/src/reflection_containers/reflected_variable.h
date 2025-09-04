#pragma once
#include <rsl/containers>
#include "../reflection_properties/access_modifier.h"
#include "../reflection_id/reflection_id.h"

namespace rythe::reflection_containers {

    struct reflected_variable {
        rsl::hashed_string name;
        rsl::dynamic_string current_namespace;
        reflection_properties::acess_modifier access_modifier;
        
        bool is_static;
        bool is_const;

        bool is_array;
        int array_size;
        
        size_t offset;
        size_t size;
        uint16_t alignment;

        reflection_id type_id;

        rsl::dynamic_array<rsl::dynamic_string> attributes;
        
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
