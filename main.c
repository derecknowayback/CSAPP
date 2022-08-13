#include <stdio.h>
#include "Chapter2.h"
int main(){
    int x = 1 << 32;
    int y = 32;
    int z = 1 << y;
    printf("x:%d, z: %d\n", x, z);
    return 0;
}

