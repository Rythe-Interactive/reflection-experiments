#include "compile_reflected_file.h"

#include "rsl/impl/util/source_location.hpp"

// Having source_location as USR does work, as there are no source files in AST.
compile_reflected_file::compile_reflected_file(const rsl::dynamic_string source_location) : source_location(source_location) {}

compile_reflected_file::~compile_reflected_file() {}
