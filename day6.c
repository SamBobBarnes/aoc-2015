//
// Created by sb17057 on 4/9/2026.
//

#include "day6.h"
#include "Inputs/day6.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// actions
#define TURN_ON 1
#define TURN_OFF 0
#define TOGGLE 2

void process_command(const int *action, const struct Point *start, const struct Point *end, bool grid[][1000]) {
    // char *action_string = "\0\0\0\0\0\0\0\0\0";
    // switch (*action) {
    //     case 0:
    //         action_string = "turn off";
    //         break;
    //     case 1:
    //         action_string = "turn on";
    //         break;
    //     case 2:
    //         action_string = "toggle";
    // }
    // printf("%s [%i,%i] thru [%i,%i]\n", action_string, start->x, start->y, end->x, end->y);

    for (int i = start->x; i <= end->x; i++)
        for (int j = start->y; j <= end->y; j++) {
            switch (*action) {
                case 0:
                    grid[i][j] = false;
                    break;
                case 1:
                    grid[i][j] = true;
                    break;
                case 2:
                    const bool current = grid[i][j];
                    grid[i][j] = !current;
                    break;
            }
        }
}

int count_lights(bool grid[][1000]) {
    int total = 0;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            if (grid[i][j]) total++;

    return total;
}

void init_lights(bool grid[][1000]) {
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            grid[i][j] = false;
}

void day6_part1() {
    print_header(6, 1);
    const char *input = day6_input.input;
    const size_t len = strlen(input);

    bool grid[1000][1000];
    init_lights(grid);

    int action = TURN_OFF;
    struct Point start;
    struct Point end;
    int index_of_last_space = -1;
    int index_of_last_comma = -1;
    bool decode_start = true;
    bool start_x_found = false;
    bool start_y_found = false;
    char word[34] = {'\0'};
    int wordi = 0;

    for (int i = 5; i < len; i++) {
        word[wordi] = input[i];
        wordi++;
        if (input[i - 2] == 'o' && input[i - 1] == 'f' && input[i] == 'f')
            action = TURN_OFF;
        else if (input[i - 1] == 'o' && input[i] == 'n')
            action = TURN_ON;
        else if (input[i - 5] == 't' && input[i - 4] == 'o' && input[i - 3] == 'g' && input[i - 2] == 'g' && input[
                     i - 1] == 'l' && input[i] == 'e')
            action = TOGGLE;
        else if (input[i] == ' ') {
            index_of_last_space = i;
            if (start_x_found && !start_y_found) {
                char y[i - index_of_last_comma];
                y[i - index_of_last_comma - 1] = '\0';
                int yi = 0;
                for (int j = index_of_last_comma + 1; j < i; j++) {
                    y[yi] = input[j];
                    yi++;
                }
                start.y = atoi(y);
                start_y_found = true;
                decode_start = false;
            }
        } else if (input[i] == ',') {
            index_of_last_comma = i;
            char x[i - index_of_last_space];
            x[i - index_of_last_space - 1] = '\0';
            int xi = 0;
            for (int j = index_of_last_space + 1; j < i; j++) {
                x[xi] = input[j];
                xi++;
            }

            if (decode_start) {
                start.x = atoi(x);
                start_x_found = true;;
            } else
                end.x = atoi(x);
        } else if (input[i] == '\n') {
            char y[i - index_of_last_comma];
            y[i - index_of_last_comma - 1] = '\0';
            int yi = 0;
            for (int j = index_of_last_comma + 1; j < i; j++) {
                y[yi] = input[j];
                yi++;
            }
            end.y = atoi(y);
            start_x_found = false;
            start_y_found = false;
            decode_start = true;
            // printf("%s", word);
            for (int l = 0; l < 34; l++)
                word[l] = '\0';
            wordi = 0;
            process_command(&action, &start, &end, grid);
            // printf("\n");
        }
    }

    const int total = count_lights(grid);


    printf("We lit %i lights", total);
}

void process_command2(const int *action, const struct Point *start, const struct Point *end, uint8_t grid[][1000]) {
    for (int i = start->x; i <= end->x; i++)
        for (int j = start->y; j <= end->y; j++) {
            int current = grid[i][j];
            switch (*action) {
                case 0:
                    if (current > 0)
                        grid[i][j] = current - 1;
                    break;
                case 1:
                    grid[i][j] = current + 1;
                    break;
                case 2:
                    grid[i][j] = current + 2;
                    break;
            }
        }
}

int count_lights2(uint8_t grid[][1000]) {
    int total = 0;
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            total += grid[i][j];

    return total;
}

void init_lights2(uint8_t grid[][1000]) {
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            grid[i][j] = 0;
}

void day6_part2() {
    print_header(6, 2);
    const char *input = day6_input.input;
    const size_t len = strlen(input);

    uint8_t grid[1000][1000];
    init_lights2(grid);

    int action = TURN_OFF;
    struct Point start;
    struct Point end;
    int index_of_last_space = -1;
    int index_of_last_comma = -1;
    bool decode_start = true;
    bool start_x_found = false;
    bool start_y_found = false;

    for (int i = 5; i < len; i++) {
        if (input[i - 2] == 'o' && input[i - 1] == 'f' && input[i] == 'f')
            action = TURN_OFF;
        else if (input[i - 1] == 'o' && input[i] == 'n')
            action = TURN_ON;
        else if (input[i - 5] == 't' && input[i - 4] == 'o' && input[i - 3] == 'g' && input[i - 2] == 'g' && input[
                     i - 1] == 'l' && input[i] == 'e')
            action = TOGGLE;
        else if (input[i] == ' ') {
            index_of_last_space = i;
            if (start_x_found && !start_y_found) {
                char y[i - index_of_last_comma];
                y[i - index_of_last_comma - 1] = '\0';
                int yi = 0;
                for (int j = index_of_last_comma + 1; j < i; j++) {
                    y[yi] = input[j];
                    yi++;
                }
                start.y = atoi(y);
                start_y_found = true;
                decode_start = false;
            }
        } else if (input[i] == ',') {
            index_of_last_comma = i;
            char x[i - index_of_last_space];
            x[i - index_of_last_space - 1] = '\0';
            int xi = 0;
            for (int j = index_of_last_space + 1; j < i; j++) {
                x[xi] = input[j];
                xi++;
            }

            if (decode_start) {
                start.x = atoi(x);
                start_x_found = true;;
            } else
                end.x = atoi(x);
        } else if (input[i] == '\n') {
            char y[i - index_of_last_comma];
            y[i - index_of_last_comma - 1] = '\0';
            int yi = 0;
            for (int j = index_of_last_comma + 1; j < i; j++) {
                y[yi] = input[j];
                yi++;
            }
            end.y = atoi(y);
            start_x_found = false;
            start_y_found = false;
            decode_start = true;
            process_command2(&action, &start, &end, grid);
            // printf("\n");
        }
    }

    const int total = count_lights2(grid);

    printf("Total brightness is %i", total);
}

IDay day6 = {
    .part1 = day6_part1,
    .part2 = day6_part2
};
