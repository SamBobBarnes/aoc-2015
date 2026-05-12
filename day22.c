//
// Created by sb17057 on 4/9/2026.
//

#include "day22.h"
#include "Inputs/day22.h"

#include <string.h>

#include "priority-q.h"

typedef struct {
    int cost;
    bool instant;
    int damage;
    int armor;
    int recharge;
    int heal;
    int duration;
} Spell;

void day22_part1() {
    print_header(22, 1);
    const char *input = day22_input.test_input;
    const size_t len = strlen(input);

    Spell spells[5] = {
        {53, true, 4}, // magic missile
        {73, true, 2, 0, 0, 2}, // drain
        {113, false, 0, 7, 0, 0, 6}, // shield
        {173, false, 3, 0, 0, 0, 6}, // poison
        {229, false, 0, 0, 101, 0, 5} // recharge
    };

    PriorityQueue *q;
}

void day22_part2() {
    print_header(22, 2);
    const char *input = day22_input.test_input;
    const size_t len = strlen(input);
}

IDay day22 = {
    .part1 = day22_part1,
    .part2 = day22_part2
};
