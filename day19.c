//
// Created by sb17057 on 4/9/2026.
//

#include "day19.h"
#include "Inputs/day19.h"

#include <string.h>

#include "debug.h"

void day19_part1() {
    print_header(19, 1);
    const char *input = day19_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, &row_count, &max_row_size, rows);

    for (int i = 0; i < row_count; i++) {
        debug_ln("%s", rows[i]);
    }
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
