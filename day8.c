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
    // const char *input = day8_input.test_input;

    char *input = ReadFile("../Inputs/day8.txt"); // disregard the first 3 chars
    input = input + 3;
    if (input) {
        printf("%s", input);
    }

    input = input - 3;
    free(input);
}

void day8_part2() {
    print_header(8, 2);
    const char *input = day8_input.test_input;
    const size_t len = strlen(input);
}

IDay day8 = {
    .part1 = day8_part1,
    .part2 = day8_part2
};
