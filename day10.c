//
// Created by sb17057 on 4/9/2026.
//

#include "day10.h"
#include "Inputs/day10.h"

#include <stdint.h>
#include <string.h>

#include "debug.h"

typedef struct {
    uint8_t count;
    char number;
} Run;

#define RUN_ARRAY_LEN 5000000

void print_run(const Run *r) {
    printf("(c: %i, n: %c, s: '", r->count, r->number);
    for (int i = 0; i < r->count; i++) {
        printf("%c", r->number);
    }
    printf("')\n");
}

void decode_run(const Run *r, char string[3]) {
    sprintf(string, "%d%c", r->count, r->number);
}

int encode_run(Run *r, const char string[2]) {
    if (string[0] == string[1]) {
        r->number = string[0];
        r->count = 2;
        return 1;
    }

    r[0].number = string[0];
    r[0].count = 1;
    r[1].number = string[1];
    r[1].count = 1;
    return 2;
}

void copy_next_back(Run *prev, int *prev_len, const Run *next, int *next_len) {
    for (int i = 0; i < *next_len; i++) {
        prev[i].number = next[i].number;
        prev[i].count = next[i].count;
    }
    *prev_len = *next_len;
    *next_len = 0;
}

void reduce_runs(Run *prev, int *prev_len, Run *next, int *next_len) {
    copy_next_back(prev, prev_len, next, next_len);
    int next_i = 0;
    for (int i = 0; i < *prev_len - 1; i++) {
        if (prev[i].number == prev[i + 1].number) {
            next[next_i].number = prev[i].number;
            next[next_i++].count = prev[i].count + prev[i + 1].count;
            i++;
        } else {
            next[next_i].number = prev[i].number;
            next[next_i++].count = prev[i].count;
        }
    }

    //catch last if it was not reduced
    if (prev[*prev_len - 1].number != prev[*prev_len - 2].number) {
        next[next_i].number = prev[*prev_len - 1].number;
        next[next_i++].count = prev[*prev_len - 1].count;
    }
    *next_len = next_i;
}

int sum_runs(const Run *prev, const int prev_len) {
    int total = 0;
    for (int i = 0; i < prev_len; i++)
        total += prev[i].count;
    return total;
}

size_t calculate(const char *input, const int reps) {
    Run *prev = malloc(RUN_ARRAY_LEN * 2);
    prev[0] = (Run){1, input[0]};
    int prev_len = 1;
    int prev_i = 0;

    const size_t len = strlen(input);
    for (int i = 1; i < len; i++) {
        if (prev[prev_i].number == input[i]) prev[prev_i].count++;
        else {
            prev[++prev_i].number = input[i];
            prev[prev_i].count = 1;
            prev_len++;
        }
    }
    if (debugging)
        for (int i = 0; i < prev_len; i++)
            print_run(&prev[i]);

    Run *next = malloc(RUN_ARRAY_LEN * 2);
    next[0] = (Run){0, '0'};
    int next_len = 0;
    int next_i = 0;

    for (int r = 0; r < reps; r++) {
        next_i = 0;
        debug_ln("%i: %i", r, prev_len);
        for (int i = 0; i < prev_len; i++) {
            char string[3];
            decode_run(&prev[i], string);
            const int encoded_count = encode_run(&next[next_i++], string);
            if (encoded_count > 1) next_i++;
        }
        next_len = next_i;

        reduce_runs(prev, &prev_len, next, &next_len);
        copy_next_back(prev, &prev_len, next, &next_len);

        debug_ln("%i: %i", r, prev_len);
        // if (debugging) {
        //     print_spacer();
        //     for (int i = 0; i < prev_len; i++)
        //         print_run(&prev[i]);
        // }
    }

    const int sum = sum_runs(prev, prev_len);
    free(prev);
    free(next);
    return sum;
}

void day10_part1() {
    print_header(10, 1);
    const char *input = day10_input.input;

    printf("%llu", calculate(input, 40));
}

void day10_part2() {
    print_header(10, 2);
    const char *input = day10_input.input;

    printf("%llu", calculate(input, 50));
}

IDay day10 = {
    .part1 = day10_part1,
    .part2 = day10_part2
};
