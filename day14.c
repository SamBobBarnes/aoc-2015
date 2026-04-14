//
// Created by sb17057 on 4/9/2026.
//

#include "day14.h"
#include "Inputs/day14.h"

#include <string.h>

void day14_part1() {
    print_header(14, 1);
    const char *input = day14_input.test_input;
    const size_t len = strlen(input);
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
