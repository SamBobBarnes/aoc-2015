//
// Created by sb17057 on 4/9/2026.
//

#include "day9.h"
#include "Inputs/day9.h"

#include <string.h>

#include "day9-pq.h"


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

    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < cities[i].link_count; j++)
            printf("%s(%i) to %s(%i) in %i\n", cities[i].name, cities[i].id, cities[cities[i].links[j].dest].name,
                   cities[i].links[j].dest, cities[i].links[j].distance);


    // use Dijkstra

    int route_count = 0;
    for (int i = 0; i < city_count - 1; i++)
        for (int j = i + 1; j < city_count; j++)
            route_count++;
    Route routes[route_count];

    int route_index = 0;

    for (int i = 0; i < city_count - 1; i++)
        for (int j = i + 1; j < city_count; j++) {
            printf("%s(%i) to %s(%i) in ", cities[i].name, cities[i].id, cities[cities[i].links[j].dest].name,
                   cities[i].links[j].dest);
            routes[route_index].src_id = i;
            routes[route_index].dest_id = i;
            routes[route_index].distance = INT_MAX;

            PriorityQueue q = {{(ItemPriority){0, i, (History){{0}, 0}}}, 1};
            while (peek(&q).id != -1) {
                ItemPriority ip = dequeue(&q);
                Node *city = &cities[ip.id];
                if (city->id == routes[route_index].dest_id) {
                    routes[route_index].distance = ip.priority;
                    break;
                }
                History node_history = ip.visited;
                node_history.visited_ids[node_history.visited_count] = city->id;
                node_history.visited_count++;

                for (int k = 0; k < city->link_count; k++) {
                    Link *link = &city->links[k];
                    bool already_visited = false;
                    // if link is dest, and we are not on the last step
                    if (link->dest == routes[route_index].dest_id && node_history.visited_count != city_count - 1)
                        already_visited = true;
                    // if link has been visited in this route
                    for (int l = 0; l < node_history.visited_count; l++) {
                        if (link->dest == node_history.visited_ids[l]) already_visited = true;
                    }
                    if (already_visited) continue;

                    enqueue(&q, (ItemPriority){ip.priority + link->distance, link->dest, node_history});
                }
            }

            printf("%i\n", routes[route_index].distance);

            route_index++;
        }

    // all shortest routes have been found
    // now find the shortest of those routes
    int min = INT_MAX;

    for (int i = 0; i < route_count; i++) {
        if (routes[i].distance < min) min = routes[i].distance;
    }

    printf("The shortest route to visit each city is %i units long", min);
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
