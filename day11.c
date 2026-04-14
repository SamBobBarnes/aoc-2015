//
// Created by sb17057 on 4/9/2026.
//

#include "day11.h"
#include "Inputs/day11.h"

#include <string.h>

void day11_part1() {
    print_header(11, 1);
    const char *input = day11_input.test_input;
    const size_t len = strlen(input);
}

void day11_part2() {
    print_header(11, 2);
    const char *input = day11_input.test_input;
    const size_t len = strlen(input);
}

IDay day11 = {
    .part1 = day11_part1,
    .part2 = day11_part2
};
