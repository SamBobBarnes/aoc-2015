//
// Created by sb17057 on 4/9/2026.
//

#include "day8.h"
#include "Inputs/day8.h"

#include <string.h>

char *ReadFile(char *filename) {
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler) {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char *) malloc(sizeof(char) * (string_size + 1));

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size) {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
        fclose(handler);
    }

    return buffer;
}

void day8_part1() {
    print_header(8, 1);
    char *input = ReadFile("../Inputs/day8.txt"); // disregard the first 3 chars
    input = input + 3;
    if (input) {
#pragma region Split Input into rows
        size_t len = strlen(input);
        int row_count = 0;
        int max_row_size = 0;
        int index_of_last_newline = -1;
        for (int i = 0; i < len; i++)
            if (input[i] == '\n') {
                row_count++;
                int row_len = i - index_of_last_newline;
                if (row_len > max_row_size) max_row_size = row_len;
                index_of_last_newline = i;
            }
        if (input[len - 1] != '\n') row_count++;
        char rows[row_count][max_row_size];
        int row_lengths[row_count];
        int current_row = 0;
        int row_index = 0;

        for (int i = 0; i < len; i++) {
            if (input[i] == '\n') {
                rows[current_row][row_index] = '\0';
                row_lengths[current_row] = row_index;
                row_index = 0;
                current_row++;
                continue;
            }
            rows[current_row][row_index] = input[i];
            row_index++;
        }
        if (input[len - 1] != '\n') {
            rows[current_row][row_index] = '\0';
            row_lengths[current_row] = row_index;
        }
#pragma endregion

        int total = 0;
        for (int i = 0; i < row_count; i++) {
            // printf("%s\n", rows[i]);
            int string_char_count = 0;
            const char *row = rows[i];
            for (int j = 1; j < row_lengths[i] - 1; j++) {
                if (row[j] == '\\' && (row[j + 1] == '\\' || row[j + 1] == '"'))
                    j++;
                else if (row[j] == '\\' && row[j + 1] == 'x')
                    j += 3;
                string_char_count++;
            }
            total += row_lengths[i] - string_char_count;
        }

        printf("The diff is %i chars", total);
    }

    input = input - 3;
    free(input);
}

void day8_part2() {
    print_header(8, 2);
    char *input = ReadFile("../Inputs/day8.txt"); // disregard the first 3 chars
    input = input + 3;
    if (input) {
#pragma region Split Input into rows
        size_t len = strlen(input);
        int row_count = 0;
        int max_row_size = 0;
        int index_of_last_newline = -1;
        for (int i = 0; i < len; i++)
            if (input[i] == '\n') {
                row_count++;
                int row_len = i - index_of_last_newline;
                if (row_len > max_row_size) max_row_size = row_len;
                index_of_last_newline = i;
            }
        if (input[len - 1] != '\n') row_count++;
        char rows[row_count][max_row_size];
        int row_lengths[row_count];
        int current_row = 0;
        int row_index = 0;

        for (int i = 0; i < len; i++) {
            if (input[i] == '\n') {
                rows[current_row][row_index] = '\0';
                row_lengths[current_row] = row_index;
                row_index = 0;
                current_row++;
                continue;
            }
            rows[current_row][row_index] = input[i];
            row_index++;
        }
        if (input[len - 1] != '\n') {
            rows[current_row][row_index] = '\0';
            row_lengths[current_row] = row_index;
        }
#pragma endregion

        int total = 0;
        for (int i = 0; i < row_count; i++) {
            // printf("%s\n", rows[i]);
            int encoded_char_count = 6;
            const char *row = rows[i];
            for (int j = 1; j < row_lengths[i] - 1; j++) {
                if (row[j] == '\\' || row[j] == '"')
                    encoded_char_count++;
                encoded_char_count++;
            }
            total += encoded_char_count - row_lengths[i];
        }

        printf("The diff is %i chars", total);
    }

    input = input - 3;
    free(input);
}

IDay day8 = {
    .part1 = day8_part1,
    .part2 = day8_part2
};
