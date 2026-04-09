//
// Created by sb17057 on 4/9/2026.
//

#include "day4.h"
#include "Inputs/day4.h"
#include <string.h>
#include "libs/md5.h"

#include <stdio.h>
#include <stdlib.h>

void print_bytes(uint8_t bytes[16]) {
    for (int i = 0; i < 16; i++) {
        printf("%02X", bytes[i]);
    }
    printf("\n");
}

void day4_part1() {
    print_header(4, 1);
    const char *input = day4_input.input;

    int seed_num = 0;
    char seed[20];
    uint8_t final_result[16] = {0};

    sprintf(seed, "%s%d", input, seed_num);

    do {
        uint8_t result[16] = {0};
        md5_context ctx;
        md5_init(&ctx);
        md5_digest(&ctx, seed, strlen(seed));
        md5_output(&ctx, result);

        // if (seed_num % 1000 == 0 ) {
        // if (seed_num == 609043) {
        //     print_bytes(result);
        //     printf("seed_num: %i\nseed: %s\n------\n", seed_num, seed);
        // }

        if (
            result[0] == 0
            && result[1] == 0
            && result[2] <= 0x0f
            && result[2] > 0x00
        ) {
            memcpy(final_result, result, 16);
            break;
        }
        seed_num++;
        sprintf(seed, "%s%d", input, seed_num);
    } while (true);

    print_bytes(final_result);
    printf("seed_num: %i\nseed: %s\n", seed_num, seed);
}


void day4_part2() {
    print_header(4, 2);
    const char *input = day4_input.input;

    int seed_num = 0;
    char seed[20];
    uint8_t final_result[16] = {0};

    sprintf(seed, "%s%d", input, seed_num);

    do {
        uint8_t result[16] = {0};
        md5_context ctx;
        md5_init(&ctx);
        md5_digest(&ctx, seed, strlen(seed));
        md5_output(&ctx, result);

        // if (seed_num % 1000 == 0 ) {
        // if (seed_num == 609043) {
        //     print_bytes(result);
        //     printf("seed_num: %i\nseed: %s\n------\n", seed_num, seed);
        // }

        if (
            result[0] == 0
            && result[1] == 0
            && result[2] == 0
            && result[3] > 0x0f
        ) {
            memcpy(final_result, result, 16);
            break;
        }
        seed_num++;
        sprintf(seed, "%s%d", input, seed_num);
    } while (true);

    print_bytes(final_result);
    printf("seed_num: %i\nseed: %s\n", seed_num, seed);
}


IDay day4 = {
    .part1 = day4_part1,
    .part2 = day4_part2
};
