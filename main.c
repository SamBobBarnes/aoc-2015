#include <stdio.h>
#include "helpers.h"
#include "days.h"

int main(void) {
    printf("\nAdvent of Code 2015 in C\n");

    constexpr int day = 9;
    IDay day_to_run;
    switch (day) {
        case 1:
            day_to_run = day1;
            break;
        case 2:
            day_to_run = day2;
            break;
        case 3:
            day_to_run = day3;
            break;
        case 4:
            day_to_run = day4;
            break;
        case 5:
            day_to_run = day5;
            break;
        case 6:
            day_to_run = day6;
            break;
        case 7:
            day_to_run = day7;
            break;
        case 8:
            day_to_run = day8;
            break;
        case 9:
            day_to_run = day9;
            break;
        default:
            return 1;
    }

    day_to_run.part1();
    day_to_run.part2();

    return 0;
}
