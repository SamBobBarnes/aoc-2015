//
// Created by sb17057 on 4/9/2026.
//

#include "day9.h"
#include "Inputs/day9.h"

#include <math.h>
#include <stdint.h>
#include <string.h>

#include "day9-pq.h"
#include "debug.h"


typedef struct Link {
    int dest;
    int distance;
} Link;

typedef struct Node {
    int id;
    char *name;
    int link_count;
    Link links[8];
} Node;

typedef struct Route {
    int src_id;
    int dest_id;
    int distance;
} Route;


int get_city(const Node *cities, const int city_count, const char *name) {
    for (int i = 0; i < city_count; i++)
        if (strcmp(cities[i].name, name) == 0)
            return i;
    return -1;
}

void day9_part1() {
    print_header(9, 1);
    const char *input = day9_input.input;
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

    Node cities[row_count];
    int city_count = 0;

    for (int i = 0; i < row_count; i++) {
        char *ptr = strtok(rows[i], " ");
        char *city1 = ptr;
        int c1_index = get_city(cities, city_count, city1);
        if (c1_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city1;
            cities[city_count].link_count = 0;
            c1_index = city_count;
            city_count++;
        }
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");
        char *city2 = ptr;
        int c2_index = get_city(cities, city_count, city2);
        if (c2_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city2;
            cities[city_count].link_count = 0;
            c2_index = city_count;
            city_count++;
        }
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");

        int dist = atoi(ptr);
        cities[c1_index].links[cities[c1_index].link_count].dest = cities[c2_index].id;
        cities[c1_index].links[cities[c1_index].link_count].distance = dist;
        cities[c1_index].link_count++;
        cities[c2_index].links[cities[c2_index].link_count].dest = cities[c1_index].id;
        cities[c2_index].links[cities[c2_index].link_count].distance = dist;
        cities[c2_index].link_count++;
    }

    if (debugging) {
        for (int i = 0; i < city_count; i++)
            for (int j = 0; j < cities[i].link_count; j++)
                printf("%s(%i) to %s(%i) in %i\n", cities[i].name, cities[i].id, cities[cities[i].links[j].dest].name,
                       cities[i].links[j].dest, cities[i].links[j].distance);
    }

    // use Dijkstra

    int route_count = 0;
    for (int i = 0; i < city_count - 1; i++)
        for (int j = i + 1; j < city_count; j++)
            route_count++;
    Route routes[route_count];

    int route_index = 0;

    for (int i = 0; i < city_count - 1; i++)
        for (int j = i + 1; j < city_count; j++) {
            routes[route_index].src_id = i;
            routes[route_index].dest_id = j;
            routes[route_index].distance = INT_MAX;

            PriorityQueue q = {{(ItemPriority){0, i, (History){{0}, 0}}}, 1, false};
            while (peek(&q).id != -1) {
                const ItemPriority ip = dequeue(&q);
                const Node *city = &cities[ip.id];

                if (debugging) {
                    printf("{\n  id: %i\n  name: %s\n  priority: %i\n  visited_count: %i\n  visited: [\n", city->id,
                           city->name, ip.priority, ip.visited.visited_count);
                    for (int k = 0; k < ip.visited.visited_count; k++) {
                        printf("    {\n      id: %i\n      name: %s\n    }\n", ip.visited.visited_ids[k],
                               cities[ip.visited.visited_ids[k]].name);
                    }
                    printf("  ]\n}\n");
                    print_ln("Viewing %s(%i) at %i dist having visited %i cities", city->name, city->id, ip.priority,
                             ip.visited.visited_count);
                }

                if (city->id == routes[route_index].dest_id) {
                    routes[route_index].distance = ip.priority;
                    debug_ln("ending at %i dist", ip.priority);
                    break;
                }
                History node_history = ip.visited;
                node_history.visited_ids[node_history.visited_count] = city->id;
                node_history.visited_count++;

                for (int k = 0; k < city->link_count; k++) {
                    const Link *link = &city->links[k];
                    bool already_visited = false;
                    // if link is dest, and we are not on the last step
                    if (link->dest == routes[route_index].dest_id && node_history.visited_count != city_count - 1)
                        already_visited = true;
                    // if link has been visited in this route
                    for (int l = 0; l < node_history.visited_count; l++) {
                        if (link->dest == node_history.visited_ids[l]) already_visited = true;
                    }
                    if (already_visited) {
                        debug_ln("%s was already visited", cities[link->dest].name);
                        continue;
                    }

                    debug_ln("enqueuing %s", cities[link->dest].name);

                    enqueue(&q, (ItemPriority){ip.priority + link->distance, link->dest, node_history});
                }
            }

            char *c1_name = cities[i].name;
            char *c2_name = cities[j].name;
            int c1_id = cities[i].id;
            int c2_id = cities[j].id;
            int distance = routes[route_index].distance;

            debug("%s(%i) to %s(%i) in %i\n", c1_name, c1_id, c2_name, c2_id, distance);
            route_index++;
            if (debugging) {
                print_spacer();
            }
        }

    // all shortest routes have been found
    // now find the shortest of those routes
    int min = INT_MAX;

    for (int i = 0; i < route_count; i++) {
        if (routes[i].distance < min) min = routes[i].distance;
    }

    printf("The shortest route to visit each city is %i units long", min);
}

