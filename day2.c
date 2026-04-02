//
// Created by sb17057 on 4/2/2026.
//
#include "day2.h"
#include "Inputs/day2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// 2*l*w + 2*w*h + 2*h*l

void reset_temp(char *temp, int *tempi) {
    temp[0] = ' ';
    temp[1] = ' ';
    *tempi = 0;
}

void day2_part1() {
    print_header(2, 1);
    const char *input = day2_input.input;
    const size_t len = strlen(input);

    char temp[3] = "  ";
    int tempi = 0;

    int length = 0;
    int width = 0;
    int height = 0;

    int total = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == 'x') {
            if (length == 0) {
                length = atoi(temp);
                reset_temp(temp, &tempi);
            } else if (width == 0) {
                width = atoi(temp);

                reset_temp(temp, &tempi);
            }
        } else if (input[i] == '\n') {
            height = atoi(temp);
            reset_temp(temp, &tempi);

            int min = INT_MAX;
            if (length * width < min) min = length * width;
            if (height * width < min) min = height * width;
            if (length * height < min) min = length * height;

            int local_total = 2 * length * width + 2 * width * height + 2 * height * length + min;
            total += local_total;
            // printf("\n%ix%ix%i - 2*%iL*%iW + 2*%iW*%iH + 2*%iH*%iL + %i = %i\n", length, width, height, length, width,
            //        width,
            //        height, height, length, min, local_total);

            length = 0;
            width = 0;
        } else {
            // printf("Before: %s",temp);
            temp[tempi] = input[i];
            tempi++;
            // printf("After: %s",temp);
        }
    }

    printf("We will need %i sqft of wrapping paper.", total);
}

void day2_part2() {
    print_header(2, 2);
    const char *input = day2_input.input;
    const size_t len = strlen(input);

    char temp[3] = "  ";
    int tempi = 0;

    int length = 0;
    int width = 0;
    int height = 0;

    int total = 0;

    for (int i = 0; i < len; ++i) {
        if (input[i] == 'x') {
            if (length == 0) {
                length = atoi(temp);
                reset_temp(temp, &tempi);
            } else if (width == 0) {
                width = atoi(temp);

                reset_temp(temp, &tempi);
            }
        } else if (input[i] == '\n') {
            height = atoi(temp);
            reset_temp(temp, &tempi);

            int min = INT_MAX;
            if ((length + width) * 2 < min) min = (length + width) * 2;
            if ((height + width) * 2 < min) min = (height + width) * 2;
            if ((length + height) * 2 < min) min = (length + height) * 2;

            int local_total = length * width * height + min;
            total += local_total;
            // printf("\n%ix%ix%i - 2*%iL*%iW + 2*%iW*%iH + 2*%iH*%iL + %i = %i\n", length, width, height, length, width,
            //        width,
            //        height, height, length, min, local_total);

            length = 0;
            width = 0;
        } else {
            // printf("Before: %s",temp);
            temp[tempi] = input[i];
            tempi++;
            // printf("After: %s",temp);
        }
    }

    printf("We will need %i ft of ribbon.", total);
}

IDay day2 = {
    .part1 = day2_part1,
    .part2 = day2_part2
};
