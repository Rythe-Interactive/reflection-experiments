#include <unordered_set>

#include <rsl/cli>

#include "impl/reflection_parsers/ast_source_parser.h"

int main(int, char* argv[])
{
    rsl::cli_parser cmdl(argv);

    rsl::dynamic_array<std::string> folders;
    std::string                     generate_folder;
    
    for(auto& param : cmdl.params("fpath"))
    {
        std::cout << '\t' << param.first << " : " << param.second << '\n';
        folders.emplace_back(param.second);
    }

    for (size_t i = 0; i < cmdl.size(); ++i)
    {
        std::cout << i << ": [" << cmdl[i] << "]\n";
    }
    
    cmdl("gpath") >> generate_folder;
    auto parser = reflection_parsers::ast_source_parser();

    parser.generate_reflection_files(folders, generate_folder);
    
    return 0;
}
