//
// Created by sb17057 on 4/2/2026.
//

#include "day1.h"
#include "Inputs/day1.h"
#include <string.h>

#include <stdio.h>

void day1_part1() {
    print_header(1,1);
    char* input = day1_input.input;
    size_t len = strlen(input);
    int floor = 0;
    for (int i = 0; i < len; ++i) {
        if (input[i] == ')') floor--;
        else floor++;
    }

    printf("Santa should go to floor %i", floor);
}

void day1_part2() {
    print_header(1,2);
    char* input = day1_input.input;
    size_t len = strlen(input);
    int floor = 0;
    for (int i = 0; i < len; ++i) {
        if (input[i] == ')') floor--;
        else floor++;
        if (floor == -1) {

            printf("Santa entered the basement on char %i", i+1);
            break;
        }
    }

}

IDay day1 = {
    .part1 = day1_part1,
    .part2 = day1_part2
};
