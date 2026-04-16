//
// Created by sb17057 on 4/9/2026.
//

#include "day12.h"
#include "Inputs/day12.h"
#include "libs/json.h"
#include <string.h>
#include "debug.h"

void day12_part1() {
    print_header(12, 1);
    bool test = false;
    char *input = nullptr;
    if (test)
        input = day12_input.test_input;
    else {
        input = read_file("../Inputs/day12.txt"); // disregard the first 3 chars
        input = input + 3;
    }
    const size_t len = strlen(input);

    bool reading_num = false;
    char num[10] = {'\0'};
    int num_i = 0;
    int total = 0;
    for (int i = 0; i < len; i++) {
        if ((input[i] >= 48 && input[i] <= 57) || input[i] == '-') reading_num = true;
        else if (reading_num) {
            int num_val = atoi(num);
            total += num_val;
            reading_num = false;
            for (int j = 0; j < 10; j++) {
                num[j] = '\0';
            }
            num_i = 0;
        }
        if (reading_num) {
            num[num_i++] = input[i];
        }
    }

    printf("The sum of all numbers is %i", total);

    if (!test) {
        input = input - 3;
        free(input);
    }
}

int reds = 0;
int red_finds = 0;

int recurse(const struct json_value_s *json, enum json_type_e enclosing_type) {
    switch (json->type) {
        case json_type_array:
            const struct json_array_s *arr = (struct json_array_s *) json->payload;
            const struct json_array_element_s *arr_elem = arr->start;
            int arr_total = 0;
            while (arr_elem != NULL) {
                arr_total += recurse(arr_elem->value, json_type_array);
                arr_elem = arr_elem->next;
            }
            return arr_total; // arrays are totaled up
        case json_type_object:
            const struct json_object_s *obj = (struct json_object_s *) json->payload;
            const struct json_object_element_s *elem = obj->start;
            int obj_total = 0;
            while (elem != NULL) {
                const int value = recurse(elem->value, json_type_object);
                if (value < 0)
                    return 0;
                // if value is less than one, an obj in this obj contains the string "red" and this object is not valid;
                obj_total += value; // else we total up the obj
                elem = elem->next;
            }
            return obj_total;
        case json_type_true:
        case json_type_false:
        case json_type_null:
            return 0; // booleans dont matter
        case json_type_string:
            if (enclosing_type == json_type_array) {
                return 0; // strings directly in arrays dont matter
            }
            const struct json_string_s *str = (struct json_string_s *) json->payload;

            if (strcmp(str->string, "red") == 0)
                return -1; // return -1 if object value is red
            return 0;
        case json_type_number:
            return atoi(((struct json_number_s *) json->payload)->number); // return numbers to total up
        default:
            exit(1);
    }
}

void day12_part2() {
    print_header(12, 2);
    bool test = true;
    char *input = nullptr;
    if (test)
        input = day12_input.test_input;
    else {
        input = read_file("../Inputs/day12.txt"); // disregard the first 3 chars
        input = input + 3;
    }
    const size_t len = strlen(input);

    struct json_value_s *json = json_parse(input, len);

    const int total = recurse(json, json_type_object);

    // 82040 < x < 121920
    print_ln("The sum of all numbers is %i", total);

    free(json);
    if (!test) {
        input = input - 3;
        free(input);
    }
}

IDay day12 = {
    .part1 = day12_part1,
    .part2 = day12_part2
};
