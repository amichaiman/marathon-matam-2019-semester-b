#include <stdio.h>

#define NUM_BITS_IN_BYTE (8)
#define INVALID_INDEX    (-1)

// shift left   ------> *2
// shift right  ------> /2
//
//
//   7654 3210
//   |||| ||||
// c 1101 1101
//

unsigned char get_bit(unsigned char c, int index) {
    if (index > NUM_BITS_IN_BYTE-1 || index < 0) {
        return INVALID_INDEX;
    }
    return (c>>index) & 0x1;
}

unsigned char set_bit(unsigned char c, int index, int val) {
    if (index > NUM_BITS_IN_BYTE-1 || index < 0) {
        return INVALID_INDEX;
    }
    unsigned char mask = 0x1<<index;

    return val ? c | mask : c & (~mask);
}

int main() {
    unsigned char c = 0x11;
    printf("%d\n%x\n", get_bit(c, 4), set_bit(c, 1, 1));
    return 0;
}

