//
// Created by dereck on 22-8-13.
//

#include <stdio.h>
const int w = sizeof(int) << 3;
const int all1 = ~0; //全为1的cover_code


void show_bytes(char* pointer,size_t len){
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%.2x",pointer[i]);
    }
    printf("\n");
}

//2.58
int is_little_endian(){
    char *byte1,*byte2;
    int a = 1;
    //注意这里一定要使用(char*)不然会出错
    //这种强制类型转换告诉编译器，程序应该把这个指针看成指向一个字节序列，而不是指向一个原始数据类型的对象
    byte1 = (char *)&a; // byte1 = 01
    byte2 = (char *)&a + sizeof(char); // byte2 = 00
    return *byte1 - *byte2;
}

//2.59
int low_x_high_y(int x,int y){
    x = x & 0xFF;
    y = (y >> 2) << 2;
    return x + y;
}

//2.60
unsigned replace_byte(unsigned x,int i,unsigned char b){
    int cover = all1 - (0xff << i * 8); // 得到一个除了replace位，其他位全为1的掩码
    x = x & cover;
    x = x + (b << (i*8));
    return x;
}

//2.61
int bit_test(int x){
    int lowest_byte = x & 0xff; //最低字节
    int highest_byte = (x >> (w-8)) & 0xff; // 最高字节
    return !(x^all1)||!(x|0)||!(lowest_byte^0xff)||!(highest_byte|0);
}

//2.62
int int_shifts_are_arithmetic(){
    int a = all1 >> 8;
    char *byte1 = (char*)&all1, *byte2 = (char*)&a;
    return !(*byte1 - *byte2);
}

//2.63 ???
//unsigned srl(unsigned x,int k){
//    unsigned xsra = (int) x >> k;
//    return ???;
//}

//2.64
/*Judge if all odd bits of x are equal to 1;
 * If yes,return 1, Otherwise, return 0.
 * (Assume w == 32 bits )*/
int any_odd_one(unsigned x){
    return !(x & 0xaaaaaaaa - 0xaaaaaaaa);
}

//2.65
/*
 * Return 1 when x contains an odd number of 1s ; 0 otherwise
 */
int odd_ones(unsigned x){

}
