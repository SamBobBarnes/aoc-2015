//
// Created by sb17057 on 4/9/2026.
//

#include "day24.h"
#include "Inputs/day24.h"

#include <string.h>

#include "debug.h"

int calculate_entanglement(const int *pkgs, const int len) {
    int e = 1;
    for (int i = 0; i < len; i++)
        e *= pkgs[i];
    return e;
}

int get_pkg_total(const int *pkgs, const int len) {
    int t = 0;
    for (int i = 0; i < len; i++)
        t += pkgs[i];
    return t;
}

bool has_overlap(const int a_len, const int a[a_len], const int b_len, const int b[b_len], const int c_len,
                 const int c[c_len]) {
    for (int i = 0; i < a_len; i++)
        for (int j = 0; j < b_len; j++)
            for (int k = 0; k < c_len; k++)
                if (a[i] == b[j] || a[i] == c[k] || b[j] == c[k]) return true;
    return false;
}

void recurse_packages(const int len, const int pkgs[len], int groups[len][len], int group_counts[len], int *group_index,
                      const int index, const int current_list_len, int current_list[current_list_len],
                      const int target) {
    const int total = get_pkg_total(current_list, current_list_len);
    if (total > target) return;
    if (total == target) {
        for (int i = 0; i < current_list_len; i++) {
            groups[*group_index][i] = current_list[i];
        }
        group_counts[*group_index] = current_list_len;
        (*group_index)++;
        return;
    }
    if (index == len) return;
    for (int i = index; i < len; i++) {
        int new_list[current_list_len + 1];
        for (int j = 0; j < current_list_len; j++) {
            new_list[j] = current_list[j];
        }
        new_list[current_list_len] = pkgs[i];
        recurse_packages(len, pkgs, groups, group_counts, group_index, i + 1, current_list_len + 1, new_list, target);
    }
}

