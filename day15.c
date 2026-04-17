//
// Created by sb17057 on 4/9/2026.
//

#include "day15.h"
#include "Inputs/day15.h"

#include <string.h>

#include "debug.h"

typedef struct {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
    char *name;
} Ingredient;

int calculate_cookie_value(const int a, const int b, const int c, const int d, const Ingredient *ingredients,
                           const int ingredient_count) {
    int capacity = a * ingredients[0].capacity + b * ingredients[1].capacity;
    int durability = a * ingredients[0].durability + b * ingredients[1].durability;
    int flavor = a * ingredients[0].flavor + b * ingredients[1].flavor;
    int texture = a * ingredients[0].texture + b * ingredients[1].texture;
    if (ingredient_count > 2) {
        capacity += c * ingredients[2].capacity + d * ingredients[3].capacity;
        durability += c * ingredients[2].durability + d * ingredients[3].durability;
        flavor += c * ingredients[2].flavor + d * ingredients[3].flavor;
        texture += c * ingredients[2].texture + d * ingredients[3].texture;
    }
    return capacity * durability * flavor * texture;
}

int recurse_ingredients(const Ingredient *ingredients, const int ingredient_count, const int a, const int b,
                        const int c, const int d) {
    if (a + b + c + d == 100) {
        const int value = calculate_cookie_value(a, b, c, d, ingredients, ingredient_count);
        debug_ln("[%i,%i,%i,%i]=%i", a, b, c, d, value);
        return value;
    }
    const int cookie1 = recurse_ingredients(ingredients, ingredient_count, a + 1, b, c, d);
    const int cookie2 = recurse_ingredients(ingredients, ingredient_count, a, b + 1, c, d);
    int cookie3 = 0;
    int cookie4 = 0;
    if (ingredient_count > 2) {
        cookie3 = recurse_ingredients(ingredients, ingredient_count, a, b, c + 1, d);
        cookie4 = recurse_ingredients(ingredients, ingredient_count, a, b, c, d + 1);
    }
    int max = 0;
    if (cookie1 > max) max = cookie1;
    if (cookie2 > max) max = cookie2;
    if (cookie3 > max) max = cookie3;
    if (cookie4 > max) max = cookie4;
    return max;
}

void day15_part1() {
    print_header(15, 1);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);

    int row_count = 0;
#pragma region Split Input into rows
    int max_row_size = 0;
    int index_of_last_newline = -1;
    for (int i = 0; i < len; i++)
        if (input[i] == '\n') {
            row_count++;
            int row_len = i - index_of_last_newline;
            if (row_len > max_row_size) max_row_size = row_len;
            index_of_last_newline = i;
        }
    if (input[len - 1] != '\n') row_count++;
    char rows[row_count][max_row_size];
    int row_lengths[row_count];
    int current_row = 0;
    int row_index = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\n') {
            rows[current_row][row_index] = '\0';
            row_lengths[current_row] = row_index;
            row_index = 0;
            current_row++;
            continue;
        }
        rows[current_row][row_index] = input[i];
        row_index++;
    }
    if (input[len - 1] != '\n') {
        rows[current_row][row_index] = '\0';
        row_lengths[current_row] = row_index;
    }
#pragma endregion

    Ingredient ingredients[row_count];

    for (int i = 0; i < row_count; i++) {
        char *name = strtok(rows[i], " ");
        size_t name_len = strlen(name);
        name[name_len - 1] = '\0';
        ingredients[i].name = name;
        strtok(nullptr, " ");
        char *capacity = strtok(nullptr, " ");
        size_t capacity_len = strlen(capacity);
        capacity[capacity_len - 1] = '\0';
        ingredients[i].capacity = atoi(capacity);
        strtok(nullptr, " ");
        char *durability = strtok(nullptr, " ");
        size_t durability_len = strlen(capacity);
        durability[durability_len - 1] = '\0';
        ingredients[i].durability = atoi(durability);
        strtok(nullptr, " ");
        char *flavor = strtok(nullptr, " ");
        size_t flavor_len = strlen(capacity);
        flavor[flavor_len - 1] = '\0';
        ingredients[i].flavor = atoi(flavor);
        strtok(nullptr, " ");
        char *texture = strtok(nullptr, " ");
        size_t texture_len = strlen(capacity);
        texture[texture_len - 1] = '\0';
        ingredients[i].texture = atoi(texture);
        strtok(nullptr, " ");
        ingredients[i].calories = atoi(strtok(nullptr, " "));
    }

    int max = recurse_ingredients(ingredients, row_count, 0, 0, 0, 0);

    print_ln("Best cookie is %i", max);
}

void day15_part2() {
    print_header(15, 2);
    const char *input = day15_input.test_input;
    const size_t len = strlen(input);
}

IDay day15 = {
    .part1 = day15_part1,
    .part2 = day15_part2
};
