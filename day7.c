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
    char label[3];
    uint16_t value;
    char a[3];
    struct Gate *a_ptr;
    char b[3];
    struct Gate *b_ptr;
    uint8_t operation;
    int result;
};

struct Gate *get_gate(const char *label, struct Gate *gates, const size_t length) {
    for (int i = 0; i < length; i++) {
        if (gates[i].label[0] == label[0] && gates[i].label[1] == label[1])
            return &gates[i];
    }
    return nullptr;
}

uint16_t process_gate(struct Gate *gate) {
    if (gate->result > -1) return gate->result;

    int value;
    switch (gate->operation) {
        case AND:
            if (gate->a_ptr == nullptr)
                value = gate->value & process_gate(gate->b_ptr);
            else
                value = process_gate(gate->a_ptr) & process_gate(gate->b_ptr);
            break;
        case OR: value = process_gate(gate->a_ptr) | process_gate(gate->b_ptr);
            break;
        case NOT: value = ~process_gate(gate->a_ptr);
            break;
        case LSHIFT: value = process_gate(gate->a_ptr) << gate->value;
            break;
        case RSHIFT: value = process_gate(gate->a_ptr) >> gate->value;
            break;
        default:
            if (gate->a_ptr != nullptr)
                value = process_gate(gate->a_ptr);
            else
                value = gate->value;
    }

    gate->result = value;
    return value;
}

bool is_num(const char c) {
    return c >= 48 && c <= 57;
}

void day7_part1() {
    print_header(7, 1);
    const char *input = day7_input.input;
    const size_t len = strlen(input);

#pragma region Gate Init
    int gate_count = 0;
    for (int i = 0; i < len; i++)
        if (input[i] == '\n') gate_count++;

    struct Gate gates[gate_count];

    for (int i = 0; i < gate_count; i++) {
        gates[i].label[0] = '\0';
        gates[i].label[1] = '\0';
        gates[i].label[2] = '\0';
        gates[i].a[0] = '\0';
        gates[i].a[1] = '\0';
        gates[i].a[2] = '\0';
        gates[i].a_ptr = nullptr;
        gates[i].b[0] = '\0';
        gates[i].b[1] = '\0';
        gates[i].b[2] = '\0';
        gates[i].b_ptr = nullptr;
        gates[i].operation = 0;
        gates[i].value = 0;
        gates[i].result = -1;
    }
#pragma endregion

#pragma region Split Input into rows
    int row_count = 0;
    int max_row_size = 0;
    int index_of_last_newline = -1;
    for (int i = 0; i < len; i++)
        if (input[i] == '\n') {
            row_count++;
            int row_len = i - index_of_last_newline;
            if (row_len > max_row_size) max_row_size = row_len;
            index_of_last_newline = i;
        }
    if (input[len - 1] != '\n') row_count++;
    char rows[row_count][max_row_size];
    int row_lengths[row_count];
    int current_row = 0;
    int row_index = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\n') {
            rows[current_row][row_index] = '\0';
            row_lengths[current_row] = row_index;
            row_index = 0;
            current_row++;
            continue;
        }
        rows[current_row][row_index] = input[i];
        row_index++;
    }
    if (input[len - 1] != '\n') {
        rows[current_row][row_index] = '\0';
        row_lengths[current_row] = row_index;
    }
#pragma endregion

#pragma region Assign values to gates
    for (int i = 0; i < row_count; i++) {
        char line[5][7];
        int line_word = 0;
        int word_char = 0;

        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 7; k++)
                line[j][k] = '\0';

        for (int j = 0; j < row_lengths[i]; j++) {
            const char current_char = rows[i][j];
            if (current_char == ' ') {
                line_word++;
                word_char = 0;
                continue;
            }
            line[line_word][word_char] = current_char;
            word_char++;
        }

        if (strcmp(line[1], "->") == 0) {
            // wire
            gates[i].label[0] = line[2][0];
            gates[i].label[1] = line[2][1];
            gates[i].operation = WIRE;
            if (is_num(line[0][0])) // has value
                gates[i].value = atoi(line[0]);
            else {
                gates[i].a[0] = line[0][0];
                gates[i].a[1] = line[0][1];
            }
        } else if (strcmp(line[0], "NOT") == 0) {
            // not
            gates[i].label[0] = line[3][0];
            gates[i].label[1] = line[3][1];
            gates[i].operation = NOT;
            gates[i].a[0] = line[1][0];
            gates[i].a[1] = line[1][1];
        } else if (strcmp(line[1], "AND") == 0) {
            // and
            gates[i].label[0] = line[4][0];
            gates[i].label[1] = line[4][1];
            gates[i].operation = AND;
            if (is_num(line[0][0])) // has value
                gates[i].value = atoi(line[0]);
            else {
                gates[i].a[0] = line[0][0];
                gates[i].a[1] = line[0][1];
            }
            gates[i].b[0] = line[2][0];
            gates[i].b[1] = line[2][1];
        } else if (strcmp(line[1], "OR") == 0) {
            // or
            gates[i].label[0] = line[4][0];
            gates[i].label[1] = line[4][1];
            gates[i].operation = OR;
            gates[i].a[0] = line[0][0];
            gates[i].a[1] = line[0][1];
            gates[i].b[0] = line[2][0];
            gates[i].b[1] = line[2][1];
        } else if (strcmp(line[1], "LSHIFT") == 0) {
            // lshift
            gates[i].label[0] = line[4][0];
            gates[i].label[1] = line[4][1];
            gates[i].operation = LSHIFT;
            gates[i].a[0] = line[0][0];
            gates[i].a[1] = line[0][1];
            gates[i].value = atoi(line[2]);
        } else if (strcmp(line[1], "RSHIFT") == 0) {
            // rshift
            gates[i].label[0] = line[4][0];
            gates[i].label[1] = line[4][1];
            gates[i].operation = RSHIFT;
            gates[i].a[0] = line[0][0];
            gates[i].a[1] = line[0][1];
            gates[i].value = atoi(line[2]);
        }
    }
#pragma endregion

#pragma region Link gates
    for (int i = 0; i < gate_count; i++) {
        struct Gate *gate = &gates[i];

        if (strcmp(gate->a, "") != 0)
            gate->a_ptr = get_gate(gate->a, gates, gate_count);

        if (strcmp(gate->b, "") != 0)
            gate->b_ptr = get_gate(gate->b, gates, gate_count);
    }
#pragma endregion

    // printf("The value of d = %i\n", process_gate(&gates[2]));
    // printf("The value of e = %i\n", process_gate(&gates[3]));
    // printf("The value of f = %i\n", process_gate(&gates[4]));
    // printf("The value of g = %i\n", process_gate(&gates[5]));
    // printf("The value of h = %i\n", process_gate(&gates[6]));
    // printf("The value of i = %i\n", process_gate(&gates[7]));
    struct Gate *a = get_gate("a", gates, gate_count);
    printf("The value of a = %i\n", process_gate(a));
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
