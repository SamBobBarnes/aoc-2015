//
// Created by sb17057 on 4/9/2026.
//

#include "day24.h"
#include "Inputs/day24.h"

#include <string.h>

void day24_part1() {
    print_header(24, 1);
    const char *input = day24_input.test_input;
    const size_t len = strlen(input);
}

void day24_part2() {
    print_header(24, 2);
    const char *input = day24_input.test_input;
    const size_t len = strlen(input);
}

IDay day24 = {
    .part1 = day24_part1,
    .part2 = day24_part2
};
