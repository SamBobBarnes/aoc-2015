//
// Created by sb17057 on 4/9/2026.
//

#include "day22.h"
#include "Inputs/day22.h"

#include <stdint.h>
#include <string.h>

#include "dictionary.h"
#include "priority-q.h"

typedef struct {
    uint8_t id;
    uint8_t cost;
    bool instant;
    uint8_t damage;
    uint8_t armor;
    uint8_t recharge;
    uint8_t heal;
    uint8_t duration;
} Spell;

typedef struct {
    uint8_t id;
    uint8_t time_remaining;
    uint8_t dmg;
    uint8_t armor;
    uint8_t recharge;
} Effect;

enum FightResult {
    PlayerWin,
    BossWin,
    NoWin
};

typedef struct FightState FightState;

struct FightState {
    int player_hp;
    int player_mana;
    int mana_used;
    int boss_hp;
    int boss_dmg;
    enum FightResult result;
    int effect_count;
    Effect effects[5];
    Spell *spell;
    FightState *prev;
};

typedef struct {
    int player_hp;
    int boss_hp;
    int mana_used;
    FightState *state;
} VisitedState;

FightState *duplicate_fight_state(FightState *state) {
    FightState *fight_state = malloc(sizeof(FightState));
    fight_state->player_hp = state->player_hp;
    fight_state->player_mana = state->player_mana;
    fight_state->mana_used = state->mana_used;
    fight_state->boss_hp = state->boss_hp;
    fight_state->boss_dmg = state->boss_dmg;
    fight_state->effect_count = 0;
    fight_state->result = NoWin;
    fight_state->prev = state;
    return fight_state;
}

int state_key(const FightState *state) {
    return state->player_hp * 100 + state->boss_hp;
}

VisitedState *create_visited_state(FightState *state) {
    VisitedState *visited = malloc(sizeof(VisitedState));
    visited->player_hp = state->player_hp;
    visited->boss_hp = state->boss_hp;
    visited->mana_used = state->mana_used;
    visited->state = state;

    return visited;
}

FightState *resolve_state(FightState *state, Spell *spell) {
    FightState *fight_state = duplicate_fight_state(state);
    fight_state->spell = spell;

    //player turn

    // evaluate existing effects
    for (int i = 0; i < state->effect_count; i++) {
        if (state->effects[i].time_remaining == 0) {
            // spell falls off if duration is 0
            continue;
        }

        fight_state->boss_hp -= state->effects[i].dmg; // evaluate effect damage
        fight_state->player_mana += state->effects[i].recharge; // evaluate effect mana gain

        if (state->effects[i].time_remaining - 1 == 0) {
            // spell falls off if duration is 0
            continue;
        }

        fight_state->effects[fight_state->effect_count] = state->effects[i]; // add effect to next state
        fight_state->effects[fight_state->effect_count++].time_remaining--; // decrease effect duration
    }

    if (fight_state->boss_hp <= 0) {
        // if player has dealt a killing blow
        fight_state->result = PlayerWin;
        return fight_state; // player wins
    }

    if (spell->cost > fight_state->player_mana) {
        // if casting would make us have negative mana, we lose
        fight_state->result = BossWin;
        return fight_state;
    }

    if (spell->instant) {
        // evaluate instant
        fight_state->player_hp += spell->heal; // heal with instant
        fight_state->boss_hp -= spell->damage; // deal damage with instant
    } else {
        fight_state->effects[fight_state->effect_count++] = (Effect){
            // if spell is not an instant, store the effect
            spell->id, spell->duration, spell->damage, spell->armor, spell->recharge
        };
    }

    // evaluate spell cost
    fight_state->mana_used += spell->cost; // add cost to mana used
    fight_state->player_mana -= spell->cost; // remove used mana

    int armor = 0;

    // boss turn

    // apply other effects
    for (int i = 0; i < fight_state->effect_count; i++) {
        fight_state->boss_hp -= fight_state->effects[i].dmg; // damage boss with effect
        fight_state->player_mana += fight_state->effects[i].recharge; // evaluate recharge
        armor += fight_state->effects[i].armor; // evaluate shield
        fight_state->effects[i].time_remaining--;
    }

    if (fight_state->boss_hp <= 0) {
        // if player has dealt a killing blow
        fight_state->result = PlayerWin;
        return fight_state; // player wins
    }
    fight_state->player_hp -= fight_state->boss_dmg - armor; // damage player
    if (fight_state->player_hp <= 0) {
        // if boss has dealt killing blow
        fight_state->result = BossWin;
        return fight_state; // player loses
    }

    return fight_state; // noone has died
}

void day22_part1() {
    print_header(22, 1);

    // int boss_hp = 14;
    // int boss_dmg = 8;
    //
    // int player_hp = 10;
    // int player_mana = 250;

    int boss_hp = 58;
    int boss_dmg = 9;

    int player_hp = 50;
    int player_mana = 500;

    Spell spells[5] = {
        {0, 53, true, 4}, // magic missile
        {1, 73, true, 2, 0, 0, 2}, // drain
        {2, 113, false, 0, 7, 0, 0, 6}, // shield
        {3, 173, false, 3, 0, 0, 0, 6}, // poison
        {4, 229, false, 0, 0, 101, 0, 5} // recharge
    };

    Dictionary dict = create_dictionary(100000);

    FightState initial_state = (FightState){player_hp, player_mana, 0, boss_hp, boss_dmg, NoWin, 0};
    VisitedState visited_state = {
        initial_state.player_hp, initial_state.boss_hp, initial_state.player_mana, &initial_state
    };
    add_to_dict(&dict, state_key(&initial_state), &visited_state);

    PriorityQueue q = create_priority_queue(1000000, false);

    enqueue(&q, new_pq_item(0, &initial_state));

    while (!is_empty(&q)) {
        FightState *state = dequeue(&q);
        if (state->result == BossWin) continue;
        if (state->result == PlayerWin) {
            printf("%i mana used to defeat the boss with %i hp left", state->mana_used, state->player_hp);
            break;
        }

        for (int i = 0; i < 5; i++) {
            bool can_add = true;
            for (int j = 0; j < state->effect_count; j++) {
                if (state->effects[j].id == spells[i].id && state->effects[j].time_remaining > 0) can_add = false;
            }
            if (can_add) {
                FightState *fight_state = resolve_state(state, &spells[i]);
                const int key = state_key(fight_state);
                VisitedState *old_state = get_from_dict(&dict, key);
                if (old_state != NULL && fight_state->result == NoWin && fight_state->mana_used < old_state->
                    mana_used) {
                    free(old_state);
                    add_to_dict(&dict, key, create_visited_state(fight_state));
                    enqueue(&q, new_pq_item(fight_state->mana_used, fight_state));
                } else if (old_state == NULL) {
                    enqueue(&q, new_pq_item(fight_state->mana_used, fight_state));
                }
            }
        }
    }
    free(dict.entries);
    free_content(&q);

    // 780 < x < 1362
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
