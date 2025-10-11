#include "reflection_id.h"

#include <cstring>      // std::memcpy
#include <sstream>
#include <iomanip>

extern "C"
{
#include "xxhash.h"
}

reflection_id::reflection_id(rsl::string_view name, const void* members_bytes, std::size_t members_size_bytes) noexcept
    : name_hash(compute_hash_from_string(name))
  , structure_hash(compute_hash_from_bytes(members_bytes, members_size_bytes)) {}

std::uint64_t reflection_id::get_name_hash() const { return name_hash; }
std::uint64_t reflection_id::get_structure_hash() const { return structure_hash; }

bool reflection_id::operator==(const reflection_id& other) const noexcept
{
    return (name_hash == other.name_hash) && (structure_hash == other.structure_hash);
}

bool reflection_id::operator!=(const reflection_id& other) const noexcept { return !(*this == other); }

rsl::string_view reflection_id::get_hash_hex_string(const std::uint64_t& hash) {}

rsl::string_view reflection_id::get_hash_decimal_string(const std::uint64_t& hash) {}

std::uint64_t reflection_id::compute_hash_from_string(rsl::string_view s) noexcept
{
    return XXH3_64bits(s.data(), s.size());
}

std::uint64_t reflection_id::compute_hash_from_bytes(const void* data, std::size_t size) noexcept
{
    return XXH3_64bits(data, size);
}
