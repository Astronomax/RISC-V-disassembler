#ifndef LAB_03_RV32_H
#define LAB_03_RV32_H

#include <cstdio>
#include <cstdint>
#include <utility>
#include <string>
#include <vector>

typedef std::vector<std::pair<uint8_t, uint8_t>> RV32_arg;

uint32_t extract_arg(const RV32_arg &arg, const uint32_t &mask) {
    uint32_t result = 0;
    for (auto &[pos1, pos2]: arg)
        if(mask & (1u << pos1))
            result |= (1u << pos2);
    return result;
}

std::vector<RV32_arg> simm = {{{12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18},
                          {19, 19}, {20, 20}, {21, 21}, {22, 22}, {23, 23}, {24, 24}, {25, 25},
                          {26, 26}, {27, 27}, {28, 28}, {29, 29}, {30, 30}, {31, 31}}, //simm[31:12]
                         {{12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}, {17, 17}, {18, 18},
                          {19, 19}, {20, 11}, {21, 1}, {22, 2}, {23, 3}, {24, 4}, {25, 5},
                          {26, 6}, {27, 7}, {28, 8}, {29, 9}, {30, 10}, {31, 20}}, //simm[20|10:1|11|19:12]
                         {{7,  11}, {8,  1}, {9,  2}, {10, 3}, {11, 4}, {25, 5}, {26, 6},
                          {27, 7}, {28, 8}, {29, 9}, {30, 10}, {31, 12}}, //simm[4:1|11] simm[12|10:5]
                         {{20, 0}, {21, 1}, {22, 2}, {23, 3}, {24, 4}, {25, 5},
                          {26, 6}, {27, 7}, {28, 8}, {29, 9}, {30, 10}, {31, 11}}, //simm[11:0]
                         {{7,  0}, {8,  1}, {9,  2}, {10, 3}, {11, 4}, {25, 5}, {26, 6},
                          {27, 7}, {28, 8}, {29, 9}, {30, 10}, {31, 11}}}; //simm[4:0] simm[11:5]
RV32_arg rs1 = {{{15, 0}, {16, 1}, {17, 2}, {18, 3}, {19, 4}}};
RV32_arg rs2 = {{{20, 0}, {21, 1}, {22, 2}, {23, 3}, {24, 4}}};
RV32_arg rd = {{{7, 0}, {8, 1}, {9, 2}, {10, 3}, {11, 4}}};
RV32_arg shamt = {{{20, 0}, {21, 1}, {22, 2}, {23, 3}, {24, 4}}};

struct RV32_word {
    std::string word_name;
    uint32_t mask, opcode;
    std::vector<RV32_arg> args;
};

RV32_word instructions[45] = {
    {"lui", 127, 55, {rd, simm[0]}},
    {"auipc", 127, 23, {rd, simm[0]}},
    {"jal", 127, 111, {rd, simm[1]}},
    {"jalr", 28799, 103, {rd, rs1, simm[3]}},
    {"beq", 28799, 99, {rs1, rs2, simm[2]}},
    {"bne", 28799, 4195, {rs1, rs2, simm[2]}},
    {"blt", 28799, 16483, {rs1, rs2, simm[2]}},
    {"bge", 28799, 20579, {rs1, rs2, simm[2]}},
    {"bltu", 28799, 24675, {rs1, rs2, simm[2]}},
    {"bgeu", 28799, 28771, {rs1, rs2, simm[2]}},
    {"lb", 28799, 3, {rd, simm[3], rs1}},
    {"lh", 28799, 4099, {rd, simm[3], rs1}},
    {"lw", 28799, 8195, {rd, simm[3], rs1}},
    {"lbu", 28799, 16387, {rd, simm[3], rs1}},
    {"lhu", 28799, 20483, {rd, simm[3], rs1}},
    {"sb", 28799, 35, {rs2, simm[4], rs1}},
    {"sh", 28799, 4131, {rs2, simm[4], rs1}},
    {"sw", 28799, 8227, {rs2, simm[4], rs1}},
    {"addi", 28799, 19, {rd, rs1, simm[3]}},
    {"slti", 28799, 8211, {rd, rs1, simm[3]}},
    {"sltiu", 28799, 12307, {rd, rs1, simm[3]}},
    {"xori", 28799, 16403, {rd, rs1, simm[3]}},
    {"ori", 28799, 24595, {rd, rs1, simm[3]}},
    {"andi", 28799, 28691, {rd, rs1, simm[3]}},
    {"slli", 4261441663, 4115, {rd, rs1, shamt}},
    {"srli", 4261441663, 20499, {rd, rs1, shamt}},
    {"srai", 4261441663, 1073762323, {rd, rs1, shamt}},
    {"add", 4261441663, 51, {rd, rs1, rs2}},
    {"sub", 4261441663, 1073741875, {rd, rs1, rs2}},
    {"sll", 4261441663, 4147, {rd, rs1, rs2}},
    {"slt", 4261441663, 8243, {rd, rs1, rs2}},
    {"sltu", 4261441663, 12339, {rd, rs1, rs2}},
    {"xor", 4261441663, 16435, {rd, rs1, rs2}},
    {"srl", 4261441663, 20531, {rd, rs1, rs2}},
    {"sra", 4261441663, 1073762355, {rd, rs1, rs2}},
    {"or", 4261441663, 24627, {rd, rs1, rs2}},
    {"and", 4261441663, 28723, {rd, rs1, rs2}},
    {"mul", 4261441663, 33554483, {rd, rs1, rs2}},
    {"mulh", 4261441663, 33558579, {rd, rs1, rs2}},
    {"mulhsu", 4261441663, 33562675, {rd, rs1, rs2}},
    {"mulhu", 4261441663, 33566771, {rd, rs1, rs2}},
    {"div", 4261441663, 33570867, {rd, rs1, rs2}},
    {"divu", 4261441663, 33574963, {rd, rs1, rs2}},
    {"rem", 4261441663, 33579059, {rd, rs1, rs2}},
    {"remu", 4261441663, 33583155, {rd, rs1, rs2}}
};

#endif //LAB_03_RV32_H