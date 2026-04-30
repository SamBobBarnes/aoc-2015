//
// Created by sb17057 on 4/9/2026.
//

#include "day19.h"
#include "Inputs/day19.h"

#include <string.h>

#include "debug.h"

int index_of(const char *string, const char *search_string, const int offset) {
    const size_t len = strlen(string);
    const size_t search_len = strlen(search_string);
    for (int i = offset; i < len - 1 - search_len; i++) {
        bool match = true;
        for (int j = 0; j < search_len; j++)
            if (string[i + j] != search_string[j]) {
                match = false;
                break;
            }
        if (match) {
            return i;
        }
    }

    return -1;
}

void day19_part1() {
    print_header(19, 1);
    const char *input = day19_input.test_input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, &row_count, &max_row_size, rows);

    char *sut = rows[row_count - 1];
    size_t sut_len = strlen(sut);
    char possibles[row_count * 10][max_row_size * 2];
    int possible_count = 0;

    for (int i = 0; i < row_count * 10; i++) possibles[i][0] = '\0';

    for (int i = 0; i < row_count - 3; i++) {
        char temp[max_row_size * 2];
        int index;

        int space_index = index_of(rows[i], " ", 0);
        char search_string[4];
        strncpy(search_string, rows[i], space_index);
        size_t search_len = strlen(search_string);
        char *replacement_string = &rows[i][space_index + 4];
        size_t replacement_len = strlen(replacement_string);

        debug_ln("%s:", search_string);

        int offset = 0;
        do {
            index = index_of(sut, search_string, offset);

            if (index == -1) break; // no more left

            strncpy(temp, sut, index);
            strcpy(&temp[index], replacement_string);
            strncpy(&temp[index + replacement_len], &sut[index + search_len], sut_len - index - search_len);

            if (debugging) {
                printf("%i,", index);
            }

            bool duplicate = false;
            for (int j = 0; j < possible_count; j++) {
                if (strcmp(possibles[j], temp) == 0) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                strcpy(possibles[possible_count++], temp);
            }

            offset = index + search_len;
        } while (index >= 0);
    }

    print_ln("There are %i unique replacements.", possible_count);
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
