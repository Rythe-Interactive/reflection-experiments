#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <string_view>
#include <utility>

#include "rsl/impl/containers/string.hpp"
#include "rsl/impl/math/basic/abs.hpp"
#include "rsl/impl/util/hash.hpp"

struct reflection_id
{
public:
    reflection_id(rsl::string_view name, const void* members_bytes, std::size_t members_size_bytes);

    reflection_id(const reflection_id&) = default;
    reflection_id(reflection_id&&) = default;
    ~reflection_id() = default;

    reflection_id& operator=(const reflection_id&) = delete;
    reflection_id& operator=(reflection_id&&) = delete;

    std::uint64_t get_name_hash() const;
    std::uint64_t get_structure_hash() const;

    std::pair<std::uint64_t, std::uint64_t> get_full_hash() const { return {name_hash, structure_hash}; }

    bool operator==(const reflection_id& other) const noexcept;
    bool operator!=(const reflection_id& other) const noexcept;

    static rsl::string_view get_hash_hex_string(const std::uint64_t& hashh);
    static rsl::string_view get_hash_decimal_string(const std::uint64_t& hash);

    static std::uint64_t compute_hash_from_string(rsl::string_view string);
    static std::uint64_t compute_hash_from_bytes(const void* data, std::size_t size);
private:
    const std::uint64_t name_hash;
    const std::uint64_t structure_hash;
};
