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
    print_header(3, 1);
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
    print_header(3, 2);
    const char *input = day3_input.input;
    const size_t len = strlen(input);

    struct Point santa_pos = new_point(0, 0);
    struct Point robot_pos = new_point(0, 0);
    bool santas_move = true;

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
    //
    // print_spacer();

    for (int i = 0; i < len; ++i) {
        switch (input[i]) {
            case '^':
                if (santas_move)
                    santa_pos.y++;
                else
                    robot_pos.y++;
                break;
            case '>':

                if (santas_move)
                    santa_pos.x++;
                else
                    robot_pos.x++;
                break;
            case '<':
                if (santas_move)
                    santa_pos.x--;
                else
                    robot_pos.x--;
                break;
            case 'v':
                if (santas_move)
                    santa_pos.y--;
                else
                    robot_pos.y--;
                break;
            default:
                printf("TILT");
                break;
        }
        // if (santas_move)
        //     printf("Santa [%i,%i] i: %i\n", santa_pos.x, santa_pos.y, i);
        // else
        //     printf("Robot [%i,%i] i: %i\n", robot_pos.x, robot_pos.y, i);

        int visited_house_index = -1;

        for (int j = 0; j < len + 1; ++j) {
            // search for previously visited house
            if (
                (santas_move
                 && houses[j].x == santa_pos.x
                 && houses[j].y == santa_pos.y)
                || (!santas_move
                    && houses[j].x == robot_pos.x
                    && houses[j].y == robot_pos.y)
            ) {
                visited_house_index = j;
                break;
            }
        }

        if (visited_house_index == -1) {
            if (santas_move) {
                houses[i + 1].x = santa_pos.x;
                houses[i + 1].y = santa_pos.y;
            } else {
                houses[i + 1].x = robot_pos.x;
                houses[i + 1].y = robot_pos.y;
            }
            houses[i + 1].count = 1;
        } else {
            houses[visited_house_index].count++;
        }
        santas_move = !santas_move;
    }

    // print_spacer();

    int total_houses_visited = 0;
    for (int j = 0; j < len + 1; ++j) {
        // printf("[%i,%i]: %i\n", houses[j].x, houses[j].y, houses[j].count);
        if (houses[j].count > 0) {
            total_houses_visited++;
        }
    }

    printf("We visited %i houses.", total_houses_visited);
}

IDay day3 = {
    .part1 = day3_part1,
    .part2 = day3_part2
};
