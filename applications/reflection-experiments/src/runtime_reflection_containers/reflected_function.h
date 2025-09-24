#pragma once
#include <rsl/containers>
#include "../reflection_properties/access_modifier.h"
#include "../reflection_id/reflection_id.h"
#include "rsl/impl/containers/hashed_string.hpp"

namespace rythe::reflection_containers
{
    struct reflected_function
    {
    private:
        rsl::hashed_string                    name;
        rsl::dynamic_string                   current_namespace;
        reflection_properties::acess_modifier access_modifier;

        bool is_static;
        bool is_const;

        void* memory_reference;

        reflection_id                           return_type_id;
        rsl::dynamic_array<reflection_id>       parameters;
        rsl::dynamic_array<rsl::dynamic_string> attributes;
    public:
        reflected_function(rsl::hashed_string name, rsl::dynamic_string current_namespace, reflection_properties::acess_modifier access_modifier, bool is_static, bool is_const, void* memory_reference, reflection_id return_type_id, rsl::dynamic_array<reflection_id> parameters, rsl::dynamic_array<rsl::dynamic_string> attributes);

        const rsl::hashed_string&             get_name() const;
        const rsl::dynamic_string&            get_namespace() const;
        reflection_properties::acess_modifier get_access_modifier() const;

        bool get_is_static() const;
        bool get_is_const() const;

        void*                                          get_memory_reference() const;
        const reflection_id&                           get_return_type() const;
        const rsl::dynamic_array<reflection_id>&       get_parameters() const;
        const rsl::dynamic_array<rsl::dynamic_string>& get_attributes() const;

        void set_name(const rsl::hashed_string& new_name);
        void set_namespace(const rsl::dynamic_string& ns);
        void set_access_modifier(reflection_properties::acess_modifier modifier);

        void set_is_static(bool value);
        void set_is_const(bool value);

        void set_memory_reference(void* mem);
        void set_return_type(const reflection_id& id);
        void set_parameters(const rsl::dynamic_array<reflection_id>& params);
        void set_attributes(const rsl::dynamic_array<rsl::dynamic_string>& attrs);

        void* get_value_ptr(void* obj);
    };
}
