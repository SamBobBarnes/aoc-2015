//
// Created by sb17057 on 4/9/2026.
//

#include "day12.h"
#include "Inputs/day12.h"

#include <string.h>

#include "debug.h"

void day12_part1() {
    print_header(12, 1);
    bool test = false;
    char *input = nullptr;
    if (test)
        input = day12_input.test_input;
    else {
        input = read_file("../Inputs/day12.txt"); // disregard the first 3 chars
        input = input + 3;
    }
    const size_t len = strlen(input);

    bool reading_num = false;
    char num[10] = {'\0'};
    int num_i = 0;
    int total = 0;
    for (int i = 0; i < len; i++) {
        if ((input[i] >= 48 && input[i] <= 57) || input[i] == '-') reading_num = true;
        else if (reading_num) {
            int num_val = atoi(num);
            total += num_val;
            reading_num = false;
            for (int j = 0; j < 10; j++) {
                num[j] = '\0';
            }
            num_i = 0;
        }
        if (reading_num) {
            num[num_i++] = input[i];
        }
    }

    printf("The sum of all numbers is %i", total);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

void day12_part2() {
    print_header(12, 2);
    bool test = false;
    char *input = nullptr;
    if (test)
        input = day12_input.test_input;
    else {
        input = read_file("../Inputs/day12.txt"); // disregard the first 3 chars
        input = input + 3;
    }
    const size_t len = strlen(input);

    bool reading_num = false;
    char num[10] = {'\0'};
    int num_i = 0;
    int total = 0;
    int depth = 0;
    int reds = 0;
    int depth_total = 0;
    int stop_reading = -1;
    for (int i = 0; i < len; i++) {
        char val = input[i];
        if (stop_reading == -1) {
            if ((input[i] >= 48 && input[i] <= 57) || input[i] == '-') reading_num = true;
            else if (reading_num) {
                int num_val = atoi(num);
                depth_total += num_val;
                reading_num = false;
                for (int j = 0; j < 10; j++) {
                    num[j] = '\0';
                }
                num_i = 0;
            }
            if (reading_num) {
                num[num_i++] = input[i];
            }
        }
        if (input[i] == '{' || input[i] == '[') {
            if (stop_reading == -1) {
                total += depth_total;
            }
            depth++;
            depth_total = 0;
        }
        if (input[i] == '}' || input[i] == ']') {
            if (depth == stop_reading - 1) {
                stop_reading = -1;
                depth_total = 0;
            }
            total += depth_total;
            depth--;
            depth_total = 0;
        }
        if (i < len - 6 && input[i] == ':' && input[i + 1] == '"' && input[i + 2] == 'r' && input[i + 3] == 'e' && input
            [i + 4] == 'd' && input[i + 5] == '"') {
            reds++;
            stop_reading = depth;
            depth_total = 0;
        }
    }

    debug_ln("reds: %i", reds);
    // 82040 < x < 121920
    printf("The sum of all numbers is %i", total);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

IDay day12 = {
    .part1 = day12_part1,
    .part2 = day12_part2
};
