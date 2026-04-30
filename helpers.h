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

#include <string.h>

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

static void free_ptr(void *ptr) {
    free(*(void **) ptr);
}

static int GetRowCount(const char *input, const size_t len, int *max_row_size) {
    int index_of_last_newline = -1;
    int row_count = 0;
    for (int i = 0; i < len; i++) {
        if (input[i] == '\n') {
            row_count++;
            index_of_last_newline = i;
        }
        int row_len = i - index_of_last_newline;
        if (row_len > *max_row_size) *max_row_size = row_len;
    }
    if (input[len - 1] != '\n') row_count++;

    return row_count;
}


/// @param input
/// @param len
/// @param row_count
/// @param max_row_size
/// @param rows
/// @remark
/// Example:\n
/// int max_row_size = 0;\n
/// int row_count = GetRowCount(input, len, &max_row_size);\n
/// char rows[row_count][max_row_size];\n
/// SplitIntoRows(input, len, &row_count, &max_row_size, rows);\n
///
static void SplitIntoRows(const char *input, const size_t len, const int *row_count, const int *max_row_size,
                          char rows[*row_count][*max_row_size]) {
    int current_row = 0;
    int row_index = 0;

    for (int i = 0; i < *row_count; i++) {
        strcpy(rows[current_row], "");
    }

    for (int i = 0; i < len; i++) {
        if (input[i] == '\n') {
            row_index = 0;
            current_row++;
            continue;
        }
        char temp2[2] = "0\0";
        temp2[0] = input[i];
        strcat(rows[current_row], temp2);
        row_index++;
    }
}

#endif //AOC_2015_IDAY_H
