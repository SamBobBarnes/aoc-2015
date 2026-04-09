//
// Created by sb17057 on 4/9/2026.
//

#include "dayX.h"
#include "Inputs/dayX.h"

void dayX_part1() {
    print_header(X, 1);
    const char *input = dayX_input.test_input;
}

void dayX_part2() {
    print_header(X, 2);
    const char *input = dayX_input.test_input;
}

IDay dayX = {
    .part1 = dayX_part1,
    .part2 = dayX_part2
};
