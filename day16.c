//
// Created by sb17057 on 4/9/2026.
//

#include "day16.h"
#include "Inputs/day16.h"

#include <string.h>

#include "debug.h"

typedef struct {
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} MfcsamScan;

void day16_part1() {
    print_header(16, 1);
    const char *input = day16_input.input;
    const size_t len = strlen(input);


    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, &row_count, &max_row_size, rows);

    MfcsamScan my_scan = (MfcsamScan){
        3, 7, 2, 3, 0, 0, 5, 3, 2, 1
    };

    MfcsamScan aunts[row_count] = {};

    for (int i = 0; i < row_count; i++) {
        strtok(rows[i], " ");
        strtok(nullptr, " ");
        char *thing1 = strtok(nullptr, " ");
        size_t thing1len = strlen(thing1);
        thing1[thing1len - 1] = '\0';
        char *thing1valstr = strtok(nullptr, " ");
        size_t thing1vallen = strlen(thing1valstr);
        thing1valstr[thing1vallen - 1] = '\0';
        int thing1val = atoi(thing1valstr);
        char *thing2 = strtok(nullptr, " ");
        size_t thing2len = strlen(thing2);
        thing2[thing2len - 1] = '\0';
        char *thing2valstr = strtok(nullptr, " ");
        size_t thing2vallen = strlen(thing2valstr);
        thing2valstr[thing2vallen - 1] = '\0';
        int thing2val = atoi(thing2valstr);
        char *thing3 = strtok(nullptr, " ");
        size_t thing3len = strlen(thing3);
        thing3[thing3len - 1] = '\0';
        int thing3val = atoi(strtok(nullptr, " "));

        aunts[i] = (MfcsamScan){-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


        if (strcmp(thing1, "children") == 0) aunts[i].children = thing1val;
        else if (strcmp(thing1, "cats") == 0) aunts[i].cats = thing1val;
        else if (strcmp(thing1, "samoyeds") == 0) aunts[i].samoyeds = thing1val;
        else if (strcmp(thing1, "pomeranians") == 0) aunts[i].pomeranians = thing1val;
        else if (strcmp(thing1, "akitas") == 0) aunts[i].akitas = thing1val;
        else if (strcmp(thing1, "vizslas") == 0) aunts[i].vizslas = thing1val;
        else if (strcmp(thing1, "goldfish") == 0) aunts[i].goldfish = thing1val;
        else if (strcmp(thing1, "trees") == 0) aunts[i].trees = thing1val;
        else if (strcmp(thing1, "cars") == 0) aunts[i].cars = thing1val;
        else if (strcmp(thing1, "perfumes") == 0) aunts[i].perfumes = thing1val;
        if (strcmp(thing2, "children") == 0) aunts[i].children = thing2val;
        else if (strcmp(thing2, "cats") == 0) aunts[i].cats = thing2val;
        else if (strcmp(thing2, "samoyeds") == 0) aunts[i].samoyeds = thing2val;
        else if (strcmp(thing2, "pomeranians") == 0) aunts[i].pomeranians = thing2val;
        else if (strcmp(thing2, "akitas") == 0) aunts[i].akitas = thing2val;
        else if (strcmp(thing2, "vizslas") == 0) aunts[i].vizslas = thing2val;
        else if (strcmp(thing2, "goldfish") == 0) aunts[i].goldfish = thing2val;
        else if (strcmp(thing2, "trees") == 0) aunts[i].trees = thing2val;
        else if (strcmp(thing2, "cars") == 0) aunts[i].cars = thing2val;
        else if (strcmp(thing2, "perfumes") == 0) aunts[i].perfumes = thing2val;
        if (strcmp(thing3, "children") == 0) aunts[i].children = thing3val;
        else if (strcmp(thing3, "cats") == 0) aunts[i].cats = thing3val;
        else if (strcmp(thing3, "samoyeds") == 0) aunts[i].samoyeds = thing3val;
        else if (strcmp(thing3, "pomeranians") == 0) aunts[i].pomeranians = thing3val;
        else if (strcmp(thing3, "akitas") == 0) aunts[i].akitas = thing3val;
        else if (strcmp(thing3, "vizslas") == 0) aunts[i].vizslas = thing3val;
        else if (strcmp(thing3, "goldfish") == 0) aunts[i].goldfish = thing3val;
        else if (strcmp(thing3, "trees") == 0) aunts[i].trees = thing3val;
        else if (strcmp(thing3, "cars") == 0) aunts[i].cars = thing3val;
        else if (strcmp(thing3, "perfumes") == 0) aunts[i].perfumes = thing3val;

        // debug_ln("{");
        // debug_ln("  i: %i,", i);
        // debug_ln("  children: %i,", aunts[i].children);
        // debug_ln("  cats: %i,", aunts[i].cats);
        // debug_ln("  samoyeds: %i,", aunts[i].samoyeds);
        // debug_ln("  pomeranians: %i,", aunts[i].pomeranians);
        // debug_ln("  akitas: %i,", aunts[i].akitas);
        // debug_ln("  vizslas: %i,", aunts[i].vizslas);
        // debug_ln("  goldfish: %i,", aunts[i].goldfish);
        // debug_ln("  trees: %i,", aunts[i].trees);
        // debug_ln("  cars: %i,", aunts[i].cars);
        // debug_ln("  perfumes: %i,", aunts[i].perfumes);
        // debug_ln("}");

        if (
            (aunts[i].children == -1 || my_scan.children == aunts[i].children) &&
            (aunts[i].cats == -1 || my_scan.cats == aunts[i].cats) &&
            (aunts[i].samoyeds == -1 || my_scan.samoyeds == aunts[i].samoyeds) &&
            (aunts[i].pomeranians == -1 || my_scan.pomeranians == aunts[i].pomeranians) &&
            (aunts[i].akitas == -1 || my_scan.akitas == aunts[i].akitas) &&
            (aunts[i].vizslas == -1 || my_scan.vizslas == aunts[i].vizslas) &&
            (aunts[i].goldfish == -1 || my_scan.goldfish == aunts[i].goldfish) &&
            (aunts[i].trees == -1 || my_scan.trees == aunts[i].trees) &&
            (aunts[i].cars == -1 || my_scan.cars == aunts[i].cars) &&
            (aunts[i].perfumes == -1 || my_scan.perfumes == aunts[i].perfumes)
        ) {
            print_ln("{");
            print_ln("  i: %i,", i);
            print_ln("  children: %i,", aunts[i].children);
            print_ln("  cats: %i,", aunts[i].cats);
            print_ln("  samoyeds: %i,", aunts[i].samoyeds);
            print_ln("  pomeranians: %i,", aunts[i].pomeranians);
            print_ln("  akitas: %i,", aunts[i].akitas);
            print_ln("  vizslas: %i,", aunts[i].vizslas);
            print_ln("  goldfish: %i,", aunts[i].goldfish);
            print_ln("  trees: %i,", aunts[i].trees);
            print_ln("  cars: %i,", aunts[i].cars);
            print_ln("  perfumes: %i,", aunts[i].perfumes);
            print_ln("}");
        }
    }
}

