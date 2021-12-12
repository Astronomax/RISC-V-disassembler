#include "elf_parser.h"
#include "rv32_print.h"
#include "fsymtab_print.h"

int main(int argc, char* argv[]) {
    Parser parser(argv[1]);
    FILE* out = fopen(argv[2], "w");

    auto sections = parser.get_sections();
    auto text_section = parser.find_section(sections, ".text");
    auto symtable_section = parser.find_section(sections, ".symtab");
    auto symtab = parser.get_symbols();

    uint32_t address = ((Elf32_Ehdr *) (parser.memory_pointer))->e_entry;
    uint16_t* beg_itr = (uint16_t*)parser.memory_pointer + text_section.section_offset / 2;
    uint16_t* end_itr = beg_itr + (text_section.section_size / 2);

    while (beg_itr != end_itr) {
        if ((*(beg_itr) & 3u) == 3u) {
            fprintf(out, "%08x          ", address);
            uint32_t row = *(beg_itr++) | (*(beg_itr++) << 16u);

            for (auto &[instruction, _print] : rv32_print) {
                if ((row & instruction.mask) == instruction.opcode) {
                    _print(out, instruction, row);
                    break;
                }
            }
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