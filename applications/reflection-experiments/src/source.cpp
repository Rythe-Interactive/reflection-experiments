#include <unordered_set>

#include <rsl/cli>

#include "impl/reflection_parsers/ast_source_parser.h"
#include "impl/reflection_context/reflection_context.h"
#include "impl/reflection_context/reflection_registration_registry.h"

int main(int, char* argv[])
{
    rsl::cli_parser cmdl(argv);
    
    reflection_registration_registry::instance().run_all();

    reflection_context::instance().print_classes();
    
    return 0;
}
