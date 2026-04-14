//
// Created by sb17057 on 4/9/2026.
//

#include "day11.h"
#include "Inputs/day11.h"

#include <stdint.h>
#include <string.h>

#include "debug.h"

bool has_straight(const char *pass) {
    for (int i = 2; i < 8; i++)
        if (pass[i - 2] == pass[i - 1] - 1
            && pass[i - 1] == pass[i] - 1)
            return true;
    return false;
}

bool has_forbidden_letters(const char *pass) {
    for (int i = 0; i < 8; i++)
        if (pass[i] == 'i' || pass[i] == 'o' || pass[i] == 'l') return true;
    return false;
}

bool has_two_pair(const char *pass) {
    int count = 0;
    for (int i = 1; i < 8; i++)
        if (pass[i - 1] == pass[i]) {
            count++;
            i++;
        }
    return count >= 2;
}

void increment(char *pass, const int i) {
    if (pass[i] == 'z') {
        pass[i] = 'a';
        if (i > 0) increment(pass, i - 1);
        return;
    }
    pass[i] = (char) ((uint8_t) pass[i] + 1);
}

char new_pass[9];

void day11_part1() {
    print_header(11, 1);
    char *input = day11_input.input;

    char pass[9] = {'\0'};
    strcpy(pass, input);

    while (!(has_straight(pass) && !has_forbidden_letters(pass) && has_two_pair(pass))) {
        debug_ln("%s", pass);
        increment(pass, 7);
    }

    strcpy(new_pass, pass);
    printf("Santa's new password is %s", pass);
}

void day11_part2() {
    print_header(11, 2);

    char pass[9] = {'\0'};
    strcpy(pass, new_pass);

    increment(pass, 7);
    
    while (!(has_straight(pass) && !has_forbidden_letters(pass) && has_two_pair(pass))) {
        debug_ln("%s", pass);
        increment(pass, 7);
    }

    printf("Santa's new password is %s", pass);
}

IDay day11 = {
    .part1 = day11_part1,
    .part2 = day11_part2
};
