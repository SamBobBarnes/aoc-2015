//
// Created by sb17057 on 4/9/2026.
//

#include "day17.h"
#include "Inputs/day17.h"
#include "libs/itertools/itertools.h"

#include <string.h>

typedef struct {
    int id;
    int volume;
} Box;

int total_vol(Box **boxes, const int box_count) {
    int total = 0;
    for (int i = 0; i < box_count; i++) {
        total += boxes[i]->volume;
    }
    return total;
}

bool identical_arrays(const int **boxes_a, const int boxes_a_count, const int **boxes_b, const int boxes_b_count) {
    if (boxes_a_count != boxes_b_count) return false;
    for (int i = 0; i < boxes_a_count; i++) {
        bool match = false;
        for (int j = 0; j < boxes_a_count; j++) {
            if (*boxes_a[i] == *boxes_b[j]) match = true;
        }
        if (!match) return false;
    }
    return true;
}

bool contains(const Box **boxes, const int box_count, const Box *box) {
    for (int i = 0; i < box_count; i++) {
        if (boxes[i]->id == box->id) return true;
    }
    return false;
}


void day17_part1() {
    print_header(17, 1);
    char *input = day17_input.test_input;
    size_t len = strlen(input);

    char line[len + 1];
    strcpy(line, input);

    Box boxes[20];
    int box_count = 0;

    // int goal = 150;
    int goal = 25;

    char *ptr = strtok(line, ",");
    while (ptr != NULL) {
        boxes[box_count].id = box_count;
        boxes[box_count++].volume = atoi(ptr);
        ptr = strtok(nullptr, ",");
    }
    int total;

    iter *i = newArrayIter(&boxes, box_count, 8);
    combinations(boxes, box_count, 8, 8);
    int *c;
    while (has_next(i)) {
        c = (int *) next(i);
        for (int j = 0; j < box_count; j++) {
            printf("%d,", c[j]);
        }
        printf("\n");
    }

    // print_ln("%i", total);
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
