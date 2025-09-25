#include "compile_reflected_file.h"

compile_reflected_file::compile_reflected_file(const rsl::dynamic_string source_location)
    : name(source_location)
  , source_location(source_location) {}

compile_reflected_file::~compile_reflected_file() {}