int factorial(const int N) {
    int fact = 1;

    // Loop from 1 to N to get the factorial
    for (int i = 1; i <= N; i++) {
        fact *= i;
    }

    return fact;
}

void day9_part2() {
    print_header(9, 2);
    const char *input = day9_input.input;
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

    Node cities[row_count];
    int city_count = 0;

    for (int i = 0; i < row_count; i++) {
        char *ptr = strtok(rows[i], " ");
        char *city1 = ptr;
        int c1_index = get_city(cities, city_count, city1);
        if (c1_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city1;
            cities[city_count].link_count = 0;
            c1_index = city_count;
            city_count++;
        }
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");
        char *city2 = ptr;
        int c2_index = get_city(cities, city_count, city2);
        if (c2_index == -1) {
            cities[city_count].id = city_count;
            cities[city_count].name = city2;
            cities[city_count].link_count = 0;
            c2_index = city_count;
            city_count++;
        }
        strtok(nullptr, " ");
        ptr = strtok(nullptr, " ");

        int dist = atoi(ptr);
        cities[c1_index].links[cities[c1_index].link_count].dest = cities[c2_index].id;
        cities[c1_index].links[cities[c1_index].link_count].distance = dist;
        cities[c1_index].link_count++;
        cities[c2_index].links[cities[c2_index].link_count].dest = cities[c1_index].id;
        cities[c2_index].links[cities[c2_index].link_count].distance = dist;
        cities[c2_index].link_count++;
    }

    if (debugging) {
        for (int i = 0; i < city_count; i++)
            for (int j = 0; j < cities[i].link_count; j++)
                printf("%s(%i) to %s(%i) in %i\n", cities[i].name, cities[i].id, cities[cities[i].links[j].dest].name,
                       cities[i].links[j].dest, cities[i].links[j].distance);
    }

    int route_count = 0;
    for (int i = 0; i < city_count - 1; i++)
        for (int j = i + 1; j < city_count; j++)
            route_count++;
    Route routes[route_count];

    int route_index = 0;

    int possibilities = 0;
    int paths[50000][8];


    for (int i0 = 0; i0 < 8; i0++)
        for (int i1 = 0; i1 < 8; i1++)
            for (int i2 = 0; i2 < 8; i2++)
                for (int i3 = 0; i3 < 8; i3++)
                    for (int i4 = 0; i4 < 8; i4++)
                        for (int i5 = 0; i5 < 8; i5++)
                            for (int i6 = 0; i6 < 8; i6++)
                                for (int i7 = 0; i7 < 8; i7++) {
                                    if (
                                        i0 == i1 || i0 == i2 || i0 == i3 || i0 == i4 || i0 == i5 || i0 == i6 || i0 == i7
                                        ||
                                        i1 == i2 || i1 == i3 || i1 == i4 || i1 == i5 || i1 == i6 || i1 == i7 ||
                                        i2 == i3 || i2 == i4 || i2 == i5 || i2 == i6 || i2 == i7 ||
                                        i3 == i4 || i3 == i5 || i3 == i6 || i3 == i7 ||
                                        i4 == i5 || i4 == i6 || i4 == i7 ||
                                        i5 == i6 || i5 == i7 ||
                                        i6 == i7
                                    )
                                        continue;
                                    paths[possibilities][0] = i0;
                                    paths[possibilities][1] = i1;
                                    paths[possibilities][2] = i2;
                                    paths[possibilities][3] = i3;
                                    paths[possibilities][4] = i4;
                                    paths[possibilities][5] = i5;
                                    paths[possibilities][6] = i6;
                                    paths[possibilities++][7] = i7;
                                }

    int max = 0;

    for (int i = 0; i < possibilities; i++) {
        int running_total = 0;
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 7; k++) {
                if (cities[paths[i][j]].links[k].dest == paths[i][j + 1]) {
                    running_total += cities[paths[i][j]].links[k].distance;
                    break;
                }
            }
        }

        if (running_total > max) max = running_total;

        int c1_id = paths[i][0];
        int c2_id = paths[i][1];
        char *c1_name = cities[c1_id].name;
        char *c2_name = cities[c2_id].name;

        debug("%s(%i) to %s(%i) in %i\n", c1_name, c1_id, c2_name, c2_id, running_total);
        route_index++;
        if (debugging) {
            print_spacer();
        }
    }

    // 761 < x < 982
    printf("The longest route to visit each city is %i units long", max);
}

IDay day9 = {
    .part1 = day9_part1,
    .part2 = day9_part2
};
