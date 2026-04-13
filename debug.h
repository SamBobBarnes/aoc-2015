//
// Created by sb17057 on 4/13/2026.
//

#ifndef AOC_2015_DEBUG_H
#define AOC_2015_DEBUG_H
#include <stdarg.h>
#include <stdio.h>
extern bool debugging;

static void debug(const char *format, ...) {
    if (debugging) {
        va_list args;
        va_start(args, format);

        printf("[DEBUG]: ");

        vprintf(format, args);
        va_end(args);
    }
}

static void debug_ln(const char *format, ...) {
    if (debugging) {
        va_list args;
        va_start(args, format);

        printf("[DEBUG]: ");

        vprintf(format, args);
        va_end(args);
        printf("\n");
    }
}
#endif //AOC_2015_DEBUG_H
