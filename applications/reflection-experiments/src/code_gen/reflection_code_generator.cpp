#include "reflection_code_generator.h"

/*
rsl::dynamic_string reflection_code_generator::generate_variable(rythe::reflection_containers::reflected_variable parsed_variable, int indent = 4) {

    rsl::dynamic_string pad = rsl::dynamic_string::from_buffer("    ");
    std::ostringstream out;

    out << "rythe::reflection_containers::reflected_variable(\n";

    const char* name = parsed_variable.get_name().data();
    out << pad << "rsl::hashed_string::from_buffer(" 
        << name << ", " << (name ? std::strlen(name) : 0) << "),\n";

    const char* ns = parsed_variable.get_namespace().data();
    out << pad << "rsl::dynamic_string::from_buffer(" 
        << name << ", " << (ns ? std::strlen(ns) : 0) << "),\n";
    
    switch (parsed_variable.get_access_modifier()) {
        case reflection_properties::acess_modifier::public_access:
            out << pad << "reflection_properties::acess_modifier::public_access,\n"; break;
        case reflection_properties::acess_modifier::protected_access:
            out << pad << "reflection_properties::acess_modifier::protected_access,\n"; break;
        case reflection_properties::acess_modifier::private_access:
            out << pad << "reflection_properties::acess_modifier::private_access,\n"; break;
        default:
            out << pad << "reflection_properties::acess_modifier::public_access,\n"; break;
    }
    
    out << pad << (parsed_variable.get_is_static() ? "true" : "false") << ",\n";
    out << pad << (parsed_variable.get_is_const() ? "true" : "false") << ",\n";
    out << pad << (parsed_variable.get_is_array() ? "true" : "false") << ",\n";
    out << pad << parsed_variable.get_array_size() << ",\n";
    
    out << pad << parsed_variable.get_offset() << ",\n";
    out << pad << parsed_variable.get_size() << ",\n";
    out << pad << parsed_variable.get_alignment() << ",\n";
    
    const char* type_str = parsed_variable.get_type_id().get_type().data();
    out << pad << "reflection_id(rsl::dynamic_string::from_buffer("
        << type_str << ", " << (type_str ? std::strlen(type_str) : 0) << ")),\n";
    
    const auto& attrs = parsed_variable.get_attributes();
    out << pad << "rsl::dynamic_array<rsl::dynamic_string>{";
    if (!attrs.empty()) out << "\n";
    for (size_t i = 0; i < attrs.size(); ++i) {
        const char* a = attrs[i].data();
        out << pad << "    rsl::dynamic_string::from_buffer(" 
            << a << ", " << (a ? std::strlen(a) : 0) << ")";
        if (i + 1 < attrs.size()) out << ",";
        out << "\n";
    }
    if (!attrs.empty()) out << pad;
    out << "}\n";

    out << "    )";
    return ;
}*/
