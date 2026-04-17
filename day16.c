//
// Created by sb17057 on 4/9/2026.
//

#include "day16.h"
#include "Inputs/day16.h"

#include <string.h>

void day16_part1() {
    print_header(16, 1);
    const char *input = day16_input.input;
    const size_t len = strlen(input);


    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, &row_count, &max_row_size, rows);
    for (int i = 0; i < row_count; i++) {
        printf("%s\n", rows[i]);
    }
}

void day16_part2() {
    print_header(16, 2);
    const char *input = day16_input.test_input;
    const size_t len = strlen(input);
}

IDay day16 = {
    .part1 = day16_part1,
    .part2 = day16_part2
};
