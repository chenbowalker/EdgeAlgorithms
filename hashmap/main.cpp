
#include <iostream>
#include "hashmap.h"

int main() {
    hashmap* hm = create_hashmap(10);
    char key1[] = "aaa";
    char val1[] = "111";
    char key2[] = "bbb";
    char val2[] = "222";
    char key3[] = "ccc";
    char val3[] = "333";
    hashmap_insert(hm, key1, 3, val1, 4);
    hashmap_insert(hm, key2, 3, val2, 4);

    std::cout << hashmap_count(hm) << std::endl;
    printf("%s\n",(char*)hashmap_get(hm, key1, 3));
    printf("%s\n",(char*)hashmap_get(hm, key2, 3));
    hashmap_insert(hm, key3, 3, val3, 4);
    std::cout << hashmap_count(hm) << std::endl;
    printf("%s\n",(char*)hashmap_get(hm, key3, 3));
    hashmap_remove(hm, key2, 3);
    std::cout << hashmap_count(hm) << std::endl;
    free_hashmap(hm);
    return 0;
}