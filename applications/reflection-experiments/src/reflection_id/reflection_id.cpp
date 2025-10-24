#include "reflection_id.h"

#include <algorithm>
#include <cstring>      // std::memcpy
#include <sstream>
#include <iomanip>
#include <iostream>

reflection_id::reflection_id(rsl::id_type name_hash, rsl::id_type structure_hash, rsl::id_type full_hash) noexcept
    : name_hash(name_hash)
  , structure_hash(structure_hash)
  , full_hash(full_hash) {}

reflection_id reflection_id::null() noexcept { return reflection_id(); }
rsl::id_type  reflection_id::get_name_hash() const { return name_hash; }

rsl::id_type reflection_id::get_structure_hash() const { return structure_hash; }
rsl::id_type reflection_id::get_full_hash() const { return full_hash; }

void reflection_id::set_name_hash(rsl::id_type hash) { name_hash = hash; }
void reflection_id::set_structure_hash(rsl::id_type hash) { structure_hash = hash; }
void reflection_id::set_full_hash(rsl::id_type hash) { full_hash = hash; }

bool reflection_id::operator==(const reflection_id& other) const noexcept
{
    return (name_hash == other.name_hash) && (structure_hash == other.structure_hash);
}

bool reflection_id::operator!=(const reflection_id& other) const noexcept { return !(*this == other); }
void reflection_id::print(int indent) const
{
    for(auto i = 0; i < indent; i++) { std::cout << ' '; }
    std::cout << "Full hash: " << this->get_full_hash() << '\n';

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Name hash: " << this->get_name_hash() << '\n';

    for(auto i = 0; i < indent + 1; i++) { std::cout << ' '; }
    std::cout << "Structure hash: " << this->get_structure_hash() << '\n';
}

rsl::string_view reflection_id::get_hash_value_hex_string(const rsl::id_type& hash)
{
    std::stringstream result;
    result << "0x" << std::hex << hash;
    return rsl::string_view::from_buffer(result.str().data(), result.str().size());
}

rsl::string_view reflection_id::get_hash_value_decimal_string(const rsl::id_type& hash)
{
    std::stringstream result;
    result << hash;
    return rsl::string_view::from_buffer(result.str().data(), result.str().size());
}

reflection_id::reflection_id() noexcept
    : name_hash(0)
  , structure_hash(0)
  , full_hash(0) {}