void day24_part1() {
    print_header(24, 1);
    const char *input = day24_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int count = GetRowCount(input, len, &max_row_size);
    char rows[count][max_row_size];
    SplitIntoRows(input, len, count, max_row_size, rows);

    int pkgs[count];
    int index = 0;
    for (int i = count - 1; i >= 0; i--)
        pkgs[index++] = atoi(rows[i]);

    int total = get_pkg_total(pkgs, count);
    int split = total / 3;
    debug_ln("%i must be split into groups of %i", total, split);
    int group_count = 200;
    int groups[group_count][count];
    int group_counts[group_count];
    int group_index = 0;
    int fake_list[1];
    recurse_packages(count, pkgs, groups, group_counts, &group_index, 0, 0, fake_list, split);
    debug_ln("%i groups created", group_index);

    if (debugging)
        for (int i = 0; i < group_index; i++) {
            for (int j = 0; j < group_counts[i]; j++) {
                printf("%i,", groups[i][j]);
            }
            printf("\n");
        }


    int *sets[2000][3];
    int set_counts[2000][3];
    int set_count = 0;

    for (int i = 0; i < group_index - 2; i++)
        for (int j = i + 1; j < group_index - 1; j++)
            for (int k = j + 1; k < group_index; k++) {
                if (!has_overlap(group_counts[i], groups[i], group_counts[j], groups[j], group_counts[k], groups[k])) {
                    sets[set_count][0] = groups[i];
                    set_counts[set_count][0] = group_counts[i];
                    sets[set_count][1] = groups[j];
                    set_counts[set_count][1] = group_counts[j];
                    sets[set_count][2] = groups[k];
                    set_counts[set_count][2] = group_counts[k];

                    set_count++;
                }
            }

    // order sets by length, entanglement

    bool sorted = false;
    while (!sorted) {
        bool switched = false;

        for (int i = 1; i < set_count; i++) {
            int a_min = __min(__min(set_counts[i-1][0], set_counts[i-1][1]), set_counts[i-1][2]);
            int b_min = __min(__min(set_counts[i][0], set_counts[i][1]), set_counts[i][2]);
            if (a_min > b_min) {
                int *temp[3] = {sets[i][0], sets[i][1], sets[i][2]};
                int temp_counts[3] = {set_counts[i][0], set_counts[i][1], set_counts[i][2]};
                sets[i][0] = sets[i - 1][0];
                sets[i][1] = sets[i - 1][1];
                sets[i][2] = sets[i - 1][2];

                set_counts[i][0] = set_counts[i - 1][0];
                set_counts[i][1] = set_counts[i - 1][1];
                set_counts[i][2] = set_counts[i - 1][2];

                sets[i - 1][0] = temp[0];
                sets[i - 1][1] = temp[1];
                sets[i - 1][2] = temp[2];

                set_counts[i - 1][0] = temp_counts[0];
                set_counts[i - 1][1] = temp_counts[1];
                set_counts[i - 1][2] = temp_counts[2];

                switched = true;
            } else if (a_min == b_min) {
                int a_ents[3] = {
                    calculate_entanglement(sets[i - 1][0], set_counts[i - 1][0]),
                    calculate_entanglement(sets[i - 1][1], set_counts[i - 1][1]),
                    calculate_entanglement(sets[i - 1][2], set_counts[i - 1][2])
                };
                int min_a = set_counts[i - 1][0];
                int min_a_ent = a_ents[0];
                if (set_counts[i - 1][1] < min_a || (set_counts[i - 1][1] == min_a && a_ents[1] < min_a_ent)) {
                    min_a = set_counts[i - 1][1];
                    min_a_ent = a_ents[1];
                }
                if (set_counts[i - 1][2] < min_a || (set_counts[i - 1][2] == min_a && a_ents[2] < min_a_ent)) {
                    min_a = set_counts[i - 1][2];
                    min_a_ent = a_ents[2];
                }

                int b_ents[3] = {
                    calculate_entanglement(sets[i][0], set_counts[i][0]),
                    calculate_entanglement(sets[i][1], set_counts[i][1]),
                    calculate_entanglement(sets[i][2], set_counts[i][2])
                };
                int min_b = set_counts[i][0];
                int min_b_ent = b_ents[0];
                if (set_counts[i][1] < min_b || (set_counts[i][1] == min_b && b_ents[1] < min_b_ent)) {
                    min_b = set_counts[i - 1][1];
                    min_b_ent = b_ents[1];
                }
                if (set_counts[i][2] < min_b || (set_counts[i][2] == min_b && b_ents[2] < min_b_ent)) {
                    min_b = set_counts[i][2];
                    min_b_ent = b_ents[2];
                }

                if (min_a_ent > min_b_ent) {
                    int *temp[3] = {sets[i][0], sets[i][1], sets[i][2]};
                    int temp_counts[3] = {set_counts[i][0], set_counts[i][1], set_counts[i][2]};
                    sets[i][0] = sets[i - 1][0];
                    sets[i][1] = sets[i - 1][1];
                    sets[i][2] = sets[i - 1][2];

                    set_counts[i][0] = set_counts[i - 1][0];
                    set_counts[i][1] = set_counts[i - 1][1];
                    set_counts[i][2] = set_counts[i - 1][2];

                    sets[i - 1][0] = temp[0];
                    sets[i - 1][1] = temp[1];
                    sets[i - 1][2] = temp[2];

                    set_counts[i - 1][0] = temp_counts[0];
                    set_counts[i - 1][1] = temp_counts[1];
                    set_counts[i - 1][2] = temp_counts[2];

                    switched = true;
                }
            }
        }
        if (!switched) sorted = true;
    }


    int a_ents[3] = {
        calculate_entanglement(sets[0][0], set_counts[0][0]),
        calculate_entanglement(sets[0][1], set_counts[0][1]),
        calculate_entanglement(sets[0][2], set_counts[0][2])
    };
    int min_a = set_counts[0][0];
    int min_a_ent = a_ents[0];
    if (set_counts[0][1] < min_a || (set_counts[0][1] == min_a && a_ents[1] < min_a_ent)) {
        min_a = set_counts[0][1];
        min_a_ent = a_ents[1];
    }
    if (set_counts[0][2] < min_a || (set_counts[0][2] == min_a && a_ents[2] < min_a_ent)) {
        min_a = set_counts[0][2];
        min_a_ent = a_ents[2];
    }

    const int smallest = min_a_ent;

    printf("%i is the smallest quantum entanglement", smallest);
}

void day24_part2() {
    print_header(24, 2);
    const char *input = day24_input.test_input;
    const size_t len = strlen(input);
}

IDay day24 = {
    .part1 = day24_part1,
    .part2 = day24_part2
};
