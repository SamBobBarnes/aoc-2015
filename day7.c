//
// Created by sb17057 on 4/9/2026.
//

#include "day7.h"
#include "Inputs/day7.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//operations
#define WIRE 0
#define AND 1
#define OR 2
#define NOT 3
#define LSHIFT 4
#define RSHIFT 5


struct Gate {
    char label[2];
    uint16_t a;
    uint16_t b;
    uint8_t operation;
    uint16_t result;
};


uint16_t process_gate(const struct Gate *gate) {
    switch (gate->operation) {
        case AND: return gate->a & gate->b;
        case OR: return gate->a | gate->b;
        case NOT: return !gate->a;
        case LSHIFT: return gate->a << gate->b;
        case RSHIFT: return gate->a >> gate->b;
        default: return gate->a;
    }
}

void day7_part1() {
    print_header(7, 1);
    const char *input = day7_input.test_input;
    const size_t len = strlen(input);

    int gate_count = 0;
    for (int i = 0; i < len; i++)
        if (input[i] == '\n') gate_count++;

    struct Gate gates[gate_count];

    char line[5][6];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            line[i][j] = '\0';

    int line_word = 0;
    int word_char = 0;
    int gate_i = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == ' ') {
            word_char = 0;
            line_word++;
            continue;
        }
        if (input[i] == '\n') {
            // process line
 if (strcmp(line[3], "") == 0) {
                // wire
                gates[i].label[0] = line[2][0];
                gates[i].label[1] = line[2][1];
                gates[i].operation = WIRE;
                gates[i].a = atoi(line[0]);
                gates[i].b = 0;
            } else if (strcmp(line[4], "") == 0) {
                // not
                gates[i].label[0] = line[3][0];
                gates[i].label[1] = line[3][1];
                gates[i].operation = NOT;
            } else if (strcmp(line[1], "AND") == 0) {
                // and
                gates[i].label[0] = line[4][0];
                gates[i].label[1] = line[4][1];
                gates[i].operation = AND;
            } else if (strcmp(line[1], "OR") == 0) {
                // or
                gates[i].label[0] = line[4][0];
                gates[i].label[1] = line[4][1];
                gates[i].operation = OR;
            } else if (strcmp(line[1], "LSHIFT") == 0) {
                // lshift
                gates[i].label[0] = line[4][0];
                gates[i].label[1] = line[4][1];
                gates[i].operation = LSHIFT;
            } else if (strcmp(line[1], "RSHIFT") == 0) {
                // rshift
                gates[i].label[0] = line[4][0];
                gates[i].label[1] = line[4][1];
                gates[i].operation = RSHIFT;
            }

            gates[i].result = process_gate(&gates[i]);

            gate_i++;
            line_word = 0;
            word_char = 0;
            continue;
        }
        line[line_word][word_char] = input[i];
        word_char++;
    }
}

void day7_part2() {
    print_header(7, 2);
    const char *input = day7_input.test_input;
    const size_t len = strlen(input);
}

IDay day7 = {
    .part1 = day7_part1,
    .part2 = day7_part2
};
