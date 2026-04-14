//
// Created by sb17057 on 4/2/2026.
//

#ifndef AOC_2015_IDAY_H
#define AOC_2015_IDAY_H
#include <stdarg.h>
#include <stdio.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#include "Inputs/iinput.h"

typedef struct {
    void (*part1)();

    void (*part2)();
} IDay;

static void print_header(const int day, const int part) {
    printf("\n--------------\n");
    printf("Day %i Part %i", day, part);
    printf("\n--------------\n");
}

struct Point {
    int x;
    int y;
};

static struct Point new_point(const int x, const int y) {
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
}

static void print_spacer() {
    printf("\n--------------\n");
}

static void print_ln(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);
    va_end(args);
    printf("\n");
}

#endif //AOC_2015_IDAY_H
