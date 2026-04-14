//
// Created by sb17057 on 4/9/2026.
//

#include "day12.h"
#include "Inputs/day12.h"

#include <string.h>

void day12_part1() {
    print_header(12, 1);
    const char *input = day12_input.test_input;
    const size_t len = strlen(input);
}

void day12_part2() {
    print_header(12, 2);
    const char *input = day12_input.test_input;
    const size_t len = strlen(input);
}

IDay day12 = {
    .part1 = day12_part1,
    .part2 = day12_part2
};
