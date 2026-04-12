//
// Created by sb17057 on 4/9/2026.
//

#include "day9.h"
#include "Inputs/day9.h"

#include <string.h>

struct Node {
    int id;
    char* name;
    int link_count;
    struct Link* links;
};

struct Link {
    int dest;
    int distance;
};

int get_city(const struct Node* cities, const int city_count, const char* name) {
    for (int i = 0; i < city_count; i++)
        if (strcmp(cities[i].name, name) == 0)
            return i;
    return -1;
}

void day9_part1() {
    print_header(9, 1);
    const char *input = day9_input.test_input;
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

    struct Node cities[row_count];
    int city_count = 0;

    for (int i = 0; i < row_count; i++) {
        char *ptr = strtok(rows[i], " ");
        char *city1 = ptr;
        int c1_index = get_city(cities, city_count, city1);
        if (c1_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city1;
            cities[city_count].link_count = 0;
            cities[city_count].links = nullptr;
            c1_index = city_count;
            city_count++;
        }
        ptr = strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");
        char *city2 = ptr;
        int c2_index = get_city(cities, city_count, city2);
        if (c2_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city2;
            cities[city_count].link_count = 0;
            cities[city_count].links = nullptr;
            c2_index = city_count;
            city_count++;
        }
        ptr = strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");

        int dist = atoi(ptr);
        //todo: update list of links

    }

    for (int i = 0; i < row_count; i++)
        printf("%s -- %i -> %s\n", routes[i].src, routes[i].dist, routes[i].dest);



    // use Dijkstra
}

void day9_part2() {
    print_header(9, 2);
    const char *input = day9_input.test_input;
    const size_t len = strlen(input);
}

IDay day9 = {
    .part1 = day9_part1,
    .part2 = day9_part2
};
