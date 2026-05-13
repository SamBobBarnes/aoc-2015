//
// Created by sb17057 on 5/13/2026.
//

#ifndef AOC_2015_DICTIONARY_H
#define AOC_2015_DICTIONARY_H

typedef struct DictionaryEntry DictionaryEntry;


typedef struct {
    int size;
    int max_size;
    DictionaryEntry *entries;
} Dictionary;


Dictionary create_dictionary(const int max_size);

void add_to_dict(Dictionary *dict, const int key, void *value);

void *get_from_dict(const Dictionary *dict, const int key);

#endif //AOC_2015_DICTIONARY_H
