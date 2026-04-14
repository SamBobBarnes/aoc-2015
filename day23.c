//
// Created by sb17057 on 4/9/2026.
//

#include "day23.h"
#include "Inputs/day23.h"

#include <string.h>

void day23_part1() {
    print_header(23, 1);
    const char *input = day23_input.test_input;
    const size_t len = strlen(input);
}

void day23_part2() {
    print_header(23, 2);
    const char *input = day23_input.test_input;
    const size_t len = strlen(input);
}

IDay day23 = {
    .part1 = day23_part1,
    .part2 = day23_part2
};
