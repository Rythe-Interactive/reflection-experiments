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
    reflection_id(rsl::string_view name, std::vector<std::pair<std::size_t, rsl::id_type>>& members) noexcept;

    reflection_id(const reflection_id&) = default;
    reflection_id(reflection_id&&) = default;
    ~reflection_id() = default;

    reflection_id& operator=(const reflection_id&) = delete;
    reflection_id& operator=(reflection_id&&) = delete;

    static reflection_id null() noexcept;

    rsl::id_type get_name_hash() const;
    rsl::id_type get_structure_hash() const;
    rsl::id_type get_full_hash() const;

    void set_name_hash(rsl::id_type hash);
    void set_structure_hash(rsl::id_type hash);
    void set_full_hash(rsl::id_type hash);
    
    bool operator==(const reflection_id& other) const noexcept;
    bool operator!=(const reflection_id& other) const noexcept;

    static rsl::string_view get_hash_value_hex_string(const rsl::id_type& hash);
    static rsl::string_view get_hash_value_decimal_string(const rsl::id_type& hash);
    
private:
    reflection_id() noexcept;

    rsl::id_type name_hash;
    rsl::id_type structure_hash;
    rsl::id_type full_hash;

    static rsl::id_type generate_structure_hash(std::vector<std::pair<std::size_t, rsl::id_type>>& members) noexcept;
};
