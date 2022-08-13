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

//2.66
/*
 * 只保留最左边的1，其余为0；如果x == 0,return 0;
 * assume w = 32;
 */
int leftmost_one(unsigned x){
    //先变成 000011..111的形式
    x = x & all1;
    unsigned low = x >> 1;
    return x - low;
}

//2.67
/*
 * int bad_int_size_is_32(){
 *  int set_msb = 1 << 31;
 *  int beyond_msb = 1 << 32;
 *  return set_msb && !beyond_msb;
 * }
 * warning : left shift count >= width 32
 * 没有遵守C语言右移不能大于width的标准,移动32位实际上只移动1位
 */
//running on 32
int my_int_size_is_32(){
    int beyond_msb = 1 << 32;
    return !(beyond_msb-1); // beyond_msb == 1
}

//running on 16
int my_int_size_is_16(){
    int beyond_msb = 1 << 32;
    return !(beyond_msb-1); // beyond_msb == 1
}

//2.68
//用n个1组成最小的数
int lower_one_mask(int n){
    int shift = w - n; // what if w == n ??? `10000` is the smallest
    return (unsigned)all1 >> shift;
}

//2.69
//bit位左旋: 比如w=4, x=1011, 左旋1位--> newX = 0111
unsigned rotate_left(unsigned  x, int n){
    //取模
    n = n & (w - 1);
    int high = x >> (w - n);
    x = x << n;
    return x + high;
}


//2.70
// fits_bits
int fits_bits(int x, int n){
    int cover = all1 << n; // 1111100000000
    return !(x&cover);
}

//2.71
typedef unsigned packed_t;
//原先的func没有考虑到machine 是 算术右移的
int xbyte(packed_t word,int bytenum){
    int max = 0xffffffff;
    int offset = bytenum << 3;
}









