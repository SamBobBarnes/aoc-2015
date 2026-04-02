//
// Created by sb17057 on 4/2/2026.
//

#ifndef AOC_2015_IDAY_H
#define AOC_2015_IDAY_H
#include <stdio.h>

#include "Inputs/iinput.h"

typedef struct {
    void (*part1)();
    void (*part2)();
} IDay;

static void print_header(int day, int part) {
    printf("\n--------------\n");
    printf("Day %i Part %i", day, part);
    printf("\n--------------\n");
}

#endif //AOC_2015_IDAY_H