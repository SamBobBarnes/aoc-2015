//
// Created by sb17057 on 4/9/2026.
//

#include "day9.h"
#include "Inputs/day9.h"

#include <string.h>

struct Route {
    char *src;
    char *dest;
    int dist;
};

void day9_part1() {
    print_header(9, 1);
    const char *input = day9_input.test_input;
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

    struct Route routes[row_count];

    for (int i = 0; i < row_count; i++) {
        char *ptr = strtok(rows[i], " ");
        int j = 0;
        while (ptr != NULL) {
            if (j == 0)
                routes[i].src = ptr;
            else if (j == 2)
                routes[i].dest = ptr;
            else if (j == 4)
                routes[i].dist = atoi(ptr);
            ptr = strtok(nullptr, " ");
            j++;
        }
    }

    for (int i = 0; i < row_count; i++)
        printf("%s\n%s -- %i -> %s\n", rows[i], routes[i].src, routes[i].dist, routes[i].dest);
    // use Dijkstra
}

void day9_part2() {
    print_header(9, 2);
    const char *input = day9_input.test_input;
    const size_t len = strlen(input);
}

IDay day9 = {
    .part1 = day9_part1,
    .part2 = day9_part2
};
