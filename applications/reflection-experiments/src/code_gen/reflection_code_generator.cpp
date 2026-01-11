#include "reflection_code_generator.h"
#include <fstream>
#include <iostream>
#include <stdio.h>

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
    const rsl::string_view    source_location = compile_file.get_source_location();
    const rsl::dynamic_string gen_path = get_gen_source_file(source_location);
    std::ofstream             file(gen_path.data());
    if(!file.is_open())
    {
        std::cout << "Could not open file " << source_location.data() << " for writing.\n";
        return;
    }
    const uint64_t file_hash = compile_file.id.get_full_hash();

    file << "#include \"../runtime_reflection_containers/runtime_reflected_class.h\"\n";
    file << "#include \"../runtime_reflection_containers/runtime_reflected_function.h\"\n";
    file << "#include \"../runtime_reflection_containers/runtime_reflected_variable.h\"\n";
    file << "#include \"../reflection_id/reflection_id.h\"\n";
    file << "#include \"../reflection_context/reflection_registration_registry.h\"\n";
    file << "#include \"../reflection_context/reflection_context.h\"\n";
    
    file << "void register_reflection_file_" << file_hash << "()\n";
    file << "{\n";
    
    // Top-level classes
    for(const auto& cls : compile_file.get_class_container())
    {
        generate_reflected_class(file, *cls.get(), "");
    }

    file << "};\n\n";

    file << "struct reflection_file_registration_helper\n";
    file << "{\n";
    file << "    reflection_file_registration_helper()\n";
    file << "    {\n";
    file <<
        "        reflection_registration_registry::instance().add(&register_reflection_file_0);\n";
    file << "    }\n";
    file << "};\n" << "static reflection_file_registration_helper registration_instance;";
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

    char* last_dot = std::strrchr(buffer, '.');
    if(last_dot != nullptr) { *last_dot = '\0'; }

    strcat_s(buffer, "_generated.hpp");

    return rsl::dynamic_string::from_buffer(buffer, std::strlen(buffer) + 1);
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

void reflection_code_generator::generate_reflected_variable(
    std::ofstream&                    file,
    const compile_reflected_variable& variable,
    const std::string&                parent_name)
{
    const std::string variable_name = "variable_" + std::to_string(variable.id.get_full_hash());

    file << "    runtime_reflected_variable " << variable_name << ";\n";
    file << "    " << generate_reflection_id(variable.id, variable_name).data();
    file << "    " << variable_name << ".offset = " << variable.offset << ";\n";
    file << "    " << variable_name << ".type_spelling = " <<
        "rsl::dynamic_string::from_string_length(\"" << variable.type_spelling.data() << "\");\n";
    file << "    " << parent_name << ".add_variable(std::move(" << variable_name << "));\n\n";
}

void reflection_code_generator::generate_reflected_class(
    std::ofstream&                 file,
    const compile_reflected_class& cls,
    const std::string&             parent_name)
{
    const std::string class_var = "class_" + std::to_string(cls.id.get_full_hash());

    file << "    runtime_reflected_class " << class_var << ";\n";
    file << "    " << generate_reflection_id(cls.id, class_var).data();

    for(const auto& var : cls.get_variable_container())
    {
        generate_reflected_variable(file, *var.get(), class_var);
    }

    for(const auto& nested : cls.get_class_container())
    {
        generate_reflected_class(file, *nested.get(), class_var);
    }

    if(parent_name.empty())
    {
        file << "    " << "reflection_context::instance().add_class(std::move(" << class_var <<
            "));\n\n";
    }
    else { file << "    " << parent_name << ".add_class(std::move(" << class_var << "));\n\n"; }
}

std::string reflection_code_generator::generate_reflection_id(
    reflection_id      id,
    const std::string& owner_name) const
{
    std::string generate;

    generate += owner_name;
    generate += ".id = reflection_id(";

    generate += std::to_string(id.get_name_hash()) += "ULL";
    generate += ", ";

    generate += std::to_string(id.get_structure_hash()) += "ULL";
    generate += ", ";

    generate += std::to_string(id.get_full_hash()) += "ULL";
    generate += ");\n";
    
    return generate;
}

