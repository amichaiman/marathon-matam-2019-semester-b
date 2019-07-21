#include <stdio.h>

#define BITS_IN_BYTE 8

unsigned int permute(unsigned int n, int *permutation);
int set_bit(int n, int i, int val);
int get_bit(int n, int i);

int main(){
    int permutations[] = {0,1,2,3,4,5,6,7,8,9,
                          10,11,12,13,14,15,16,17,18,19,
                          20,21,22,23,24,25,26,27,28,29,
                          30,31};

    printf("the new value of %u is %d\n", 1234, permute(1234,permutations));
    return 0;
}

unsigned int permute(unsigned int n, int *permutation){
    int output = 0;
    for (int i=0; i<8*sizeof(int); i++) {
        output = set_bit(output, i, get_bit(n, permutation[i]));
    }
    return output;
}


int set_bit(int n, int i, int val) {
    if (val) {
        return n |= 1<<i;
    }
    return n &= ~(1<<i);
}

int get_bit(int n, int i) {
    return (n>>i) & 0x1;
}
