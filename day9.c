//
// Created by sb17057 on 4/9/2026.
//

#include "day9.h"
#include "Inputs/day9.h"

#include <string.h>

void day9_part1() {
    print_header(9, 1);
    const char *input = day9_input.test_input;
    const size_t len = strlen(input);
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
