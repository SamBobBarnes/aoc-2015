//
// Created by sb17057 on 4/9/2026.
//

#include "day13.h"
#include "Inputs/day13.h"

#include <string.h>

void day13_part1() {
    print_header(13, 1);
    const char *input = day13_input.test_input;
    const size_t len = strlen(input);
}

void day13_part2() {
    print_header(13, 2);
    const char *input = day13_input.test_input;
    const size_t len = strlen(input);
}

IDay day13 = {
    .part1 = day13_part1,
    .part2 = day13_part2
};
