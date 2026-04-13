//
// Created by sb17057 on 4/9/2026.
//

#include "day10.h"
#include "Inputs/day10.h"

#include <string.h>

void day10_part1() {
    print_header(10, 1);
    const char *input = day10_input.test_input;
    const size_t len = strlen(input);
}

void day10_part2() {
    print_header(10, 2);
    const char *input = day10_input.test_input;
    const size_t len = strlen(input);
}

IDay day10 = {
    .part1 = day10_part1,
    .part2 = day10_part2
};
