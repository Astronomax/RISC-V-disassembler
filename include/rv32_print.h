#ifndef LAB_03_RV32_PRINT_H
#define LAB_03_RV32_PRINT_H
#include <cstdio>
#include <functional>
#include "rv32.h"

namespace rv32_printers {
    std::string registers[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
                                 "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
                                 "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
                                 "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

    std::function<void(FILE*, const RV32_word &, uint32_t)> print_0 = [](FILE* f, const RV32_word &word, uint32_t bits) {
        uint32_t arg0 = extract_arg(word.args[0], bits);
        int32_t arg1 = extract_arg(word.args[1], bits);
        if (arg1 & 2048) arg1 -= 4096;
        fprintf(f,"%s %s, %d", word.word_name.c_str(), registers[arg0].c_str(), arg1);
    };

    std::function<void(FILE*, const RV32_word &, uint32_t)> print_1 = [](FILE* f, const RV32_word &word, uint32_t bits) {
        uint32_t arg0 = extract_arg(word.args[0], bits);
        int32_t arg1 = (int32_t) extract_arg(word.args[1], bits);
        if (arg1 & 2048) arg1 -= 4096;
        uint32_t arg2 = extract_arg(word.args[2], bits);
        fprintf(f, "%s %s, %d(%s)", word.word_name.c_str(), registers[arg0].c_str(), arg1, registers[arg2].c_str());
    };

    std::function<void(FILE*, const RV32_word &, uint32_t)> print_2 = [](FILE* f, const RV32_word &word, uint32_t bits) {
        uint32_t arg0 = extract_arg(word.args[0], bits);
        uint32_t arg1 = extract_arg(word.args[1], bits);
        int32_t arg2 = extract_arg(word.args[2], bits);
        if (arg2 & 2048) arg2 -= 4096;
        fprintf(f, "%s %s, %s, %d", word.word_name.c_str(), registers[arg0].c_str(), registers[arg1].c_str(), arg2);
    };

    std::function<void(FILE*, const RV32_word &, uint32_t)> print_3 = [](FILE* f, const RV32_word &word, uint32_t bits) {
        uint32_t arg0 = extract_arg(word.args[0], bits);
        uint32_t arg1 = extract_arg(word.args[1], bits);
        uint32_t arg2 = extract_arg(word.args[2], bits);
        fprintf(f, "%s %s, %s, %s", word.word_name.c_str(), registers[arg0].c_str(), registers[arg1].c_str(), registers[arg2].c_str());
    };
};

std::pair<RV32_word, std::function<void(FILE*, const RV32_word&, uint32_t)>> rv32_print[45] = {
          {instructions[0], rv32_printers::print_0 },  //       "lui"
          {instructions[1], rv32_printers::print_0 },  //       "auipc"
          {instructions[2], rv32_printers::print_0 },  //       "jal"
          {instructions[3], rv32_printers::print_2 },  //       "jalr"
          {instructions[4], rv32_printers::print_2 },  //       "beq"
          {instructions[5], rv32_printers::print_2 },  //       "bne"
          {instructions[6], rv32_printers::print_2 },  //       "blt"
          {instructions[7], rv32_printers::print_2 },  //       "bge"
          {instructions[8], rv32_printers::print_2 },  //       "bltu"
          {instructions[9], rv32_printers::print_0 },  //       "bgeu"
          {instructions[10], rv32_printers::print_1 }, //       "lb"
          {instructions[11], rv32_printers::print_1 }, //       "lh"
          {instructions[12], rv32_printers::print_1 }, //       "lw"
          {instructions[13], rv32_printers::print_1 }, //       "lbu"
          {instructions[14], rv32_printers::print_1 }, //       "lhu"
          {instructions[15], rv32_printers::print_1 }, //       "sb"
          {instructions[16], rv32_printers::print_1 }, //       "sh"
          {instructions[17], rv32_printers::print_1 }, //       "sw"
          {instructions[18], rv32_printers::print_2 }, //       "addi"
          {instructions[19], rv32_printers::print_2 }, //       "slti"
          {instructions[20], rv32_printers::print_2 }, //       "sltiu"
          {instructions[21], rv32_printers::print_2 }, //       "xori"
          {instructions[22], rv32_printers::print_2 }, //       "ori"
          {instructions[23], rv32_printers::print_2 }, //       "andi"
          {instructions[24], rv32_printers::print_2 }, //       "slli"
          {instructions[25], rv32_printers::print_2 }, //       "srli"
          {instructions[26], rv32_printers::print_2 }, //       "srai"
          {instructions[27], rv32_printers::print_3 }, //       "add"
          {instructions[28], rv32_printers::print_3 }, //       "sub"
          {instructions[29], rv32_printers::print_3 }, //       "sll"
          {instructions[30], rv32_printers::print_3 }, //       "slt"
          {instructions[31], rv32_printers::print_3 }, //       "sltu"
          {instructions[32], rv32_printers::print_3 }, //       "xor"
          {instructions[33], rv32_printers::print_3 }, //       "srl"
          {instructions[34], rv32_printers::print_3 }, //       "sra"
          {instructions[35], rv32_printers::print_3 }, //       "or"
          {instructions[36], rv32_printers::print_3 }, //       "and"
          {instructions[37], rv32_printers::print_3 }, //       "mul"
          {instructions[38], rv32_printers::print_3 }, //       "mulh"
          {instructions[39], rv32_printers::print_3 }, //       "mulhsu"
          {instructions[40], rv32_printers::print_3 }, //       "mulhu"
          {instructions[41], rv32_printers::print_3 }, //       "div"
          {instructions[42], rv32_printers::print_3 }, //       "divu"
          {instructions[43], rv32_printers::print_3 }, //       "rem"
          {instructions[44], rv32_printers::print_3 }  //       "remu"
};

#endif //LAB_03_RV32_PRINT_H
