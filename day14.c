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

typedef struct {
    char name[10];
    int speed;
    int flight_time;
    int rest_time;
} Reindeer;

int get_current_dist(const Reindeer *reindeer, const int sec) {
    const int cycle_time = reindeer->flight_time + reindeer->rest_time;
    int cycles_completed = sec / cycle_time;
    int remaining_seconds = sec % cycle_time;
    if (remaining_seconds > reindeer->flight_time) {
        remaining_seconds = 0;
        cycles_completed++;
    }
    const int total_dist = cycles_completed * reindeer->flight_time * reindeer->speed + remaining_seconds * reindeer->
                           speed;
    return total_dist;
}

void day14_part2() {
    print_header(14, 2);
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
    Reindeer reindeer[row_count];
    int distances[row_count];
    int scores[row_count];

#pragma region Divide rows into data
    for (int i = 0; i < row_count; i++) {
        strcpy(reindeer[i].name, strtok(rows[i], " "));
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        reindeer[i].speed = atoi(strtok(nullptr, " "));
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        reindeer[i].flight_time = atoi(strtok(nullptr, " "));
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        strtok(nullptr, " ");
        reindeer[i].rest_time = atoi(strtok(nullptr, " "));
        distances[i] = 0;
        scores[i] = 0;
    }
#pragma endregion
    for (int sec = 1; sec <= seconds; sec++) {
        int max_dist = 0;
        for (int i = 0; i < row_count; i++) {
            distances[i] = get_current_dist(&reindeer[i], sec);
        }
        for (int i = 0; i < row_count; i++) {
            if (distances[i] > max_dist) {
                max_dist = distances[i];
            }
        }
        for (int i = 0; i < row_count; i++) {
            if (distances[i] == max_dist) {
                scores[i]++;
            }
        }
        // for (int i = 0; i < row_count; i++) {
        //     debug_ln("%s has %i points after %i seconds; d: %i", reindeer[i].name, scores[i], sec, distances[i]);
        // }
    }
    for (int i = 0; i < row_count; i++) {
        if (max < scores[i]) max = scores[i];
        debug_ln("%s has %i points after %i seconds", reindeer[i].name, scores[i], seconds);
    }

    printf("the high score is %i", max);
}

IDay day14 = {
    .part1 = day14_part1,
    .part2 = day14_part2
};
