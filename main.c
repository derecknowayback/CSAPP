#include <stdio.h>
#include "Chapter2.h"
int main(){
    int x = lower_one_mask(6);
    show_bytes((char*)&x, sizeof(int));
    return 0;
}

