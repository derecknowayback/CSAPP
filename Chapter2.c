//
// Created by dereck on 22-8-13.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

const int w = sizeof(int) << 3;
const int all1 = ~0; //全为1的cover_code


void show_bytes(char* pointer,size_t len){
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%.2x",pointer[i]);
    }
    printf("\n");
}

// 2.58
//int is_little_endian(){
//    char *byte1,*byte2;
//    int a = 1;
//    //注意这里一定要使用(char*)不然会出错
//    //这种强制类型转换告诉编译器，程序应该把这个指针看成指向一个字节序列，而不是指向一个原始数据类型的对象
//    byte1 = (char *)&a; // byte1 = 01
//    byte2 = (char *)&a + sizeof(char); // byte2 = 00
//    return *byte1 - *byte2;
//}
int is_little_endian(){
    char* byte ;
    unsigned magic = 0xff;
    byte = (char *)&magic;
    return !(byte[0] - 0xff); //小端返回1，大端返回0
}


// 2.59
int low_x_high_y(int x,int y){
    x = x & 0xFF;
    y = (y >> 8) << 8;
    return x + y; //or : return (x & 0xFF) | (y & ~0xFF)
}



// 2.60
unsigned replace_byte(unsigned x,int i,unsigned char b){
//    int mask = all1 - (0xff << i * 8); // 得到一个除了replace位，其他位全为1的掩码(打掉要替换的段）
//    x = x & mask;
//    x = x + (b << (i*8));
//    return x;
    //1 byte has 8 bits, << 3 means * 8
      unsigned mask = ((unsigned) 0xFF) << (i << 3);
      unsigned pos_byte = ((unsigned) b) << (i << 3);
      return (x & ~mask) | pos_byte;
}

// 2.61
int bit_test(int x){
    int lowest_byte = x & 0xff; //最低字节
    int highest_byte = (x >> (w-8)) & 0xff; // 最高字节
    return !(x^all1)||!(x|0)||!(lowest_byte^0xff)||!(highest_byte|0);
}

// 2.62
int int_shifts_are_arithmetic(){
//    int a = all1 >> 8;
//    char *byte1 = (char*)&all1, *byte2 = (char*)&a;
//    return !(*byte1 - *byte2);
    return !(all1 ^ (all1 >> 1));
}

// 2.63
unsigned srl(unsigned x,int k){
    unsigned xsra = (int ) x >> k;
    unsigned mask = ~(all1 << (w - k));
    return xsra & mask;
}
int sra(int x, int k){
    int xsrl = (unsigned ) x >> k;
    unsigned sign = x & (1 << (w-1));

}

// 2.64
/*Judge if any odd bits of x are equal to 1
 * If yes,return 1, Otherwise, return 0. -> 只要奇数位有1，就返回1，否则返回0
 * (Assume w == 32 bits )*/
int any_odd_one(unsigned x){
    return x & 0xaaaaaaaa;
}

//2.65
/*
 * Return 1 when x contains an odd number of 1s ; 0 otherwise
 */
int odd_ones(unsigned x){
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x1;
    return x;
}

//2.66
/*
 * 只保留最左边的1，其余为0；如果x == 0,return 0;
 * assume w = 32;
 */
