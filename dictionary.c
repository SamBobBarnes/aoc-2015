//
// Created by sb17057 on 5/13/2026.
//

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>

struct DictionaryEntry {
    int key;
    void *value;
};

Dictionary create_dictionary(const int max_size) {
    Dictionary dictionary;
    dictionary.entries = malloc(sizeof(DictionaryEntry) * max_size);
    dictionary.max_size = max_size;
    dictionary.size = 0;

    return dictionary;
}

void *get_from_dict(const Dictionary *dict, const int key) {
    if (dict->size == 0) return NULL;

    for (int i = 0; i < dict->size; i++) {
        if (dict->entries[i].key == key)
            return dict->entries[i].value;
    }

    return NULL;
}

int get_index(const Dictionary *dict, const int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->entries[i].key == key)
            return i;
    }
    return -1;
}

void add_to_dict(Dictionary *dict, const int key, void *value) {
    if (dict->size == dict->max_size) {
        printf("Dictionary is full\n");
        return;
    }

    const int index = get_index(dict, key);
    if (index == -1) {
        dict->entries[dict->size].key = key;
        dict->entries[dict->size].value = value;
        dict->size++;
    } else {
        dict->entries[index].value = value;
    }
}

int *get_keys(const Dictionary *dict) {
    int *keys = malloc(sizeof(int) * dict->size);
    for (int i = 0; i < dict->size; i++) {
        keys[i] = dict->entries[i].key;
    }
    return keys;
}
