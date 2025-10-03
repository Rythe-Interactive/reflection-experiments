#include "reflected_variable.h"

rythe::reflection_containers::reflected_variable::reflected_variable(
    rsl::hashed_string                      name,
    rsl::dynamic_string                     current_namespace,
    reflection_properties::acess_modifier   access_modifier,
    bool                                    is_static,
    bool                                    is_const,
    bool                                    is_array,
    int                                     array_size,
    size_t                                  offset,
    size_t                                  size,
    uint16_t                                alignment,
    reflection_id                           type_id,
    rsl::dynamic_array<rsl::dynamic_string> attributes)
    : name(name)
  , current_namespace(current_namespace)
  , access_modifier(access_modifier)
  , is_static(is_static)
  , is_const(is_const)
  , is_array(is_array)
  , array_size(array_size)
  , offset(offset)
  , size(size)
  , alignment(alignment)
  , type_id(type_id)
  , attributes(attributes) {}

void* rythe::reflection_containers::reflected_variable::get_value_ptr(void* obj)
{
    return reinterpret_cast<char*>(obj) + offset;
}

const rsl::hashed_string& rythe::reflection_containers::reflected_variable::get_name() const { return this->name; }

const rsl::dynamic_string& rythe::reflection_containers::reflected_variable::get_namespace() const
{
    return this->current_namespace;
}

reflection_properties::acess_modifier rythe::reflection_containers::reflected_variable::get_access_modifier() const
{
    return this->access_modifier;
}

bool rythe::reflection_containers::reflected_variable::get_is_static() const { return this->is_static; }

bool rythe::reflection_containers::reflected_variable::get_is_const() const { return this->is_const; }

bool rythe::reflection_containers::reflected_variable::get_is_array() const { return this->is_array; }

int rythe::reflection_containers::reflected_variable::get_array_size() const { return this->array_size; }

size_t rythe::reflection_containers::reflected_variable::get_offset() const { return this->offset; }

size_t rythe::reflection_containers::reflected_variable::get_size() const { return this->size; }

uint16_t rythe::reflection_containers::reflected_variable::get_alignment() const { return this->alignment; }

const reflection_id& rythe::reflection_containers::reflected_variable::get_type_id() const { return this->type_id; }

const rsl::dynamic_array<rsl::dynamic_string>& rythe::reflection_containers::reflected_variable::get_attributes() const
{
    return this->attributes;
}

void rythe::reflection_containers::reflected_variable::set_name(const rsl::hashed_string& name) { this->name = name; }

void rythe::reflection_containers::reflected_variable::set_namespace(const rsl::dynamic_string& current_namespace)
{
    this->current_namespace = current_namespace;
}

void rythe::reflection_containers::reflected_variable::set_access_modifier(
    reflection_properties::acess_modifier access_modifier) { this->access_modifier = access_modifier; }

void rythe::reflection_containers::reflected_variable::set_is_static(bool is_static) { this->is_static = is_static; }

void rythe::reflection_containers::reflected_variable::set_is_const(bool is_const) { this->is_const = is_const; }

void rythe::reflection_containers::reflected_variable::set_is_array(bool is_array) { this->is_array = is_array; }

void rythe::reflection_containers::reflected_variable::set_array_size(int array_size) { this->array_size = array_size; }

void rythe::reflection_containers::reflected_variable::set_offset(size_t offset) { this->offset = offset; }

void rythe::reflection_containers::reflected_variable::set_size(size_t size) { this->size = size; }

void rythe::reflection_containers::reflected_variable::set_alignment(uint16_t alignment)
{
    this->alignment = alignment;
}

void rythe::reflection_containers::reflected_variable::set_type_id(const reflection_id& type_id)
{
    this->type_id = type_id;
}

void rythe::reflection_containers::reflected_variable::set_attributes(
    const rsl::dynamic_array<rsl::dynamic_string>& attributes) { this->attributes = attributes; }