int leftmost_one(unsigned x) {
    /*
     * first, generate a mask that all bits after leftmost one are one
     * e.g. 0xFF00 -> 0xFFFF, and 0x6000 -> 0x7FFF
     * If x = 0, get 0
     */
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    /*
     * then, do (mask >> 1) + (mask && 1), in which mask && 1 deals with case x = 0, reserve leftmost bit one
     * that's we want
     */
    return (x >> 1) + (x && 1);
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
int int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit() {
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
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
//    int w = sizeof(unsigned) << 3;
//    /* pay attention when n == 0 */
//    return x << n | x >> (w - n );
}


//2.70
// fits_bits
int fits_bits(int x, int n){
    //自己写的有问题。碰到 比如w = 8, n = 3，0b00000110 is not ok;
    //主要问题就是，不只是看这个表达式能不能塞到n位中，还要看首位（符号位）满不满足
    //    int cover = all1 << n; // 1111100000000
    //    return !(x&cover);
  /*
  * 1 <= n <= w
  * assume w = 8, n = 3
  * if x > 0
  *   0b00000010 is ok, 0b00001010 is not, and 0b00000110 is not yet (thanks itardc@163.com)
  * if x < 0
  *   0b11111100 is ok, 0b10111100 is not, and 0b11111000 is not yet
  * the point is
  *   x << (w-n) >> (w-n) must be equal to x itself.
   *   本质是 w-n 对于这个数实在是没有什么用，对于正数要求这w-n个数是0，对于负数是1
  */
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}


//2.71
typedef unsigned packed_t;
//This function can’t extract negetive number from packet_t word.
//原先的func没有考虑到负数的情况，符号扩展的时候会将负数变为正数
//ban 掉了 & 怎么做呢
int xbyte(packed_t word,int bytenum){
    int max_bytenum = 3;
    return (int) word << ((max_bytenum - bytenum) << 3) >> (max_bytenum << 3);
}


//2.72
void copy_int(int val,void* buf,int maxbytes){
    //Wrong Code:if(maxbytes - sizeof(val) >= 0)
    // ->  For operation sizeof return 'size_t' equals to unsigned
    //if(maxbytes >= sizeof(val)) 这样还是不行，万一有人传了一个负数的maxbytes进来就完蛋了
    if (maxbytes >= (int ) sizeof(val)) // 必须添加一个强制类型转换
        memcpy(buf,(void*)&val, sizeof(val));
}


//2.73
//饱和（溢出）的时候返回 Tmax or Tmin
int saturating_add(int x, int y){
    //不使用if怎么办？太优雅了 这写法
    int sum = x + y;
    int sig_mask = INT_MIN;
    /*
     * if x > 0, y > 0 but sum < 0, it's a positive overflow
     * if x < 0, y < 0 but sum >= 0, it's a negetive overflow
     */
    int pos_over = !(x & sig_mask) && !(y & sig_mask) && (sum & sig_mask);
    int neg_over = (x & sig_mask) && (y & sig_mask) && !(sum & sig_mask);

    (pos_over && (sum = INT_MAX) || neg_over && (sum = INT_MIN));

    return sum;
    //links : https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.73/
}

//2.74
//if x-y not overflows, return 1
//只会有 1.负-非负  2.非负-负
int tsub_ok(int x, int y){
    int sub = x - y;
    int mask = all1;
    int res = 1;
     (x & mask) && !(y & mask) && !(sub & mask)&&(res = 0); // nmp
     !(x & mask) && (y & mask) && (sub & mask)&&(res = 0); // pmn
    //还有一种情况？？？我觉得Tmin已经解决问题了？？？
    //是这样的，博客的实现有问题，单凭y==Tmin并不能判断溢出，只有x>=0&&y==Tmin才可以说溢出；
    return res;
}

//2.75
//怎么不用循环实现 获得x*y的高w位
int signed_high_prod(int x, int y){

}
unsigned unsigned_high_prod(unsigned x,unsigned y){

}


//2.76
void *my_calloc(size_t nmeb, size_t size){
    //Q:size_t is unsigned long on Linux, how should I solve the overflow problem?
    void* res_ptr = malloc(size * nmeb);
    memset(res_ptr,0,nmeb * size);
}

//2.78
int divide_power2(int x, int y){
    // 不用 ? 和 if 怎么做
    //return (x > 0 ? x : (x + (y << 1) - 1)) / ( 2 << y );
}

//2.79
//return x * 3 / 4
int mul3div4(int x){
    x = divide_power2(x,2);
    return x * 3;
}

//2.80
//return 3/4x
int threefourths(int x){
    //difference ???
}

//2.81
//bit patterns: 1(w-k个1)--0(k个0)
int bit_mode_k(int k){
    return all1 << k;
}
//bit patterns： 0（w-k-j个0）--1（k个1）--0（j个0）
int bit_mode_k_j(int k, int j){
    //if(j == 0) return bit_mode_k_j(k);
    int suffix0 = all1 << j;
    int prefix0 = (1 << (k + j + 1)) - 1; // k + j == w 可以吗？？？
    return suffix0 & prefix0;
}