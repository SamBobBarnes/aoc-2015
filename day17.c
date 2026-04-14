//
// Created by sb17057 on 4/9/2026.
//

#include "day17.h"
#include "Inputs/day17.h"

#include <string.h>

void day17_part1() {
    print_header(17, 1);
    const char *input = day17_input.test_input;
    const size_t len = strlen(input);
}

void day17_part2() {
    print_header(17, 2);
    const char *input = day17_input.test_input;
    const size_t len = strlen(input);
}

IDay day17 = {
    .part1 = day17_part1,
    .part2 = day17_part2
};
