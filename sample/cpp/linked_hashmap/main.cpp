#include <stdio.h>
#include <stdlib.h>
#include "linked_hashmap.h"
using namespace oak;

int main(int argc, char** argv)
{
    LinkedListMap<int, int> map;
    map.add(1, 101);
    map.add(2, 102);
    map.add(3, 103);
    printf("map.empty() = %s\n", map.empty() ? "true" : "false");
    printf("map.size() = %d\n", map.size());

    for (LinkedListMap<int, int>::Iterator it = map.begin(); it != map.end(); it++) {
        printf("k = %d, val = %d\n", (*it).key, it->data);
        
    }

    return 0;
}
