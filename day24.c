//
// Created by sb17057 on 4/9/2026.
//

#include "day24.h"
#include "Inputs/day24.h"

#include <stdint.h>
#include <string.h>

#include "debug.h"

uint64_t calculate_entanglement(const int *pkgs, const int len) {
    uint64_t e = 1;
    for (int i = 0; i < len; i++)
        e *= (uint64_t) pkgs[i];
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

typedef struct {
    long long qe;
    int ct;
} Stack;

Stack recurse_pkgs(const int *pkgs, const int len, const int pos, const int remaining_wt, const Stack current) {
    if (remaining_wt == 0) return current;
    if (remaining_wt < 0 || pos == len) return (Stack){LONG_MAX, INT_MAX};
    const Stack included = recurse_pkgs(pkgs, len, pos + 1, remaining_wt - pkgs[pos],
                                        (Stack){current.qe * pkgs[pos], current.ct + 1});
    const Stack notIncluded = recurse_pkgs(pkgs, len, pos + 1, remaining_wt, current);

    if (included.ct < notIncluded.ct) return included;
    if (notIncluded.ct < included.ct) return notIncluded;
    if (included.qe < notIncluded.qe) return included;
    return notIncluded;
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
    // int index = 0;
    // for (int i = count - 1; i >= 0; i--)
    //     pkgs[index++] = atoi(rows[i]);
    for (int i = 0; i < count; i++)
        pkgs[i] = atoi(rows[i]);

    int total = get_pkg_total(pkgs, count);
    int split = total / 3;
    debug_ln("%i must be split into groups of %i", total, split);

    printf("%lld is the smallest qe", recurse_pkgs(pkgs, count, 0, split, (Stack){1, 0}).qe);
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
