#include <stdio.h>
#include "iday.h"
#include "days.h"

int main(void) {
    printf("\nAdvent of Code 2015 in C\n");

    constexpr int day = 1;
    IDay day_to_run;
    switch (day) {
        case 1:
            day_to_run = day1;
            break;
        case 2:
            day_to_run = day2;
            break;
        default:
            return 1;
    }

    day_to_run.part1();
    day_to_run.part2();

    return 0;
}