void day16_part2() {
    print_header(16, 2);
    const char *input = day16_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, &row_count, &max_row_size, rows);

    MfcsamScan my_scan = (MfcsamScan){
        3, 7, 2, 3, 0, 0, 5, 3, 2, 1
    };

    MfcsamScan aunts[row_count] = {};

    for (int i = 0; i < row_count; i++) {
        strtok(rows[i], " ");
        strtok(nullptr, " ");
        char *thing1 = strtok(nullptr, " ");
        size_t thing1len = strlen(thing1);
        thing1[thing1len - 1] = '\0';
        char *thing1valstr = strtok(nullptr, " ");
        size_t thing1vallen = strlen(thing1valstr);
        thing1valstr[thing1vallen - 1] = '\0';
        int thing1val = atoi(thing1valstr);
        char *thing2 = strtok(nullptr, " ");
        size_t thing2len = strlen(thing2);
        thing2[thing2len - 1] = '\0';
        char *thing2valstr = strtok(nullptr, " ");
        size_t thing2vallen = strlen(thing2valstr);
        thing2valstr[thing2vallen - 1] = '\0';
        int thing2val = atoi(thing2valstr);
        char *thing3 = strtok(nullptr, " ");
        size_t thing3len = strlen(thing3);
        thing3[thing3len - 1] = '\0';
        int thing3val = atoi(strtok(nullptr, " "));

        aunts[i] = (MfcsamScan){-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


        if (strcmp(thing1, "children") == 0) aunts[i].children = thing1val;
        else if (strcmp(thing1, "cats") == 0) aunts[i].cats = thing1val;
        else if (strcmp(thing1, "samoyeds") == 0) aunts[i].samoyeds = thing1val;
        else if (strcmp(thing1, "pomeranians") == 0) aunts[i].pomeranians = thing1val;
        else if (strcmp(thing1, "akitas") == 0) aunts[i].akitas = thing1val;
        else if (strcmp(thing1, "vizslas") == 0) aunts[i].vizslas = thing1val;
        else if (strcmp(thing1, "goldfish") == 0) aunts[i].goldfish = thing1val;
        else if (strcmp(thing1, "trees") == 0) aunts[i].trees = thing1val;
        else if (strcmp(thing1, "cars") == 0) aunts[i].cars = thing1val;
        else if (strcmp(thing1, "perfumes") == 0) aunts[i].perfumes = thing1val;
        if (strcmp(thing2, "children") == 0) aunts[i].children = thing2val;
        else if (strcmp(thing2, "cats") == 0) aunts[i].cats = thing2val;
        else if (strcmp(thing2, "samoyeds") == 0) aunts[i].samoyeds = thing2val;
        else if (strcmp(thing2, "pomeranians") == 0) aunts[i].pomeranians = thing2val;
        else if (strcmp(thing2, "akitas") == 0) aunts[i].akitas = thing2val;
        else if (strcmp(thing2, "vizslas") == 0) aunts[i].vizslas = thing2val;
        else if (strcmp(thing2, "goldfish") == 0) aunts[i].goldfish = thing2val;
        else if (strcmp(thing2, "trees") == 0) aunts[i].trees = thing2val;
        else if (strcmp(thing2, "cars") == 0) aunts[i].cars = thing2val;
        else if (strcmp(thing2, "perfumes") == 0) aunts[i].perfumes = thing2val;
        if (strcmp(thing3, "children") == 0) aunts[i].children = thing3val;
        else if (strcmp(thing3, "cats") == 0) aunts[i].cats = thing3val;
        else if (strcmp(thing3, "samoyeds") == 0) aunts[i].samoyeds = thing3val;
        else if (strcmp(thing3, "pomeranians") == 0) aunts[i].pomeranians = thing3val;
        else if (strcmp(thing3, "akitas") == 0) aunts[i].akitas = thing3val;
        else if (strcmp(thing3, "vizslas") == 0) aunts[i].vizslas = thing3val;
        else if (strcmp(thing3, "goldfish") == 0) aunts[i].goldfish = thing3val;
        else if (strcmp(thing3, "trees") == 0) aunts[i].trees = thing3val;
        else if (strcmp(thing3, "cars") == 0) aunts[i].cars = thing3val;
        else if (strcmp(thing3, "perfumes") == 0) aunts[i].perfumes = thing3val;

        // debug_ln("{");
        // debug_ln("  i: %i,", i);
        // debug_ln("  children: %i,", aunts[i].children);
        // debug_ln("  cats: %i,", aunts[i].cats);
        // debug_ln("  samoyeds: %i,", aunts[i].samoyeds);
        // debug_ln("  pomeranians: %i,", aunts[i].pomeranians);
        // debug_ln("  akitas: %i,", aunts[i].akitas);
        // debug_ln("  vizslas: %i,", aunts[i].vizslas);
        // debug_ln("  goldfish: %i,", aunts[i].goldfish);
        // debug_ln("  trees: %i,", aunts[i].trees);
        // debug_ln("  cars: %i,", aunts[i].cars);
        // debug_ln("  perfumes: %i,", aunts[i].perfumes);
        // debug_ln("}");

        if (
            (aunts[i].children == -1 || my_scan.children == aunts[i].children) &&
            (aunts[i].cats == -1 || my_scan.cats < aunts[i].cats) &&
            (aunts[i].samoyeds == -1 || my_scan.samoyeds == aunts[i].samoyeds) &&
            (aunts[i].pomeranians == -1 || my_scan.pomeranians > aunts[i].pomeranians) &&
            (aunts[i].akitas == -1 || my_scan.akitas == aunts[i].akitas) &&
            (aunts[i].vizslas == -1 || my_scan.vizslas == aunts[i].vizslas) &&
            (aunts[i].goldfish == -1 || my_scan.goldfish > aunts[i].goldfish) &&
            (aunts[i].trees == -1 || my_scan.trees < aunts[i].trees) &&
            (aunts[i].cars == -1 || my_scan.cars == aunts[i].cars) &&
            (aunts[i].perfumes == -1 || my_scan.perfumes == aunts[i].perfumes)
        ) {
            print_ln("{");
            print_ln("  i: %i,", i);
            print_ln("  children: %i,", aunts[i].children);
            print_ln("  cats: %i,", aunts[i].cats);
            print_ln("  samoyeds: %i,", aunts[i].samoyeds);
            print_ln("  pomeranians: %i,", aunts[i].pomeranians);
            print_ln("  akitas: %i,", aunts[i].akitas);
            print_ln("  vizslas: %i,", aunts[i].vizslas);
            print_ln("  goldfish: %i,", aunts[i].goldfish);
            print_ln("  trees: %i,", aunts[i].trees);
            print_ln("  cars: %i,", aunts[i].cars);
            print_ln("  perfumes: %i,", aunts[i].perfumes);
            print_ln("}");
        }
    }
}

IDay day16 = {
    .part1 = day16_part1,
    .part2 = day16_part2
};
