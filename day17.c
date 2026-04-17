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

void recurse_boxes(const Box **boxes, const int box_count, Box boxes_used[box_count], const int box_used_count,
                   int ***combinations, int **combination_counts, int *total, const int goal) {
    int total_volume = total_vol(&boxes_used, box_count);
    if (total_volume > goal) return; // if goal exceeded return
    if (total_volume == goal) {
        // if goal met
        for (int i = 0; i < *total; i++) {
            // if an identical set is found, dont double count return
            int boxids_used[box_used_count];
            for (int j = 0; j < box_used_count; j++) boxids_used[j] = boxes_used[j].id;
            if (identical_arrays(combinations[i], *combination_counts[i], (int **) &boxids_used, box_used_count))
                return;
        }
        for (int i = 0; i < box_used_count; i++) {
            // finally, write to combinations and add to total
            *combinations[*total][i] = boxes_used[i].id;
        }
        *combination_counts[*total] = box_used_count;
        (*total)++;
    }

    for (int i = 0; i < box_count; i++) {
        if (contains(&boxes_used, box_used_count, boxes[i])) continue; // if box already in set, continue to the next
        boxes_used[box_used_count] = *boxes[i];
        recurse_boxes(boxes, box_count, boxes_used, box_used_count + 1, combinations, combination_counts, total,
                      goal); // recurse
    }
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

    int *combinations[20 * 20][box_count];
    int combination_counts[20 * 20];
    Box boxes_used[20];
    int box_used_count = 0;

    int total;

    recurse_boxes((Box **) &boxes, box_count, boxes_used, box_used_count, (int ***) combinations,
                  (int **) &combination_counts, &total, goal);
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
