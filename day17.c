//
// Created by sb17057 on 4/9/2026.
//

#include "day17.h"
#include "Inputs/day17.h"

#include <string.h>

typedef struct {
    int id;
    int volume;
} Box;

int total_vol(Box *boxes, int box_count) {
    int total = 0;
    for (int i = 0; i < box_count; i++) {
        total += boxes[i].volume;
    }
    return total;
}

bool identical_arrays(const Box *boxes_a, const int boxes_a_count, const Box *boxes_b, const int boxes_b_count) {
    if (boxes_a_count != boxes_b_count) return false;
    for (int i = 0; i < boxes_a_count; i++) {
        bool match = false;
        for (int j = 0; j < boxes_a_count; j++) {
            if (boxes_a[i].id == boxes_b[j].id) match = true;
        }
        if (!match) return false;
    }
    return true;
}

bool contains(const Box *boxes, const int box_count, const Box *box) {
    for (int i = 0; i < box_count; i++) {
        if (boxes[i].id == box->id) return true;
    }
    return false;
}

void recurse_boxes(const Box *boxes, const int box_count, Box boxes_used[box_count], const int box_used_count,
                   Box *combinations[][box_count], int *combination_counts, int *total, const int goal) {
    int total_volume = total_vol(boxes_used, box_count);
    if (total_volume > goal) return;
    if (total_volume == goal) {
        for (int i = 0; i < *total; i++) {
            if (identical_arrays((Box *) combinations[i], combination_counts[i], boxes_used, box_used_count)) return;
        }
        for (int i = 0; i < box_used_count; i++) {
            *combinations[*total][i] = boxes_used[i];
        }
        combination_counts[*total] = box_used_count;
        (*total)++;
    }

    for (int i = 0; i < box_count; i++) {
        if (contains(boxes_used, box_used_count, &boxes[i])) continue;
        boxes_used[box_used_count] = boxes[i];
        recurse_boxes(boxes, box_count, boxes_used, box_used_count + 1, combinations, combination_counts, total, goal);
    }
}

void day17_part1() {
    print_header(17, 1);
    char *input = day17_input.test_input;

    Box boxes[20];
    int box_count = 0;

    // int volume = 150;
    int volume = 25;

    char *ptr = strtok(input, ",");
    while (ptr != NULL) {
        boxes[box_count].id = box_count;
        boxes[box_count++].volume = atoi(ptr);
        ptr = strtok(nullptr, ",");
    }
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
