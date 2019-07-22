#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_ARGS (3)
#define FALSE    (0)
#define TRUE     (1)

long get_file_len(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file); //fseek(file, 0, SEEK_SET)
    return size;
}

int str_appears_in_file_once(FILE* file, int size, char* str) {
    long total_bytes_read = 0;
    int appears = FALSE;
    char* line = NULL;
    size_t len = 0; //size_t is exactly like unsigned long
    ssize_t read;

    while ((total_bytes_read <= size) && (read = getline(&line, &len, file)) != -1) {
        if (total_bytes_read > size) {
            line[strlen(line)-(total_bytes_read-size)] = '\0';
        }
        total_bytes_read += read;
        if (strstr(line, str)) {
            if (appears) {
                return FALSE;
            }
            appears = TRUE;
        }
    }
    return appears;
}

int str_appears_in_both_halfs_once(char* str, char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "ERROR: Couldn't open file in str_appears_in_both_halfs_once\n");
        return 0;
    }
    long file_len = get_file_len(file);
    int str_appears_in_first_half = str_appears_in_file_once(file, file_len/2, str);
    fseek(file, file_len/2, SEEK_SET);
    int str_appears_in_second_half = str_appears_in_file_once(file, file_len/2, str);

    return str_appears_in_first_half && str_appears_in_second_half;
}

int main(int argc, char** argv) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "Usage: ./<exe> <string> <filename>\n");
        exit(1);
    }
    printf("%s %s in both half of file once!\n",
            argv[1], str_appears_in_both_halfs_once(argv[1], argv[2]) ? "appears" : "dosn't appear");
}

