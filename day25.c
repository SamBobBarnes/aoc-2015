//
// Created by sb17057 on 4/9/2026.
//

#include "day25.h"
#include "Inputs/day25.h"

#include <stdint.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Point;

uint64_t calculate_next(const uint64_t last) {
    uint64_t mul = (uint64_t) 252533 * last;
    return mul % 33554393;
}

Point next_point(const Point current) {
    if (current.y == 1) return (Point){1, current.x + 1};
    return (Point){current.x + 1, current.y - 1};
}


void day25_part1() {
    print_header(25, 1);
    Point goal = {3019, 3010};

    uint64_t current_val = 20151125;
    Point current = {1, 1};
    while (current.x != goal.x || current.y != goal.y) {
        current = next_point(current);
        current_val = calculate_next(current_val);
    }
    print_ln("code is %lld", current_val);
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
