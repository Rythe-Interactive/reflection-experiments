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
    reflection_id(rsl::id_type name_hash, rsl::id_type structure_hash, rsl::id_type full_hash) noexcept;

    reflection_id(const reflection_id&) = default;
    reflection_id(reflection_id&&) = default;
    ~reflection_id() = default;

    reflection_id& operator=(const reflection_id&) = default;
    reflection_id& operator=(reflection_id&&) = default;

    static reflection_id null() noexcept;

    rsl::id_type get_name_hash() const;
    rsl::id_type get_structure_hash() const;
    rsl::id_type get_full_hash() const;

    void set_name_hash(rsl::id_type hash);
    void set_structure_hash(rsl::id_type hash);
    void set_full_hash(rsl::id_type hash);
    
    bool operator==(const reflection_id& other) const noexcept;
    bool operator!=(const reflection_id& other) const noexcept;

    void print(int indent) const;
    
    static rsl::string_view get_hash_value_hex_string(const rsl::id_type& hash);
    static rsl::string_view get_hash_value_decimal_string(const rsl::id_type& hash);

    reflection_id() noexcept;
private:

    rsl::id_type name_hash;
    rsl::id_type structure_hash;
    rsl::id_type full_hash;
};

// specialize std::hash
namespace std
{
    template<>
    struct hash<reflection_id>
    {
        std::size_t operator()(const reflection_id& id) const noexcept
        {
            // Combine the three 64-bit numbers into one hash
            return id.get_full_hash();
        }
    };
}
