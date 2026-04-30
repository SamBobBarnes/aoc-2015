//
// Created by sb17057 on 4/9/2026.
//

#include "day18.h"
#include "Inputs/day18.h"

#include <string.h>

#include "debug.h"

void print_grid(const size_t row_count, const size_t row_width, const bool grid[row_width][row_count]) {
    if (debugging) {
        for (int y = 0; y < row_count; y++) {
            for (int x = 0; x < row_width; x++) {
                printf("%c", grid[x][y] ? '#' : '.');
            }
            print_ln("");
        }
    }
}

void day18_part1() {
    print_header(18, 1);
    const char *input = day18_input.input;
    const size_t len = strlen(input);

    int row_width = 0;
    int row_count = GetRowCount(input, len, &row_width);
    char rows[row_count][row_width];
    SplitIntoRows(input, len, &row_count, &row_width, rows);

    bool grid[row_width][row_count];
    row_width--;
    for (int x = 0; x < row_width; x++) {
        for (int y = 0; y < row_count; y++) {
            grid[x][y] = rows[y][x] == '#';
        }
    }

    print_grid(row_count, row_width, grid);

    constexpr int rounds = 100;

    for (int i = 0; i < rounds; i++) {
        if (debugging) {
            print_spacer();
        }

        bool temp_grid[row_width][row_count];
        for (int x = 0; x < row_width; x++) {
            for (int y = 0; y < row_count; y++) {
                int total = 0;
                const bool on = grid[x][y];

                if (x > 0 && y > 0 && grid[x - 1][y - 1]) total++; // top left
                if (x > 0 && y < row_count - 1 && grid[x - 1][y + 1]) total++; // bottom left
                if (x > 0 && grid[x - 1][y]) total++; // left
                if (y > 0 && grid[x][y - 1]) total++; // top
                if (y < row_count - 1 && grid[x][y + 1]) total++; // bottom
                if (x < row_width - 1 && grid[x + 1][y]) total++; // right
                if (x < row_width - 1 && y < row_count - 1 && grid[x + 1][y + 1]) total++; // bottom right
                if (x < row_width - 1 && y > 0 && grid[x + 1][y - 1]) total++; // top right

                if ((on && (total == 2 || total == 3)) || (!on && total == 3)) temp_grid[x][y] = true;
                else temp_grid[x][y] = false;
            }
        }

        for (int x = 0; x < row_width; x++)
            for (int y = 0; y < row_count; y++)
                grid[x][y] = temp_grid[x][y];

        print_grid(10, 10, grid);
    }

    int total = 0;
    for (int x = 0; x < row_width; x++)
        for (int y = 0; y < row_count; y++)
            if (grid[x][y]) total++;

    print_ln("total lights on is %i", total);
}

void day18_part2() {
    print_header(18, 2);
    const char *input = day18_input.input;
    const size_t len = strlen(input);

    int row_width = 0;
    int row_count = GetRowCount(input, len, &row_width);
    char rows[row_count][row_width];
    SplitIntoRows(input, len, &row_count, &row_width, rows);

    bool grid[row_width][row_count];
    row_width--;
    for (int x = 0; x < row_width; x++) {
        for (int y = 0; y < row_count; y++) {
            if ((x == 0 && y == 0) || (x == 0 && y == row_count - 1) || (x == row_width - 1 && y == 0) || (
                    x == row_width - 1 && y == row_count - 1)) {
                grid[x][y] = true;
                continue;
            }
            grid[x][y] = rows[y][x] == '#';
        }
    }

    print_grid(row_count, row_width, grid);

    constexpr int rounds = 100;

    for (int i = 0; i < rounds; i++) {
        if (debugging) {
            print_spacer();
        }

        bool temp_grid[row_width][row_count];
        for (int x = 0; x < row_width; x++) {
            for (int y = 0; y < row_count; y++) {
                int total = 0;
                const bool on = grid[x][y];
                if ((x == 0 && y == 0) || (x == 0 && y == row_count - 1) || (x == row_width - 1 && y == 0) || (
                        x == row_width - 1 && y == row_count - 1)) {
                    temp_grid[x][y] = true;
                    continue;
                }
                if (x > 0 && y > 0 && grid[x - 1][y - 1]) total++; // top left
                if (x > 0 && y < row_count - 1 && grid[x - 1][y + 1]) total++; // bottom left
                if (x > 0 && grid[x - 1][y]) total++; // left
                if (y > 0 && grid[x][y - 1]) total++; // top
                if (y < row_count - 1 && grid[x][y + 1]) total++; // bottom
                if (x < row_width - 1 && grid[x + 1][y]) total++; // right
                if (x < row_width - 1 && y < row_count - 1 && grid[x + 1][y + 1]) total++; // bottom right
                if (x < row_width - 1 && y > 0 && grid[x + 1][y - 1]) total++; // top right

                if ((on && (total == 2 || total == 3)) || (!on && total == 3)) temp_grid[x][y] = true;
                else temp_grid[x][y] = false;
            }
        }

        for (int x = 0; x < row_width; x++)
            for (int y = 0; y < row_count; y++)
                grid[x][y] = temp_grid[x][y];

        print_grid(row_count, row_width, grid);
    }

    int total = 0;
    for (int x = 0; x < row_width; x++)
        for (int y = 0; y < row_count; y++)
            if (grid[x][y]) total++;

    print_ln("total lights on is %i", total);
}

IDay day18 = {
    .part1 = day18_part1,
    .part2 = day18_part2
};
