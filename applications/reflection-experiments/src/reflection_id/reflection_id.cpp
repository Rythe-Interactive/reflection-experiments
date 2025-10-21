#include "reflection_id.h"

#include <algorithm>
#include <cstring>      // std::memcpy
#include <sstream>
#include <iomanip>

extern "C"
{
#include "xxhash.h"
}

reflection_id::reflection_id(rsl::string_view name, std::vector<std::pair<std::size_t, rsl::id_type>>& members) noexcept
    : name_hash(rsl::hash_string(name))
  , structure_hash(generate_structure_hash(members))
{
    full_hash = rsl::combine_hash(rsl::internal::hash::default_seed, name_hash, structure_hash);
}

reflection_id reflection_id::null() noexcept { return reflection_id(); }
rsl::id_type  reflection_id::get_name_hash() const { return name_hash; }

rsl::id_type reflection_id::get_structure_hash() const { return structure_hash; }
rsl::id_type reflection_id::get_full_hash() const { return full_hash; }

void reflection_id::set_name_hash(rsl::id_type hash) { name_hash = hash; }
void reflection_id::set_structure_hash(rsl::id_type hash) { structure_hash = hash; }
void reflection_id::set_full_hash(rsl::id_type hash) { full_hash = hash; }

bool         reflection_id::operator==(const reflection_id& other) const noexcept
{
    return (name_hash == other.name_hash) && (structure_hash == other.structure_hash);
}

bool reflection_id::operator!=(const reflection_id& other) const noexcept { return !(*this == other); }

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

rsl::id_type reflection_id::generate_structure_hash(std::vector<std::pair<std::size_t, rsl::id_type>>& members) noexcept
{
    std::ranges::sort(
        members,
        [](const std::pair<std::size_t, rsl::id_type> a, const std::pair<std::size_t, rsl::id_type> b)
        {
            return a.first <= b.first;
        });

    rsl::id_type hash = rsl::internal::hash::default_seed;
    for(const auto& member : members)
    {
        rsl::id_type member_hash = member.second;
        hash = rsl::combine_hash(rsl::internal::hash::default_seed, hash, member_hash);
    }
    return hash;
}
