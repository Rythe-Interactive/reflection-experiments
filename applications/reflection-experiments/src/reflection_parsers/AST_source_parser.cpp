#include "AST_source_parser.h"

reflection_parsers::AST_source_parser::AST_source_parser() {
    index = clang_createIndex(0, 0);
}

reflection_parsers::AST_source_parser::~AST_source_parser() {
    
}

void reflection_parsers::AST_source_parser::parse_source_folders(const std::unordered_set<std::string> &folders) {
    index = clang_createIndex(0, 0);

    for (auto folder : folders) {
        
        rsl::dynamic_string string = rsl::dynamic_string::from_buffer(folder.c_str(), folder.size());
        
        for (const auto& entry : std::filesystem::recursive_directory_iterator(string.data())) {
            if (!entry.is_regular_file()) continue;
            
            std::filesystem::path path = entry.path();
            if (path.extension() == ".hpp" || path.extension() == ".h") {
                AST_parse_file(path.string().c_str(), index);
                }
        }
    }
}

void reflection_parsers::AST_source_parser::AST_parse_file(const std::string filePath, CXIndex index) {
    
    CXTranslationUnit unit = clang_parseTranslationUnit(
          index,
          filePath.c_str(), nullptr, 0,
          nullptr, 0,
          CXTranslationUnit_None); 
    
    if (unit == nullptr){
        std::cerr << "Unable to parse translation unit. Quitting.\n";
        return;
    }
    CXCursor cursor = clang_getTranslationUnitCursor(unit); //Obtain a cursor at the root of the translation unit

    visitor_context context = {.self = this, .depth = 0};
    
    clang_visitChildren(
      cursor, //Root cursor
      visitor_callback_wrapper, //CXCursorVisitor: a function pointer
      &context //client_data
      );
}

CXChildVisitResult reflection_parsers::AST_source_parser::visitor(
    CXCursor current_cursor,
    CXCursor parent,
    CXClientData client_data) {

    auto* data = static_cast<visitor_context*>(client_data);

    CXString current_display_name = clang_getCursorDisplayName(current_cursor);
    const char* char_display_name = clang_getCString(current_display_name);
    if (strcmp(char_display_name, "")) {
        for (int i = 0; i < data->depth; i++) std::cout << "  ";
        std::cout << "Visiting element: " << char_display_name << "\n";
        
        if (parent.kind == CXCursor_FunctionDecl) {}
        
        if (current_cursor.kind == CXCursor_FieldDecl) {
            
        
            
            
        }
        
        clang_disposeString(current_display_name);
        visitor_context child{.self = data->self, .depth = data->depth + 1 };
        
        clang_visitChildren(
            current_cursor,
            visitor_callback_wrapper,
            &child);
    }
    return CXChildVisit_Continue;
}

CXChildVisitResult reflection_parsers::AST_source_parser::visitor_callback_wrapper(
    CXCursor cursor,
    CXCursor parent,
    CXClientData client_data) {
    
    auto self = static_cast<reflection_parsers::AST_source_parser*>(client_data);
    return self->visitor(cursor, parent, client_data);
}

rythe::reflection_containers::reflected_variable reflection_parsers::AST_source_parser::extract_variable(CXCursor cursor) {
    
    CXString field_name = clang_getCursorSpelling(cursor);

    CXCursor parent = clang_getCursorSemanticParent(cursor);
    CXString parentName = clang_getCursorSpelling(parent);
    
    reflection_properties::acess_modifier access;
    switch (clang_getCXXAccessSpecifier(cursor)) {
    case CX_CXXPublic:
        access = reflection_properties::acess_modifier::public_access;
        break;
    case CX_CXXProtected:
        access = reflection_properties::acess_modifier::protected_access;
        break;
    case CX_CXXPrivate:
        access = reflection_properties::acess_modifier::private_access;
        break;
    case CX_CXXInvalidAccessSpecifier:
        // Debug something bad
        break;
    default:
        break;
    }
    
    CXType type = clang_getCursorType(cursor);
    CXString type_spelling = clang_getTypeSpelling(type);

    bool is_const = clang_isConstQualifiedType(type);

    // Not sure how to do that yet
    bool is_static = true;
    
    bool is_array = false;
    int array_size = 0;
    
    if (type.kind == CXType_ConstantArray) {
        is_array = true;
        array_size = static_cast<int>(clang_getArraySize(type));
    }

    size_t size = clang_Type_getSizeOf(type);
    size_t align = clang_Type_getAlignOf(type);

    int offset = (int)clang_Cursor_getOffsetOfField(cursor);

    rsl::dynamic_array<rsl::dynamic_string> attributes;

    const char* field_cstr = clang_getCString(field_name);
    const char* parent_cstr = clang_getCString(parentName);
    
    return rythe::reflection_containers::reflected_variable<int>(
        rsl::hashed_string::from_buffer(
            field_cstr,
            strlen(clang_getCString(field_name))),
        rsl::dynamic_string::from_buffer(
            parent_cstr,
            strlen(clang_getCString(parentName))),
        access,
        is_static,
        is_const,
        is_array,
        array_size,
        offset,
        reflection_id(
            rsl::dynamic_string::from_buffer(
                field_cstr,
                strlen(clang_getCString(field_name)))),
        attributes);
}





