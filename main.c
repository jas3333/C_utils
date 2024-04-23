#include <stdio.h>
#include "utils.h"

int main() {

    map_t map = hash_init(10);
    char string[2];  
    char a = 'a';
    for (int i = 0; i < 20; i++) {
        string[0] = a + i;
        h_insert(&map, string, i);
    }

    h_show_all(&map);

    return 0;
}
