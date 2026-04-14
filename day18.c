//
// Created by sb17057 on 4/9/2026.
//

#include "day18.h"
#include "Inputs/day18.h"

#include <string.h>

void day18_part1() {
    print_header(18, 1);
    const char *input = day18_input.test_input;
    const size_t len = strlen(input);
}

void day18_part2() {
    print_header(18, 2);
    const char *input = day18_input.test_input;
    const size_t len = strlen(input);
}

IDay day18 = {
    .part1 = day18_part1,
    .part2 = day18_part2
};
