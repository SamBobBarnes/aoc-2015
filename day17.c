//
// Created by sb17057 on 4/9/2026.
//

#include "day17.h"
#include "Inputs/day17.h"

#include <string.h>
#include <math.h>

#include "debug.h"

typedef struct {
    int id;
    int volume;
} Box;

int get_total(const long current, const Box *boxes, const int box_count) {
    int total = 0;
    for (int i = 0; i < box_count; i++) {
        long mask = pow(2, i);
        bool has_box = (mask & current) > 0;
        if (has_box) {
            total += boxes[i].volume;
        }
    }
    return total;
}

void day17_part1() {
    print_header(17, 1);
    char *input = day17_input.input;
    size_t len = strlen(input);

    char line[len + 1];
    strcpy(line, input);

    Box boxes[20];
    int box_count = 0;

    int goal = 150;
    // int goal = 25;

    char *ptr = strtok(line, ",");
    while (ptr != NULL) {
        boxes[box_count].id = box_count;
        boxes[box_count++].volume = atoi(ptr);
        ptr = strtok(nullptr, ",");
    }
    int total = 0;

    //sort list

    bool sorted = false;
    while (!sorted) {
        bool switched = false;

        for (int i = 1; i < box_count; i++) {
            if (boxes[i - 1].volume > boxes[i].volume) {
                int a_vol = boxes[i - 1].volume;
                int b_vol = boxes[i].volume;
                boxes[i - 1].volume = b_vol;
                boxes[i].volume = a_vol;
                switched = true;
            }
        }

        if (!switched) sorted = true;
    }


    for (int i = 0; i < box_count; i++) {
        debug_ln("%i", boxes[i].volume);
    }

    for (long i = 0; i < pow(2, box_count); i++) {
        if (get_total(i, boxes, box_count) == goal) {
            total++;
        }
    }

    print_ln("%i", total);
}


void day17_part2() {
    print_header(17, 2);
    const char *input = day17_input.test_input;
    const size_t len = strlen(input);
}

IDay day17 = {
    .part1 = day17_part1,
    .part2 = day17_part2
};
