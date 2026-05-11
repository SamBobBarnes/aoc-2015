//
// Created by sb17057 on 4/9/2026.
//

#include "day20.h"
#include "Inputs/day20.h"

#include <math.h>
#include <string.h>

void day20_part1() {
    print_header(20, 1);
    const char *input = day20_input.input;
    const size_t len = strlen(input);

    int total = atoi(input) / 10;

    for (int i = 1; i <= total; i++) {
        int count = 0;
        int rt = (int) sqrt(i);
        for (int j = 1; j <= rt; j++) {
            if (i % j == 0) {
                count += j;
                count += i / j;
            }
            if (count >= total) {
                printf("%i", i);
                return;
            }
        }
    }
}

void day20_part2() {
    print_header(20, 2);
    const char *input = day20_input.input;
    const size_t len = strlen(input);

    int total = atoi(input);
    int i = 0;
    do {
        int count = 0;
        int rt = (int) sqrt(i);
        for (int j = 1; j <= rt; j++) {
            if (i % j == 0) {
                if (j <= 50) {
                    count += i / j;
                }
                if (i / j <= 50) {
                    count += j;
                }
            }
            if (count * 11 >= total) {
                printf("%i", i);
                return;
            }
        }
        i++;
    } while (true);
    // x < 887040
}

IDay day20 = {
    .part1 = day20_part1,
    .part2 = day20_part2
};
