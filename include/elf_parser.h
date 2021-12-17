#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <cinttypes>
#include <string>
#include <vector>
#include "elf_headers.h"

struct Parser {
    char *file_bytes;
    char *memory_pointer;

    struct section {
        int section_index = 0;
        intptr_t section_offset, section_addr;
        std::string section_name;
        std::string section_type;
        int section_size;
        int section_ent_size;
        int section_addr_align;
    };

    struct symbol {
        std::string symbol_index;
        intptr_t symbol_value;
        int symbol_num = 0;
        int symbol_size = 0;
        std::string symbol_type;
        std::string symbol_bind;
        std::string symbol_visibility;
        std::string symbol_name;
        std::string symbol_section;
    };

    section &find_section(std::vector<Parser::section> &sections, const std::string &name);

    Parser(const std::string& path);
    ~Parser();

    std::string get_symbol_visibility(uint8_t sym_vis);

    std::string get_section_type(int type);

    std::vector<section> get_sections();

    std::string get_symbol_type(uint8_t sym_type);

    std::string get_symbol_bind(uint8_t sym_bind);

    std::string get_symbol_index(uint16_t sym_idx);

    std::vector<symbol> get_symbols();
};

#endif //CODE_PARSER_H