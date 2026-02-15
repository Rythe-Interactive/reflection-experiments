#include <unordered_set>

#include <rsl/cli>

#include "impl/reflection_parsers/ast_source_parser.h"
#include "impl/reflection_context/reflection_context.h"
#include "impl/reflection_context/reflection_registration_registry.h"
#include "target/test_generated.hpp"

int main(int, char* argv[])
{
    rsl::cli_parser cmdl(argv);

    // any particular reason for unordered_set?
    std::unordered_set<std::string> folders;

    for(auto& param : cmdl.params("fpath"))
    {
        std::cout << '\t' << param.first << " : " << param.second << '\n';
        folders.insert(param.second);
    }

    auto parser = reflection_parsers::ast_source_parser();

    parser.generate_reflection_files(folders);
    reflection_registration_registry::instance().clear();
    register_reflection_file_0();
    reflection_registration_registry::instance().run_all();
    //lala
    reflection_context::instance().print_classes();    
    
    
    return 0;
}
