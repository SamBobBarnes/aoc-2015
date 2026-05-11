//
// Created by sb17057 on 4/9/2026.
//

#include "day19.h"
#include "Inputs/day19.h"

#include <string.h>

#include "debug.h"

int index_of(const char *string, const char *search_string, const int offset) {
    const size_t len = strlen(string);
    const size_t search_len = strlen(search_string);
    for (int i = offset; i < len - search_len + 1; i++) {
        bool match = true;
        for (int j = 0; j < search_len; j++)
            if (string[i + j] != search_string[j]) {
                match = false;
                break;
            }
        if (match) {
            return i;
        }
    }

    return -1;
}

void day19_part1() {
    print_header(19, 1);
    const char *input = day19_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, row_count, max_row_size, rows);

    char *sut = rows[row_count - 1];
    size_t sut_len = strlen(sut);

    int possibles_max_size = row_count * 100;
    char **possibles = malloc(sizeof(char *) * possibles_max_size);
    for (int i = 0; i < possibles_max_size; i++) {
        possibles[i] = (char *) malloc(sizeof(char) * max_row_size * 2);
        possibles[i][0] = '\0';
    }
    int possible_count = 0;

    for (int i = 0; i < row_count - 2; i++) {
        char temp[max_row_size * 2];
        temp[0] = '\0';
        int index;

        int space_index = index_of(rows[i], " ", 0);
        char search_string[3] = "\0\0\0";
        strncpy(search_string, rows[i], space_index);
        size_t search_len = strlen(search_string);
        char *replacement_string = &rows[i][space_index + 4];
        size_t replacement_len = strlen(replacement_string);

        debug_ln("%s:", search_string);

        int offset = 0;
        do {
            index = index_of(sut, search_string, offset);

            if (index == -1) break; // no more left

            temp[0] = '\0';
            strncpy(temp, sut, index);
            strcpy(&temp[index], replacement_string);
            strcpy(&temp[index + replacement_len], &sut[index + search_len]);

            if (debugging) {
                printf("%i,", index);
            }

            bool duplicate = false;
            for (int j = 0; j < possible_count; j++) {
                if (strcmp(possibles[j], temp) == 0) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                strcpy(possibles[possible_count++], temp);
            }

            offset = (int) (index + search_len);
        } while (index >= 0);
    }

    // 443 < x
    print_ln("There are %i unique replacements.", possible_count);
    free(possibles);
}

enum TokenType {
    TILT,
    TOKEN, // X
    RN, // (
    AR, // )
    Y // ,
};

typedef struct {
    enum TokenType type;
    char key[3];
} Molecule;


typedef struct {
    char key[3];
    char value[10];
    Molecule molecule[8];
    int mol_count;
} Replacement;

typedef struct {
    enum TokenType type;
    int count;
} TokenCount;


void print_molecule(const TokenCount *molecule, const size_t len) {
    for (int i = 0; i < len; i++) {
        if (molecule[i].type == TOKEN)
            printf("%iT", molecule[i].count);
        else if (molecule[i].type == RN)
            printf("(");
        else if (molecule[i].type == AR)
            printf(")");
        else if (molecule[i].type == Y)
            printf(",");
    }
}

void create_molecules(const char *molecule, const size_t mol_len, Molecule molecules[], int *mol_count) {
    for (int i = 0; i < mol_len; i++) {
        molecules[*mol_count] = (Molecule){TILT, "\0\0\0"};
        if (i < mol_len - 1 && molecule[i + 1] >= 97) {
            char key[3] = "\0\0\0";
            sprintf(key, "%c%c", (char) molecule[i], (char) molecule[i + 1]);
            if (strcmp(key, "Rn") == 0)
                molecules[*mol_count].type = RN;
            else if (strcmp(key, "Ar") == 0)
                molecules[*mol_count].type = AR;
            else
                molecules[*mol_count].type = TOKEN;
            strcpy(molecules[*mol_count].key, key);
            i++;
        } else {
            if (molecule[i] == 'Y')
                molecules[*mol_count].type = Y;
            else
                molecules[*mol_count].type = TOKEN;
            molecules[*mol_count].key[0] = molecule[i];
        }

        (*mol_count)++;
    }
}

void day19_part2() {
    print_header(19, 2);
    const char *input = day19_input.input;
    const size_t len = strlen(input);

    int max_row_size = 0;
    int row_count = GetRowCount(input, len, &max_row_size);
    char rows[row_count][max_row_size];
    SplitIntoRows(input, len, row_count, max_row_size, rows);

    const char *molecule = rows[row_count - 1];
    const size_t mol_len = strlen(molecule);

    Molecule molecules[mol_len];
    int mol_count = 0;

    create_molecules(molecule, mol_len, molecules, &mol_count);

    int bracket_count = 0;
    int comma_count = 0;
    for (int i = 0; i < mol_count; i++) {
        if (molecules[i].type == RN || molecules[i].type == AR)
            bracket_count++;
        if (molecules[i].type == Y)
            comma_count++;
    }

    // x < 213
    printf("It will take %i steps", mol_count - bracket_count - comma_count * 2 - 1);
}


IDay day19 = {
    .part1 = day19_part1,
    .part2 = day19_part2
};
