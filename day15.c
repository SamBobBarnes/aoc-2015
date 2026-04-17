//
// Created by sb17057 on 4/9/2026.
//

#include "day15.h"
#include "Inputs/day15.h"

#include <string.h>

typedef struct {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
    char *name;
} Ingredient;

void day15_part1() {
    print_header(15, 1);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);

    int row_count = 0;
#pragma region Split Input into rows
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

    Ingredient ingredients[row_count];

    for (int i = 0; i < row_count; i++) {
        char *name = strtok(rows[i], " ");
        size_t name_len = strlen(name);
        name[name_len-1] = '\0';
        ingredients[i].name = name;
        strtok(nullptr, " ");
        char *capacity = strtok(nullptr, " ");
        size_t capacity_len = strlen(capacity);
        capacity[capacity_len-1] = '\0';
        ingredients[i].capacity = atoi(capacity);
        strtok(nullptr, " ");
        char *durability = strtok(nullptr, " ");
        size_t durability_len = strlen(capacity);
        durability[durability_len-1] = '\0';
        ingredients[i].durability = atoi(durability);
        strtok(nullptr, " ");
        char *flavor = strtok(nullptr, " ");
        size_t flavor_len = strlen(capacity);
        flavor[flavor_len-1] = '\0';
        ingredients[i].flavor = atoi(flavor);
        strtok(nullptr, " ");
        char *texture = strtok(nullptr, " ");
        size_t texture_len = strlen(capacity);
        texture[texture_len-1] = '\0';
        ingredients[i].texture = atoi(texture);
        strtok(nullptr, " ");
        ingredients[i].calories = atoi(strtok(nullptr, " "));
    }


}

void day15_part2() {
    print_header(15, 2);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);
}

IDay day15 = {
    .part1 = day15_part1,
    .part2 = day15_part2
};
