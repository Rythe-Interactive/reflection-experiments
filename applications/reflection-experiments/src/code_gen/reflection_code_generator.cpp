#include "reflection_code_generator.h"
#include "D:/MyProjects/reflection-experiments/applications/reflection-experiments/src/target/test.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "../runtime_reflection_containers/reflected_function.h"
#include "../runtime_reflection_containers/runtime_reflected_variable.h"

const rsl::dynamic_string reflection_code_generator::generate_variable(
    [[maybe_unused]] runtime_reflected_variable parsed_variable)
{
    /*
    std::string        pad = "    ";
    std::ostringstream out;

    out << "rythe::reflection_containers::runtime_reflected_variable(\n";

    const char* name = parsed_variable.get_name().data();
    out << pad << "\"" << name << "\"\n";

    const char* name_space = parsed_variable.get_namespace().data();
    out << pad << "\"" << name_space << "\"\n";

    switch(parsed_variable.get_access_modifier())
    {
        case reflection_properties::access_modifier::public_access:
            out << pad << "reflection_properties::acess_modifier::public_access,\n";
            break;
        case reflection_properties::access_modifier::protected_access:
            out << pad << "reflection_properties::acess_modifier::protected_access,\n";
            break;
        case reflection_properties::access_modifier::private_access:
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

    //const char* type_str = parsed_variable.get_type_id().get_type().data();
    //out << pad << "reflection_id(rsl::dynamic_string::from_string_length(" << type_str << ")),\n";

    const auto& attributes = parsed_variable.get_attributes();
    out << pad << "rsl::dynamic_array<rsl::dynamic_string>{";
    if(!attributes.empty()) { out << "\n"; }
    for (int i = 0; i < attributes.size(); ++i) {
        const char* attribute = attributes[i].data();
        out << pad << "    rsl::dynamic_string::from_buffer(" 
            << attribute << ", " << (attribute ? attributes.size() : 0) << ")";
        if (i + 1 < attributes) out << ",";
        out << "\n";
    }
    
    if(!attributes.empty()) { out << pad; }
    out << "}\n";

    out << "    )";

    std::string string = out.str();
    return rsl::dynamic_string::from_buffer(string.c_str(), string.size());
    */
    return {};
}

reflection_code_generator::reflection_code_generator() {}

reflection_code_generator::~reflection_code_generator() {}

void reflection_code_generator::generate_reflected_file(const compile_reflected_file& compile_file)
{
    const rsl::string_view source_location = compile_file.get_source_location();
    std::ofstream          file(get_gen_source_file(source_location).data());
    if(!file.is_open()) { std::cout << "Could not open file " << source_location.data() << " for writing.\n"; }

    file << "#include \"runtime_reflected_variable.hpp\"\n";
    file << "using namespace rythe::reflection_containers;\n\n";
    file << "void generate_variable(rythe::reflection_containers::runtime_reflected_variable parsed_variable) {\n";
    //file << "    auto var = " << generate_variable(parsed_variable).data() << ";\n";
    file << "}\n";
}

rsl::dynamic_string reflection_code_generator::get_gen_source_file(rsl::string_view source_location)
{
    if(source_location.size() >= 256)
    {
        std::cout << "source_path is too long\n";
        return {};
    }

    char buffer[256];
    std::memcpy(buffer, source_location.data(), source_location.size());
    buffer[source_location.size()] = '\0';
    
    char* lastSlash = std::strrchr(buffer, '/');
    if(lastSlash != nullptr) { *lastSlash = '\0'; }

    strcat_s(buffer, sizeof(buffer), "/generated");

    return rsl::dynamic_string::from_buffer(buffer, std::strlen(buffer));
}


/*
rsl::dynamic_string reflection_code_generator::generate_variable(rythe::reflection_containers::runtime_reflected_variable parsed_variable) {

    std::string pad = "    ";
    std::ostringstream out;

    out << "rythe::reflection_containers::runtime_reflected_variable(\n";

    const char* name = parsed_variable.get_source_location().data();
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


void reflection_code_generator::generate_reflected_variable_file(
    const runtime_reflected_variable& parsed_variable,
    const std::string&                outFile)
{
    std::cout << "reflection_code_generator::generate_reflected_variable_file\n";
    std::ofstream file(outFile);
    if(!file.is_open()) { std::cout << "Could not open file " << outFile << " for writing.\n"; }

    file << "#include \"runtime_reflected_variable.hpp\"\n";
    file << "using namespace rythe::reflection_containers;\n\n";
    file << "void generate_variable(rythe::reflection_containers::runtime_reflected_variable parsed_variable) {\n";
    file << "    auto var = " << generate_variable(parsed_variable).data() << ";\n";
    file << "}\n";
}
