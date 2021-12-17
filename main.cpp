#include "elf_parser.h"
#include "rv32_print.h"
#include "fsymtab_print.h"

std::string find_mark(const std::vector<Parser::symbol> &symtab, uint32_t address) {
    for (auto it = symtab.rbegin(); it != symtab.rend(); ++it)
        if (it->symbol_value == address)
            return it->symbol_name + ":";
    return "";
}

int main(int argc, char* argv[]) {
    Parser parser(argv[1]);
    FILE* out = fopen(argv[2], "w");

    std::vector<Parser::section> sections = parser.get_sections();
    Parser::section text_section = parser.find_section(sections, ".text");
    Parser::section symtable_section = parser.find_section(sections, ".symtab");
    std::vector<Parser::symbol> symtab = parser.get_symbols();

    uint32_t address = ((Elf32_Ehdr *) (parser.memory_pointer))->e_entry;
    uint16_t* beg_itr = (uint16_t*)parser.memory_pointer + text_section.section_offset / 2;
    uint16_t* end_itr = beg_itr + (text_section.section_size / 2);

    while (beg_itr != end_itr) {
        if ((*(beg_itr) & 3u) == 3u) {
            uint32_t block = *(beg_itr++) | (*(beg_itr++) << 16u);
            std::string mrk = find_mark(symtab, address);
            fprintf(out, "%08x %10s ", address, mrk.c_str());
            for (auto &[instr, instr_print] : rv32_print)
                if ((block & instr.mask) == instr.opcode)
                    instr_print(out, instr, block);
            fprintf(out, "\n");
            address += 4;
        } else {
            printf("unknown command\n");
            address += 2;
        }
    }
    fprintf(out, "\n");
    fprint_symtab(out, symtab);
    fclose(out);
    return 0;
}