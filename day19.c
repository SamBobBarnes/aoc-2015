//
// Created by sb17057 on 4/9/2026.
//

#include "day19.h"
#include "Inputs/day19.h"

#include <string.h>

void day19_part1() {
    print_header(19, 1);
    const char *input = day19_input.test_input;
    const size_t len = strlen(input);
}

void day19_part2() {
    print_header(19, 2);
    const char *input = day19_input.test_input;
    const size_t len = strlen(input);
}

IDay day19 = {
    .part1 = day19_part1,
    .part2 = day19_part2
};
