//
// Created by sb17057 on 4/9/2026.
//

#include "day13.h"
#include "Inputs/day13.h"

#include <string.h>

#include "debug.h"


typedef struct {
    int id;
    int happiness;
    int neighbor;
} HappinessModifier;


int index_of_person(char arr[][20], const size_t len, const char *string_to_find) {
    for (int i = 0; i < len; i++) {
        if (strcmp(arr[i], string_to_find) == 0) return i;
    }

    return -1;
}

int calc_happiness(const int *table, const int table_len, const HappinessModifier *modifiers, const int modifier_len) {
    int happiness = 0;
    for (int i = 0; i < table_len; i++) {
        const int *z;
        if (i == 0) z = &table[table_len - 1];
        else z = &table[i - 1];
        const int *a = &table[i];
        const int *b;
        if (i == table_len - 1) b = &table[0];
        else b = &table[i + 1];

        for (int j = 0; j < modifier_len; j++) {
            if (modifiers[j].id == *a && modifiers[j].neighbor == *b || modifiers[j].id == *a && modifiers[j].neighbor
                == *z) {
                happiness += modifiers[j].happiness;
            }
        }
    }
    return happiness;
}

bool id_in_table(const int *table, const int table_len, const int id) {
    for (int i = 0; i < table_len; i++) {
        if (table[i] == id) return true;
    }
    return false;
}

int recurse_table_placements(int *table, const int table_index, const int table_len, const HappinessModifier *modifiers,
                             const int mod_len, const int depth) {
    int max = 0;
    debug_ln("d: %i, ti: %i", depth, table_index);
    for (int i = 0; i < table_len; i++) {
        if (!id_in_table(table, table_index + 1, i)) {
            table[table_index] = i;
            int value;
            if (depth == table_len - 1) {
                if (debugging) {
                    for (int j = 0; j < table_len; j++) {
                        printf("%i, ", table[j]);
                    }
                }
                value = calc_happiness(table, table_len, modifiers, mod_len);
                if (debugging) {
                    printf("\ntotal: %i", value);
                    print_spacer();
                }
            } else {
                value = recurse_table_placements(table, table_index + 1, table_len, modifiers, mod_len, depth + 1);
            }
            if (max < value) max = value;
        }
    }
    return max;
}

void day13_part1() {
    print_header(13, 1);
    const char *input = day13_input.input;
#pragma region Split Input into rows
    const size_t len = strlen(input);
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

    char persons[row_count][20];
    int persons_len = 0;

    HappinessModifier modifiers[row_count];
    int modifier_len = 0;

#pragma region Divide rows into data
    for (int i = 0; i < row_count; i++) {
        char *ptr = strtok(rows[i], " ");
        char *a = ptr;
        int a_index = index_of_person(persons, row_count, a);
        if (a_index == -1) {
            strcpy(persons[persons_len], a);
            a_index = persons_len++;
        }
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");
        bool gain = strcmp(ptr, "gain") == 0;
        ptr = strtok(nullptr, " ");
        int happiness = atoi(ptr);
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");
        size_t b_len = strlen(ptr);
        ptr[b_len - 1] = '\0';
        char *b = ptr;
        int b_index = index_of_person(persons, row_count, b);
        if (b_index == -1) {
            strcpy(persons[persons_len], b);
            b_index = persons_len++;
        }

        modifiers[modifier_len++] = (HappinessModifier){a_index, gain ? happiness : -happiness, b_index};

        debug_ln("%s would %s %i happiness units by sitting next to %s", a, gain ? "gain" : "lose", happiness, b);
    }
#pragma endregion

    if (debugging) {
        for (int i = 0; i < modifier_len; i++) {
            debug_ln("%s(%i) would gain %i happiness units by sitting next to %s(%i)", persons[modifiers[i].id],
                     modifiers[i].id, modifiers[i].happiness, persons[modifiers[i].neighbor], modifiers[i].neighbor);
        }
        print_spacer();
    }

    int table_placements[persons_len];

    const int max_happiness = recurse_table_placements(table_placements, 0, persons_len, modifiers, modifier_len, 0);

    printf("max happiness: %i\n", max_happiness);
}

void day13_part2() {
    print_header(13, 2);
    const char *input = day13_input.test_input;
    const size_t len = strlen(input);
}

IDay day13 = {
    .part1 = day13_part1,
    .part2 = day13_part2
};
