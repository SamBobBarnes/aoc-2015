//
// Created by sb17057 on 4/9/2026.
//

#include "day22.h"
#include "Inputs/day22.h"

#include <string.h>

void day22_part1() {
    print_header(22, 1);
    const char *input = day22_input.test_input;
    const size_t len = strlen(input);
}

void day22_part2() {
    print_header(22, 2);
    const char *input = day22_input.test_input;
    const size_t len = strlen(input);
}

IDay day22 = {
    .part1 = day22_part1,
    .part2 = day22_part2
};
