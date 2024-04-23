#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

map_t hash_init(int size) {
    map_t hash_map = {0}; 
    hash_map.size = size;
    hash_map.load = 0;

    hash_map.entries = calloc(hash_map.size, sizeof(entries_t));
    if (hash_map.entries == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    return hash_map;
}

uint32_t hash(char *key) {
    uint32_t hash = BASIS_32;
    size_t length = strlen(key);

    for (size_t i = 0; i < length; i++) {
        hash ^= key[i];
        hash *= PRIME_32;
    }

    return hash;
}

map_t expand(map_t *map) {
    map_t new_map = hash_init(map->size * 2);
    for (int i = 0; i < map->size; i++) {
        if (map->entries[i].key != NULL) {
            h_insert(&new_map, map->entries[i].key, map->entries[i].value);
        }
    }
    free(map->entries);
    return new_map;
}

void h_insert(map_t *map, char *key, int value) {
    if ((double)map->load / (double)map->size >= 0.7) {
        map_t new_map = expand(map);
        *map = new_map;
    }

    uint32_t index = hash(key) % map->size;
    uint32_t start_index = index;

    while (map->entries[index].key != NULL && strcmp(map->entries[index].key, key) != 0) {
        index++;

        if (index == map->size) {
            index = 0;
        } else if (index == start_index) {
            printf("Index at capacity\n");
            break;
        }
    }

    if (map->entries[index].key == NULL) {
        map->entries[index].key = strdup(key);
        map->entries[index].value = value;
        map->load++;
    } else {
        map->entries[index].value = value;  // If the slot has matching key, update the value
    }
}

void h_show_all(map_t *map) {
    for (uint32_t i = 0; i < map->size; i++) {
        printf("Key: %s, Value: %d\n", map->entries[i].key, map->entries[i].value);
    }
}
