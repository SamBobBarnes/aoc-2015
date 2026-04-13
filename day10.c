//
// Created by sb17057 on 4/9/2026.
//

#include "day10.h"
#include "Inputs/day10.h"

#include <string.h>

#include "debug.h"

void day10_part1() {
    print_header(10, 1);
    const char *input = day10_input.input;

    char prev[1000000] = {'\0'};
    char next[1000000] = {'\0'};
    strcpy(prev, input);

    int reps = 40;
    for (int r = 0; r < reps; r++) {
        size_t len = strlen(prev);
        debug("%llu\n", len);
        int run_len = 1;
        char run_char = prev[0];

        for (int i = 1; i < len; i++) {
            if (prev[i] == run_char) run_len++;
            else {
                char run_len_string[5] = {'\0'};
                itoa(run_len, run_len_string, 10);
                strcat(next, run_len_string);
                char run_char_string[2] = {run_char, '\0'};
                strcat(next, run_char_string);
                run_len = 1;
                run_char = prev[i];
            }
        }

        char run_len_string[5] = {'\0'};
        itoa(run_len, run_len_string, 10);
        strcat(next, run_len_string);
        char run_char_string[2] = {run_char, '\0'};
        strcat(next, run_char_string);
        strcpy(prev, next);
        for (int i = 0; i < strlen(next); i++) next[i] = '\0';
    }

    printf("%llu", strlen(prev));
}

void day10_part2() {
    print_header(10, 2);
    const char *input = day10_input.input;
    const size_t len = strlen(input);

    // need to compress this somehow
    char prev[2000000] = {'\0'};
    char next[2000000] = {'\0'};
    strcpy(prev, input);

    int reps = 50;
    for (int r = 0; r < reps; r++) {
        size_t len = strlen(prev);
        debug("%i - %llu\n", r, len);
        int run_len = 1;
        char run_char = prev[0];

        for (int i = 1; i < len; i++) {
            if (prev[i] == run_char) run_len++;
            else {
                char run_len_string[5] = {'\0'};
                itoa(run_len, run_len_string, 10);
                strcat(next, run_len_string);
                char run_char_string[2] = {run_char, '\0'};
                strcat(next, run_char_string);
                run_len = 1;
                run_char = prev[i];
            }
        }

        char run_len_string[5] = {'\0'};
        itoa(run_len, run_len_string, 10);
        strcat(next, run_len_string);
        char run_char_string[2] = {run_char, '\0'};
        strcat(next, run_char_string);
        strcpy(prev, next);
        for (int i = 0; i < strlen(next); i++) next[i] = '\0';
    }

    printf("%llu", strlen(prev));
}

IDay day10 = {
    .part1 = day10_part1,
    .part2 = day10_part2
};
