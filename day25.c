//
// Created by sb17057 on 4/9/2026.
//

#include "day25.h"
#include "Inputs/day25.h"

#include <string.h>

void day25_part1() {
    print_header(25, 1);
    const char *input = day25_input.test_input;
    const size_t len = strlen(input);
}

void day25_part2() {
    print_header(25, 2);
    const char *input = day25_input.test_input;
    const size_t len = strlen(input);
}

IDay day25 = {
    .part1 = day25_part1,
    .part2 = day25_part2
};
