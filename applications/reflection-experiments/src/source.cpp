#include <unordered_set>

#include "rsl/containers"
#include "rsl/cli"

#include "reflection_parsers/ast_source_parser.h"


int main(int, char* argv[])
{
    rsl::cli_parser cmdl(argv);

    std::unordered_set<std::string> folders;

    std::string string;
    for(auto& param : cmdl.params("fpath"))
    {
        std::cout << '\t' << param.first << " : " << param.second << '\n';
        folders.insert(param.second);
    }

    std::cout << "Here is the parameter: " << string << std::endl;

    auto parser = reflection_parsers::ast_source_parser();

    parser.parse_source_folders(folders);

    return 0;
}
