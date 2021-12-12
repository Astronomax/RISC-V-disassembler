#include "fsymtab_print.h"

void fprint_symtab(FILE* f, const std::vector<Parser::symbol> &symbols) {
    fprintf(f, "Symbol Value              Size Type     Bind     Vis       Index Name\n");
    for (auto &symbol: symbols) {
        fprintf(f, "[%4i] 0x%-15lx %5i %-8s %-8s %-8s %6s %s\n", symbol.symbol_num,
               symbol.symbol_value,
               symbol.symbol_size,
               symbol.symbol_type.c_str(),
               symbol.symbol_bind.c_str(),
               symbol.symbol_visibility.c_str(),
               symbol.symbol_index.c_str(),
               symbol.symbol_name.c_str());
    }
}