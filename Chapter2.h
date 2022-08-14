//
// Created by dereck on 22-8-13.
//

#ifndef CSAPP_CHAPTER2_H
#define CSAPP_CHAPTER2_H
int is_little_endian();
int low_x_high_y(int x,int y);
unsigned replace_byte(unsigned x,int i,unsigned char b);
int bit_test(int x);
int int_shifts_are_arithmetic();
unsigned srl(unsigned x,int k);
int any_odd_one(unsigned x);
int odd_ones(unsigned x);
int leftmost_one(unsigned x);
int lower_one_mask(int n);
int int_size_is_32();
int int_size_is_32_for_16bit();
int fits_bits(int x, int n);
typedef unsigned packed_t;
int xbyte(packed_t word,int bytenum);
unsigned rotate_left(unsigned  x, int n);
void show_bytes(char* pointer,size_t len);
void copy_int(int val,void* buf,int maxbytes);
int saturating_add(int x, int y);
int tsub_ok(int x, int y);
#endif //CSAPP_CHAPTER2_H
