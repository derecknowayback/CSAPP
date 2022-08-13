#include <stdio.h>
#include "Chapter2.h"
int main(){
    int a = 0xf0000000;
    a = a<<4;
    printf("%d",a);
    return 0;
}

