//
// Created by sb17057 on 4/9/2026.
//

#include "day21.h"
#include "Inputs/day21.h"

#include <string.h>

void day21_part1() {
    print_header(21, 1);
    const char *input = day21_input.test_input;
    const size_t len = strlen(input);
}

void day21_part2() {
    print_header(21, 2);
    const char *input = day21_input.test_input;
    const size_t len = strlen(input);
}

IDay day21 = {
    .part1 = day21_part1,
    .part2 = day21_part2
};
