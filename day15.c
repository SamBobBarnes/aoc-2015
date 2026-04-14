//
// Created by sb17057 on 4/9/2026.
//

#include "day15.h"
#include "Inputs/day15.h"

#include <string.h>

void day15_part1() {
    print_header(15, 1);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);
}

void day15_part2() {
    print_header(15, 2);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);
}

IDay day15 = {
    .part1 = day15_part1,
    .part2 = day15_part2
};
