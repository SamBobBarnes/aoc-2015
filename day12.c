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

int reds = 0;

int recurse(int *i, const char *json, const size_t len, const int depth) {
    int total = 0;
    bool red = false;
    char container = *i != 0 ? json[(*i) - 1] : 'r';

    bool reading_num = false;
    char num[10] = {'\0'};
    int num_i = 0;
    while (*i < len) {
        const char val = json[*i];
        if (val == '{' || val == '[') {
            (*i)++;
            total += recurse(i, json, len, depth + 1);
        }
        if (val == '}' || val == ']') {
            (*i)++;
            break;
        }
        if (*i < len - 3 && json[*i] == 'r' && json[*i + 1] == 'e' && json[*i + 2] == 'd' && container == '{') {
            red = true;
        }
        if ((val >= 48 && val <= 57) || val == '-') reading_num = true;
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
            num[num_i++] = val;
        }

        (*i)++;
    }

    char spacer[200] = {'\0'};
    for (int j = 0; j < depth; j++)
        spacer[j] = ' ';

    if (red) {
        debug_ln(RED "%s%c d: %i, t: %i" RESET, spacer, container, depth, total, red);
        reds++;
        return 0;
    }
    debug_ln("%s%c d: %i, t: %i", spacer, container, depth, total, red);

    return total;
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

    int i = 0;
    const int total = recurse(&i, input, len, 0);

    // 82040 < x < 121920
    print_ln("reds: %i", reds);
    print_ln("The sum of all numbers is %i", total);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

IDay day12 = {
    .part1 = day12_part1,
    .part2 = day12_part2
};
