#include "runtime_reflection_containers.h"
#include "impl/reflection_id/reflection_id.h"
#include "impl/reflection_context/reflection_registration_registry.h"
#include "impl/reflection_context/reflection_context.h"
void register_reflection_file_test6()
{
    runtime_reflected_class class_8289272331526344721;
    class_8289272331526344721.name = rsl::dynamic_string::from_string_length("very_cool_target_class6");
    class_8289272331526344721.id = reflection_id(10760971408359493101ULL, 3676408051602900246ULL, 8289272331526344721ULL);
    class_8289272331526344721.type_spelling = rsl::dynamic_string::from_string_length("very_cool_target_class6");

    runtime_reflected_variable variable_6501503083828029313;
    variable_6501503083828029313.name = rsl::dynamic_string::from_string_length("int_variable");
    variable_6501503083828029313.id = reflection_id(10933754376540684078ULL, 16350452351519940193ULL, 6501503083828029313ULL);
    variable_6501503083828029313.offset = 0;
    variable_6501503083828029313.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_8289272331526344721.add_variable(std::move(variable_6501503083828029313));

    runtime_reflected_variable variable_126163732700301715;
    variable_126163732700301715.name = rsl::dynamic_string::from_string_length("variable");
    variable_126163732700301715.id = reflection_id(5770744143431503129ULL, 12913254394975708779ULL, 126163732700301715ULL);
    variable_126163732700301715.offset = 4;
    variable_126163732700301715.type_spelling = rsl::dynamic_string::from_string_length("float");
    class_8289272331526344721.add_variable(std::move(variable_126163732700301715));

    runtime_reflected_variable variable_17337086075296791468;
    variable_17337086075296791468.name = rsl::dynamic_string::from_string_length("char_variable");
    variable_17337086075296791468.id = reflection_id(15779825311949492597ULL, 9221959329564397894ULL, 17337086075296791468ULL);
    variable_17337086075296791468.offset = 8;
    variable_17337086075296791468.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_8289272331526344721.add_variable(std::move(variable_17337086075296791468));

    runtime_reflected_function function_11759744666720004420;
    function_11759744666720004420.name = rsl::dynamic_string::from_string_length("void_function");
    function_11759744666720004420.id = reflection_id(5474487154151368338ULL, 18229931349466367843ULL, 11759744666720004420ULL);
    function_11759744666720004420.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_11759744666720004420.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_11759744666720004420.parameter_names.push_back(rsl::dynamic_string::from_string_length("int_parameter"));
    function_11759744666720004420.is_const = false;
    function_11759744666720004420.is_static = false;
    class_8289272331526344721.add_function(std::move(function_11759744666720004420));

    runtime_reflected_class class_4925371442925827229;
    class_4925371442925827229.name = rsl::dynamic_string::from_string_length("nested_class6");
    class_4925371442925827229.id = reflection_id(8923260168921671644ULL, 7743830921338232219ULL, 4925371442925827229ULL);
    class_4925371442925827229.type_spelling = rsl::dynamic_string::from_string_length("nested_class6");

    runtime_reflected_variable variable_9809713342160364025;
    variable_9809713342160364025.name = rsl::dynamic_string::from_string_length("value");
    variable_9809713342160364025.id = reflection_id(785375445157317512ULL, 16350452351519940193ULL, 9809713342160364025ULL);
    variable_9809713342160364025.offset = 0;
    variable_9809713342160364025.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_4925371442925827229.add_variable(std::move(variable_9809713342160364025));

    runtime_reflected_function function_8326206098713976876;
    function_8326206098713976876.name = rsl::dynamic_string::from_string_length("get_value");
    function_8326206098713976876.id = reflection_id(4568201618035357963ULL, 3401684896289255038ULL, 8326206098713976876ULL);
    function_8326206098713976876.return_type_spelling = rsl::dynamic_string::from_string_length("int");
    function_8326206098713976876.is_const = true;
    function_8326206098713976876.is_static = false;
    class_4925371442925827229.add_function(std::move(function_8326206098713976876));

    runtime_reflected_function function_3472948984907647894;
    function_3472948984907647894.name = rsl::dynamic_string::from_string_length("nested_class");
    function_3472948984907647894.id = reflection_id(8627741348740311923ULL, 1911340477269032797ULL, 3472948984907647894ULL);
    function_3472948984907647894.return_type_spelling = rsl::dynamic_string::from_string_length("int");
    function_3472948984907647894.is_const = false;
    function_3472948984907647894.is_static = false;
    class_4925371442925827229.add_function(std::move(function_3472948984907647894));

    runtime_reflected_function function_15519012992129584017;
    function_15519012992129584017.name = rsl::dynamic_string::from_string_length("set_value");
    function_15519012992129584017.id = reflection_id(4624142122059757516ULL, 18229931349466367843ULL, 15519012992129584017ULL);
    function_15519012992129584017.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_15519012992129584017.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_15519012992129584017.parameter_names.push_back(rsl::dynamic_string::from_string_length("v"));
    function_15519012992129584017.is_const = false;
    function_15519012992129584017.is_static = false;
    class_4925371442925827229.add_function(std::move(function_15519012992129584017));

    class_8289272331526344721.add_class(std::move(class_4925371442925827229));

    reflection_context::instance().add_class(std::move(class_8289272331526344721));

    runtime_reflected_class class_7008656928531724364;
    class_7008656928531724364.name = rsl::dynamic_string::from_string_length("target_class6");
    class_7008656928531724364.id = reflection_id(2923096643722786925ULL, 529573297870223312ULL, 7008656928531724364ULL);
    class_7008656928531724364.type_spelling = rsl::dynamic_string::from_string_length("target_class6");

    runtime_reflected_variable variable_13153249853553726320;
    variable_13153249853553726320.name = rsl::dynamic_string::from_string_length("int_variable2");
    variable_13153249853553726320.id = reflection_id(4281340778281841492ULL, 16350452351519940193ULL, 13153249853553726320ULL);
    variable_13153249853553726320.offset = 0;
    variable_13153249853553726320.type_spelling = rsl::dynamic_string::from_string_length("int");
    class_7008656928531724364.add_variable(std::move(variable_13153249853553726320));

    runtime_reflected_variable variable_6526241590453974317;
    variable_6526241590453974317.name = rsl::dynamic_string::from_string_length("char_variable2");
    variable_6526241590453974317.id = reflection_id(10234543199726084352ULL, 9221959329564397894ULL, 6526241590453974317ULL);
    variable_6526241590453974317.offset = 4;
    variable_6526241590453974317.type_spelling = rsl::dynamic_string::from_string_length("char");
    class_7008656928531724364.add_variable(std::move(variable_6526241590453974317));

    runtime_reflected_function function_14922869285292655127;
    function_14922869285292655127.name = rsl::dynamic_string::from_string_length("void_function2");
    function_14922869285292655127.id = reflection_id(15516586722032245315ULL, 7342613789149850713ULL, 14922869285292655127ULL);
    function_14922869285292655127.return_type_spelling = rsl::dynamic_string::from_string_length("void");
    function_14922869285292655127.parameter_types_spelling.push_back(rsl::dynamic_string::from_string_length("int"));
    function_14922869285292655127.parameter_names.push_back(rsl::dynamic_string::from_string_length("int_parameter"));
    function_14922869285292655127.is_const = false;
    function_14922869285292655127.is_static = true;
    class_7008656928531724364.add_function(std::move(function_14922869285292655127));

    reflection_context::instance().add_class(std::move(class_7008656928531724364));

};

struct reflection_file_registration_helper
{
    reflection_file_registration_helper()
    {
        reflection_registration_registry::instance().add(&register_reflection_file_test6);
    }
};
static reflection_file_registration_helper registration_instance;