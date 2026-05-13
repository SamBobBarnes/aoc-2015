//
// Created by sb17057 on 4/9/2026.
//

#include "day23.h"
#include "Inputs/day23.h"

#include <string.h>

enum Instruction {
    HLF,
    TPL,
    INC,
    JMP,
    JIE,
    JIO
};

enum Register {
    A,
    B
};

typedef struct {
    enum Instruction type;
    enum Register reg;
    int offset;
} Instruction;

enum Instruction get_instruction(char instr[4]) {
    if (strcmp(instr, "hlf") == 0) return HLF;
    if (strcmp(instr, "tpl") == 0) return TPL;
    if (strcmp(instr, "inc") == 0) return INC;
    if (strcmp(instr, "jmp") == 0) return JMP;
    if (strcmp(instr, "jie") == 0) return JIE;
    if (strcmp(instr, "jio") == 0) return JIO;
    printf("%s is not a valid opcode", instr);
    exit(1);
}

void day23_part1() {
    print_header(23, 1);
    const char *input = day23_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, row_count, max_row_size, rows);

    // two registers
    // 6 instructions
    //    hlf r - halve register
    //    tpl r - triple register
    //    inc r - increment register
    //    jmp offset - jump to current instr + offset
    //    jie r, offset - jump if even
    //    jio r, offset - jump if odd

    Instruction instructions[row_count];

    for (int i = 0; i < row_count; i++) {
        char instr[4] = "";
        char reg[2] = "";
        char offset[5] = "";
        strncpy(instr, rows[i], 3);
        instructions[i].type = get_instruction(instr);

        strncpy(reg, rows[i] + 4, 1);
        if (rows[i][4] == 'a')
            instructions[i].reg = A;
        else if (rows[i][4] == 'b')
            instructions[i].reg = B;
        else
            strcpy(offset, rows[i] + 4);


        if (rows[i][5] == ',')
            strcpy(offset, rows[i] + 7);

        if (strcmp(offset, "") != 0)
            instructions[i].offset = atoi(offset);
    }

    int regA = 0;
    int regB = 0;
    int index = 0;
    int *reg = NULL;
    while (index < row_count) {
        switch (instructions[index].reg) {
            case A:
                reg = &regA;
                break;
            case B:
                reg = &regB;
                break;
            default:
                reg = NULL;
        }
        switch (instructions[index].type) {
            case HLF:
                *reg = *reg / 2;
                break;
            case TPL:
                *reg = *reg * 3;
                break;
            case INC:
                (*reg)++;
                break;
            case JMP:
                index += instructions[index].offset;
                continue;
                break;
            case JIE:
                if (*reg % 2 == 0) {
                    index += instructions[index].offset;
                    continue;
                }
                break;
            case JIO:
                if (*reg == 1) {
                    index += instructions[index].offset;
                    continue;
                }
                break;
            default:
                printf("TILT");
                exit(1);
        }
        index++;
    }

    print_ln("Reg A: %i\nReg B: %i", regA, regB);
}

void day23_part2() {
    print_header(23, 2);
    const char *input = day23_input.test_input;
    const size_t len = strlen(input);
}

IDay day23 = {
    .part1 = day23_part1,
    .part2 = day23_part2
};
