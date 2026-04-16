//
// Created by sb17057 on 4/9/2026.
//

#include "day14.h"
#include "Inputs/day14.h"

#include <string.h>

#include "debug.h"

void day14_part1() {
    print_header(14, 1);
    const char *input = day14_input.input;

#pragma region Split Input into rows
    size_t len = strlen(input);
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

    int max = 0;
    // int seconds = 1000;
    int seconds = 2503;

#pragma region Divide rows into data
    for (int i = 0; i < row_count; i++) {
        char *name = strtok(rows[i], " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        int speed = atoi(strtok(nullptr, " "));
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        int flight_time = atoi(strtok(nullptr, " "));
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        int rest_time = atoi(strtok(nullptr, " "));
        int cycle_time = flight_time + rest_time;
        int cycles_completed = seconds / cycle_time;
        int remaining_seconds = seconds % cycle_time;
        if (remaining_seconds > flight_time) {
            remaining_seconds = 0;
            cycles_completed++;
        }
        int total_dist = cycles_completed * flight_time * speed + remaining_seconds * speed;

        debug_ln("%s went %i km. (s: %i, ft: %i, rt: %i, ct %i, cc: %i, rs: %i", name, total_dist, speed, flight_time,
                 rest_time, cycle_time, cycles_completed, remaining_seconds);
        if (max < total_dist) max = total_dist;
    }
#pragma endregion

    printf("the fastest reindeer traveled %i km", max);
}

void day14_part2() {
    print_header(14, 2);
    const char *input = day14_input.test_input;
    const size_t len = strlen(input);
}

IDay day14 = {
    .part1 = day14_part1,
    .part2 = day14_part2
};
