#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(){
    int32_t x = 6;
    uint64_t y = 120;
    printf("x = %" PRId32 ",y = %" PRIu64 "\n",x,y);
    return 0;
}
