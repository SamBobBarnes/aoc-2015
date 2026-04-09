//
// Created by sb17057 on 4/9/2026.
//

#include "day5.h"
#include "Inputs/day5.h"

#include <string.h>

void day5_part1() {
    print_header(5, 1);
    const char *input = day5_input.input;
    const size_t len = strlen(input);

    int total = 0;
    for (int i = 0; i < len; i += 17) {
        char word[17] = "\0";
        bool double_letter = false;
        bool forbidden_pairs = false;
        int vowels = 0;
        for (int j = 0; j < 16; j++) {
            char pair[2];
            word[j] = input[i + j];
            if (j < 15) {
                pair[0] = input[i + j];
                pair[1] = input[i + j + 1];
                if (pair[0] == pair[1])
                    double_letter = true;
                if (
                    strncmp(pair, "ab", 2) == 0
                    || strncmp(pair, "cd", 2) == 0
                    || strncmp(pair, "pq", 2) == 0
                    || strncmp(pair, "xy", 2) == 0
                )
                    forbidden_pairs = true;
            }
            if (input[i + j] == 'a'
                || input[i + j] == 'e'
                || input[i + j] == 'i'
                || input[i + j] == 'o'
                || input[i + j] == 'u'
            )
                vowels++;
        }
        // printf("string: %s\nvowels: %i\ndl: %d\nfp: %d\n-----------\n", word, vowels, double_letter,
        // forbidden_pairs);
        if (vowels >= 3 && double_letter && !forbidden_pairs)
            total++;
    }

    printf("There are %i nice strings", total);
}

void day5_part2() {
    print_header(5, 2);
    const char *input = day5_input.input;
    const size_t len = strlen(input);

    int total = 0;
    for (int i = 0; i < len; i += 17) {
        char word[17] = "\0";
        bool duplicate_pair = false;
        bool letter_straddle = false;
        char pairs[15][2];
        for (int j = 0; j < 16; j++) {
            word[j] = input[i + j];
            if (j < 15) {
                pairs[j][0] = input[i + j];
                pairs[j][1] = input[i + j + 1];
            }
            // find letter straddle
            if (j < 14 && input[i + j] == input[i + j + 2])
                letter_straddle = true;
        }

        // search for duplicate pairs
        for (int j = 0; j < 13; j++) {
            for (int k = j + 2; k < 15; k++) {
                // printf("j:%i, k:%i [%c,%c][%c,%c]\n", j, k, pairs[j][0], pairs[j][1], pairs[k][0], pairs[k][1]);
                if (pairs[j][0] == pairs[k][0] && pairs[j][1] == pairs[k][1]) {
                    duplicate_pair = true;
                    break;
                }
            }
            if (duplicate_pair)
                break;
        }

        // printf("%s\ndp: %d\nls: %d\n-------\n", word, duplicate_pair, letter_straddle);

        if (letter_straddle && duplicate_pair)
            total++;
    }

    printf("There are %i nice strings", total);
}

IDay day5 = {
    .part1 = day5_part1,
    .part2 = day5_part2
};
