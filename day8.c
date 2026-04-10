//
// Created by sb17057 on 4/9/2026.
//

#include "day8.h"
#include "Inputs/day8.h"

#include <string.h>

void day8_part1() {
    print_header(8, 1);
    // const char *input = day8_input.test_input;
    size_t len = 0;
 const char *input = read_text_file("Inputs/day8.txt", &len);

    printf("%s", input);
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
