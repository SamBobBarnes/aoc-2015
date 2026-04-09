//
// Created by sb17057 on 4/8/2026.
//

#include "day3.h"
#include "Inputs/day3.h"

#include <limits.h>
#include <string.h>

struct House {
    int x;
    int y;
    int count;
};

void day3_part1() {
    print_header(2, 1);
    const char *input = day3_input.input;
    const size_t len = strlen(input);

    int x = 0;
    int y = 0;

    struct House houses[len + 1];
    houses[0].count = 1;
    houses[0].x = 0;
    houses[0].y = 0;
    for (int i = 1; i < len + 1; ++i) {
        houses[i].x = INT_MAX;
        houses[i].y = INT_MAX;
        houses[i].count = 0;
    }

    // for (int j = 0; j < len + 1; ++j)
    //     printf("[%i,%i]: %i\n", houses[j].x, houses[j].y, houses[j].count);

    for (int i = 0; i < len; ++i) {
        switch (input[i]) {
            case '^':
                y++;
                break;
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            case 'v':
                y--;
                break;
            default:
                printf("TILT");
                break;
        }
        // printf("[%i,%i] i: %i\n", x, y, i);
        int visited_house_index = -1;

        for (int j = 0; j < len + 1; ++j) {
            if (houses[j].x == x && houses[j].y == y) {
                visited_house_index = j;
                break;
            }
        }

        if (visited_house_index == -1) {
            houses[i + 1].x = x;
            houses[i + 1].y = y;
            houses[i + 1].count = 1;
        } else {
            houses[visited_house_index].count++;
        }
    }

    int total_houses_visited = 0;
    for (int j = 0; j < len + 1; ++j) {
        // printf("[%i,%i]: %i\n", houses[j].x, houses[j].y, houses[j].count);
        if (houses[j].count > 0) {
            total_houses_visited++;
        }
    }

    printf("Santa visited %i houses.", total_houses_visited);
}

void day3_part2() {
    print_header(2, 1);
    char *input = day3_input.test_input;
}

IDay day3 = {
    .part1 = day3_part1,
    .part2 = day3_part2
};
