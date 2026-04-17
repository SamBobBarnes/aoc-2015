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
    if (capacity < 0) capacity = 0;
    if (durability < 0) durability = 0;
    if (flavor < 0) flavor = 0;
    if (texture < 0) texture = 0;
    return capacity * durability * flavor * texture;
}

int recurse_ingredients(const Ingredient *ingredients, const int ingredient_count) {
    int max = 0;
    for (int a = 0; a <= 100; a++)
        for (int b = 0; b <= 100; b++) {
            if (ingredient_count > 2) {
                for (int c = 0; c <= 100; c++)
                    for (int d = 0; d <= 100; d++)
                        if (a + b + c + d == 100) {
                            const int value = calculate_cookie_value(a, b, c, d, ingredients, ingredient_count);
                            // debug_ln("[%i,%i,%i,%i]=%i", a, b, c, d, value);
                            if (value > max) max = value;
                        }
            } else {
                if (a + b == 100) {
                    const int value = calculate_cookie_value(a, b, 0, 0, ingredients, ingredient_count);
                    debug_ln("[%i,%i]=%i", a, b, value);
                    if (value > max) max = value;
                }
            }
        }

    return max;
}

int calculate_cookie_calories(const int a, const int b, const int c, const int d, const Ingredient *ingredients,
                              const int ingredient_count) {
    int calories = a * ingredients[0].calories + b * ingredients[1].calories;
    if (ingredient_count > 2)
        calories += c * ingredients[2].calories + d * ingredients[3].calories;
    return calories;
}

int recurse_ingredients_p2(const Ingredient *ingredients, const int ingredient_count) {
    int max = 0;
    for (int a = 0; a <= 100; a++)
        for (int b = 0; b <= 100; b++) {
            if (ingredient_count > 2) {
                for (int c = 0; c <= 100; c++)
                    for (int d = 0; d <= 100; d++)
                        if (a + b + c + d == 100 && calculate_cookie_calories(a, b, c, d, ingredients, ingredient_count)
                            == 500) {
                            const int value = calculate_cookie_value(a, b, c, d, ingredients, ingredient_count);
                            // debug_ln("[%i,%i,%i,%i]=%i", a, b, c, d, value);
                            if (value > max) max = value;
                        }
            } else {
                if (a + b == 100 && calculate_cookie_calories(a, b, 0, 0, ingredients, ingredient_count) == 500) {
                    const int value = calculate_cookie_value(a, b, 0, 0, ingredients, ingredient_count);
                    debug_ln("[%i,%i]=%i", a, b, value);
                    if (value > max) max = value;
                }
            }
        }

    return max;
}

void day15_part1() {
    print_header(15, 1);
    const char *input = day15_input.input;
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
        strtok(nullptr, " ");
        size_t capacity_len = strlen(capacity);
        capacity[capacity_len - 1] = '\0';
        ingredients[i].capacity = atoi(capacity);
        char *durability = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t durability_len = strlen(durability);
        durability[durability_len - 1] = '\0';
        ingredients[i].durability = atoi(durability);
        char *flavor = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t flavor_len = strlen(flavor);
        flavor[flavor_len - 1] = '\0';
        ingredients[i].flavor = atoi(flavor);
        char *texture = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t texture_len = strlen(texture);
        texture[texture_len - 1] = '\0';
        ingredients[i].texture = atoi(texture);
        ingredients[i].calories = atoi(strtok(nullptr, " "));
    }

    for (int i = 0; i < row_count; i++) {
        debug_ln("%s: c: %i, r: %i, d: %i, f: %i, t: %i", ingredients[i].name, ingredients[i].capacity,
                 ingredients[i].durability, ingredients[i].flavor, ingredients[i].texture);
    }

    int max = recurse_ingredients(ingredients, row_count);

    print_ln("Best cookie is %i", max);
}

void day15_part2() {
    print_header(15, 2);
    const char *input = day15_input.input;
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
        strtok(nullptr, " ");
        size_t capacity_len = strlen(capacity);
        capacity[capacity_len - 1] = '\0';
        ingredients[i].capacity = atoi(capacity);
        char *durability = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t durability_len = strlen(durability);
        durability[durability_len - 1] = '\0';
        ingredients[i].durability = atoi(durability);
        char *flavor = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t flavor_len = strlen(flavor);
        flavor[flavor_len - 1] = '\0';
        ingredients[i].flavor = atoi(flavor);
        char *texture = strtok(nullptr, " ");
        strtok(nullptr, " ");
        size_t texture_len = strlen(texture);
        texture[texture_len - 1] = '\0';
        ingredients[i].texture = atoi(texture);
        ingredients[i].calories = atoi(strtok(nullptr, " "));
    }

    for (int i = 0; i < row_count; i++) {
        debug_ln("%s: c: %i, r: %i, d: %i, f: %i, t: %i", ingredients[i].name, ingredients[i].capacity,
                 ingredients[i].durability, ingredients[i].flavor, ingredients[i].texture);
    }

    int max = recurse_ingredients_p2(ingredients, row_count);

    print_ln("Best cookie is %i", max);
}

IDay day15 = {
    .part1 = day15_part1,
    .part2 = day15_part2
};
