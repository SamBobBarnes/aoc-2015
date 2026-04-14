//
// Created by sb17057 on 4/9/2026.
//

#include "day12.h"
#include "Inputs/day12.h"

#include <string.h>

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

    printf("The sum of all number is %i", total);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

void day12_part2() {
    print_header(12, 2);
    bool test = true;
    char *input = nullptr;
    if (test)
        input = day12_input.test_input;
    else {
        input = read_file("../Inputs/day12.txt"); // disregard the first 3 chars
        input = input + 3;
    }
    const size_t len = strlen(input);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

IDay day12 = {
    .part1 = day12_part1,
    .part2 = day12_part2
};
