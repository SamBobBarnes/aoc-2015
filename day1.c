//
// Created by sb17057 on 4/2/2026.
//

#include "day1.h"
#include "Inputs/day1.h"

#include <stdio.h>

void day1_part1() {
    print_header(1,1);
    char* input = day1_input.test_input;
}

void day1_part2() {
    print_header(1,2);
}

IDay day1 = {
    .part1 = day1_part1,
    .part2 = day1_part2
};
