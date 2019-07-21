#include <stdio.h>

#define POSITIVE (0xb)
#define NEGATIVE (0xc)

int encodeBCD(int number, char *buffer);
int decodeBCD(int *number, char* buffer);

int main() {
    int n = -23678; //1453;
    char buffer[100];
    int decoded_n;

    printf("Number: %d\n", n);
    int buffer_effective_size = encodeBCD(n, buffer);
    int i;

    for (i=0; i<buffer_effective_size; i++) {
        printf("0x%x\t", 0xff&buffer[i]);
    }
    puts("");

    decodeBCD(&decoded_n, buffer);
    printf("decoded n: %d\n", decoded_n);
    return 0;
}

int get_num_digits(int n) {
    if (n == 0) {
        return 0;
    }
    return 1 + get_num_digits(n/10);
}

int encodeBCD(int number, char *buffer){
    int i;
    int sign = number >= 0 ? POSITIVE : NEGATIVE;
    int num_digits = get_num_digits(number);

    if (sign == NEGATIVE) {
        number = -number;
    }

    for (i=0; number>0; i++) {
        buffer[i] = number%10; //left half of byte
        buffer[i] <<= 4;
        number /= 10;
        buffer[i] |= number%10; //second half of byte
        number /= 10;
    }

    if (num_digits%2) {
        buffer[i-1] |= sign;
    } else {
        buffer[i] |= sign;
    }

    return num_digits%2 ? i : i+1;
}

int has_sign(unsigned char c) {
    return (c>>4 ) == POSITIVE ||
           (c>>4 ) == NEGATIVE ||
           (c&0xf) == POSITIVE ||
           (c&0xf) == NEGATIVE;
}

int get_index_of_sign(char* buffer) {
    int i;
    for (i=0; !has_sign(buffer[i]); i++);
    return i;
}

// 35 41 b
int decodeBCD(int *number, char* buffer) {
    int i, last_byte = get_index_of_sign(buffer);
    int sign;
    /* take care of last byte which contains the sign */
    if (has_sign(buffer[last_byte]>>4)) {
        sign = buffer[last_byte]>>4;
        *number = 0;
    } else {
        sign = buffer[last_byte]&0xf;
        *number = buffer[last_byte]>>4;
    }

    /* take care of the rest */
    for (i = last_byte-1; i >= 0; i--) {
        *number *= 10; //make room for next digit
        *number += (unsigned char)buffer[i]&0xf; //add right part of byte

        *number *= 10; //make room for next digit
        *number += (unsigned char)buffer[i]>>4; //add left part of byte
    }

    if (sign == NEGATIVE) {
        *number = -(*number);
    }
    return last_byte;
}

int cfwrite(FILE* file, int number) {
    int num_digits = get_num_digits(number);
    char buffer[num_digits];
    int i, effective_buffer_len = encodeBCD(number, buffer); /* 1 */

    for (i=0; i<effective_buffer_len; i++) {
        fputc(buffer[i], file);
    }
}

void set_encoding(int(*encode)(int, char*), int(*decode)(int*, char* buffer)) {
}
