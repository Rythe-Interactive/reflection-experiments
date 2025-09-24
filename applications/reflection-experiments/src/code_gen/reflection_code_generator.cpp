#include "reflection_code_generator.h"

#include <fstream>
#include <iostream>

#include "../runtime_reflection_containers/reflected_function.h"
#include "../runtime_reflection_containers/reflected_variable.h"

rsl::dynamic_string reflection_code_generator::generate_variable(rythe::reflection_containers::reflected_variable parsed_variable)
{
    std::string        pad = "    ";
    std::ostringstream out;

    out << "rythe::reflection_containers::reflected_variable(\n";

    const char* name = parsed_variable.get_name().data();
    out << pad << "\"" << name << "\"\n";

    const char* name_space = parsed_variable.get_namespace().data();
    out << pad << "\"" << name_space << "\"\n";

    switch(parsed_variable.get_access_modifier())
    {
        case reflection_properties::acess_modifier::public_access:
            out << pad << "reflection_properties::acess_modifier::public_access,\n";
            break;
        case reflection_properties::acess_modifier::protected_access:
            out << pad << "reflection_properties::acess_modifier::protected_access,\n";
            break;
        case reflection_properties::acess_modifier::private_access:
            out << pad << "reflection_properties::acess_modifier::private_access,\n";
            break;
        default:
            out << pad << "reflection_properties::acess_modifier::public_access,\n";
            break;
    }

    out << pad << (parsed_variable.get_is_static() ? "true" : "false") << ",\n";
    out << pad << (parsed_variable.get_is_const() ? "true" : "false") << ",\n";
    out << pad << (parsed_variable.get_is_array() ? "true" : "false") << ",\n";
    out << pad << parsed_variable.get_array_size() << ",\n";

    out << pad << parsed_variable.get_offset() << ",\n";
    out << pad << parsed_variable.get_size() << ",\n";
    out << pad << parsed_variable.get_alignment() << ",\n";

    const char* type_str = parsed_variable.get_type_id().get_type().data();
    out << pad << "reflection_id(rsl::dynamic_string::from_string_length(" << type_str << ")),\n";

    const auto& attributes = parsed_variable.get_attributes();
    out << pad << "rsl::dynamic_array<rsl::dynamic_string>{";
    if(!attributes.empty()) { out << "\n"; }
    /*for (int i = 0; i < attributes.size(); ++i) {
        const char* attribute = attributes[i].data();
        out << pad << "    rsl::dynamic_string::from_buffer(" 
            << attribute << ", " << (attribute ? attributes.size() : 0) << ")";
        if (i + 1 < attributes) out << ",";
        out << "\n";
    }*/
    if(!attributes.empty()) { out << pad; }
    out << "}\n";

    out << "    )";

    std::string string = out.str();
    return rsl::dynamic_string::from_buffer(string.c_str(), string.size());
}

reflection_code_generator::reflection_code_generator() {}

reflection_code_generator::~reflection_code_generator() {}
/*
rsl::dynamic_string reflection_code_generator::generate_variable(rythe::reflection_containers::reflected_variable parsed_variable) {

    std::string pad = "    ";
    std::ostringstream out;

    out << "rythe::reflection_containers::reflected_variable(\n";

    const char* name = parsed_variable.get_name().data();
    out << pad << "\"" << name << "\"\n";

    const char* name_space = parsed_variable.get_namespace().data();
    out << pad << "\"" << name_space << "\"\n";
    
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
    
    const auto& attributes = parsed_variable.get_attributes();
    out << pad << "rsl::dynamic_array<rsl::dynamic_string>{";
    if (!attributes.empty()) out << "\n";
    for (int i = 0; i < attributes.size(); ++i) {
        const char* attribute = attributes[i].data();
        out << pad << "    rsl::dynamic_string::from_buffer(" 
            << attribute << ", " << (attribute ? attributes.size() : 0) << ")";
        if (i + 1 < attributes) out << ",";
        out << "\n";
    }
    if (!attributes.empty()) out << pad;
    out << "}\n";

    out << "    )";
    
    std::string string = out.str();
    return rsl::dynamic_string::from_buffer(string.c_str(), string.size());
}
*/


void reflection_code_generator::generate_reflected_variable_file(const rythe::reflection_containers::reflected_variable& parsed_variable, const std::string& outFile)
{
    std::cout << "reflection_code_generator::generate_reflected_variable_file\n";
    std::ofstream file(outFile);
    if(!file.is_open()) { std::cout << "Could not open file " << outFile << " for writing.\n"; }

    file << "#include \"reflected_variable.hpp\"\n";
    file << "using namespace rythe::reflection_containers;\n\n";
    file << "void generate_variable(rythe::reflection_containers::reflected_variable parsed_variable) {\n";
    file << "    auto var = " << generate_variable(parsed_variable).data() << ";\n";
    file << "}\n";
}
