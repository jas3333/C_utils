#include <stdint.h>

#define PRIME_32 16777691 
#define BASIS_32 2166136261

typedef struct {
    int value;
    char *key;
} entries_t;

typedef struct {
    entries_t *entries;
    int size;               // Max capacity
    int load;               // Capacity
} map_t;


map_t hash_init(int size); 
void h_show_all(map_t *map);
uint32_t hash(char *key); 
void h_insert(map_t *map, char *key, int value); 
