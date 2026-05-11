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
    int cost;
} Stats;

typedef struct {
    int cost;
    int damage;
    int armor;
} Gear;

bool do_we_win(const Stats *player, const Stats *opponent) {
    int attacking_rounds = opponent->hp / __max(1, player->damage - opponent->armor);
    int defending_rounds = player->hp / __max(1, opponent->damage - player->armor);
    if (defending_rounds > attacking_rounds)return true;
    if (defending_rounds < attacking_rounds)return false;

    int attacking_remainder = opponent->hp % __max(1, player->damage - opponent->armor);
    int defending_remainder = player->hp % __max(1, opponent->damage - player->armor);
    if (defending_remainder == 0 && attacking_remainder > 0) return false;
    return true;
}

void day21_part1() {
    print_header(21, 1);

    Stats opponent = (Stats){104, 8, 1};

    Gear weapons[5] = {
        (Gear){8, 4, 0},
        (Gear){10, 5, 0},
        (Gear){25, 6, 0},
        (Gear){40, 7, 0},
        (Gear){74, 8, 0}
    };

    Gear armor[6] = {
        (Gear){0, 0, 0},
        (Gear){13, 0, 1},
        (Gear){31, 0, 2},
        (Gear){53, 0, 3},
        (Gear){75, 0, 4},
        (Gear){102, 0, 5}
    };

    Gear rings[7] = {
        (Gear){0, 0, 0},
        (Gear){25, 1, 0},
        (Gear){50, 2, 0},
        (Gear){100, 3, 0},
        (Gear){20, 0, 1},
        (Gear){40, 0, 2},
        (Gear){80, 0, 3}
    };

    int min = INT_MAX;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < 7; k++)
                for (int l = 0; l < 7; l++) {
                    if (k > 0 && l > 0 && k == l) continue; // cant have the same rings
                    const Stats player = (Stats){
                        100, weapons[i].damage + rings[k].damage + rings[l].damage,
                        armor[j].armor + rings[k].armor + rings[l].armor,
                        weapons[i].cost + armor[j].cost + rings[k].cost + rings[l].cost
                    };
                    if (do_we_win(&player, &opponent) && player.cost < min) {
                        print_ln("hp:%i, d:%i, a:%i, $%i", player.hp, player.damage, player.armor, player.cost);
                        min = player.cost;
                    }
                }

    printf("%i", min);
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
