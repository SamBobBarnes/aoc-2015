//
// Created by sb17057 on 4/9/2026.
//

#include "day21.h"
#include "Inputs/day21.h"

#include <string.h>

typedef struct {
    int hp;
    int damage;
    int armor;
} Stats;

void day21_part1() {
    print_header(21, 1);
    bool test = true;

    Stats player;
    Stats opponent;
    if (test) {
        player = (Stats){8, 5, 5};
        opponent = (Stats){12, 7, 2};
    } else {
        player = (Stats){100, 0, 0};
        opponent = (Stats){104, 8, 1};
    }
}

void day21_part2() {
    print_header(21, 2);
    bool test = true;

    Stats player;
    Stats opponent;
    if (test) {
        player = (Stats){8, 5, 5};
        opponent = (Stats){12, 7, 2};
    } else {
        player = (Stats){100, 0, 0};
        opponent = (Stats){104, 8, 1};
    }
}

IDay day21 = {
    .part1 = day21_part1,
    .part2 = day21_part2
};
