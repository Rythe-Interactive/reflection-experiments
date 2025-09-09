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
        
        reflected_variable(rsl::hashed_string name,
            rsl::dynamic_string current_namespace,
            reflection_properties::acess_modifier access_modifier,
            bool is_static,
            bool is_const,
            bool is_array,
            int array_size,
            size_t offset,
            size_t size,
            uint16_t alignment,
            reflection_id type_id,
            rsl::dynamic_array<rsl::dynamic_string> attributes);

        template <typename T>
            reflected_variable()
              : size(sizeof(T)), alignment(alignof(T)){}


        void* get_value_ptr(void* obj) {
            return reinterpret_cast<char*>(obj) + offset;
        }

        const rsl::hashed_string& get_name() const;
        const rsl::dynamic_string& get_namespace() const;
        reflection_properties::acess_modifier get_access_modifier() const;

        bool get_is_static() const;
        bool get_is_const() const;

        bool get_is_array() const;
        int get_array_size() const;

        size_t get_offset() const;
        size_t get_size() const;
        uint16_t get_alignment() const;

        const reflection_id& get_type_id() const;
        const rsl::dynamic_array<rsl::dynamic_string>& get_attributes() const;
        
        void set_name(const rsl::hashed_string& n);
        void set_namespace(const rsl::dynamic_string& ns);
        void set_access_modifier(reflection_properties::acess_modifier mod);

        void set_is_static(bool v);
        void set_is_const(bool v);

        void set_is_array(bool v);
        void set_array_size(int sz);

        void set_offset(size_t o);
        void set_size(size_t s);
        void set_alignment(uint16_t a);

        void set_type_id(const reflection_id& id);
        void set_attributes(const rsl::dynamic_array<rsl::dynamic_string>& attrs);
    };
}
