#ifndef LAB_03_FSYMTAB_PRINT_H
#define LAB_03_FSYMTAB_PRINT_H

#include "elf_parser.h"

void fprint_symtab(FILE* f, const std::vector<Parser::symbol> &symbols);

#endif //LAB_03_FSYMTAB_PRINT_H