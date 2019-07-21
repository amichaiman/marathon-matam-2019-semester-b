#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ARGS (3)

long get_file_len(FILE *file);
int sentence_appears_in_both_halfs_of_file(char* sentence, char* filename);

int main(int argc, char **argv) {
    if (argc != NUM_ARGS) {
        fprintf(stderr, "Usage: <string> <filename>\n");
        exit(1);
    }
    printf("sentence%s appears in both halfs\n",
            sentence_appears_in_both_halfs_of_file(argv[1], argv[2]) ? "" : " doesn't");


    return 0;
}

/* input: file, file's length and a sentence
 * output: location of sentence in file if it appears in it once only. -1 otherwise
 * */
long sentence_appears_once_in_file(FILE* file, int file_len, char* sentence) {
    int location = -1;
    char* line = NULL; //current line being read
    size_t len = 0;
    ssize_t read; //number of bytes read by getline
    ssize_t total_read = 0; //total number of bytes read

    while ((read = getline(&line, &len, file)) != -1) {
        total_read += read;
        if (total_read > file_len+1) {
            break;
        }
        if (strstr(line, sentence)) {
            if (location) { //if sentence appears more than once
                return -1;
            }
            location = ftell(file); //rememeber location
        }
    }
    return location;
}

int sentence_appears_in_both_halfs_of_file(char* sentence, char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: couldn't open %s\n", filename);
        exit(2);
    }

    long file_len = get_file_len(file);
    long location_in_first_half = sentence_appears_once_in_file(file, file_len/2, sentence); //search first half
    fseek(file, file_len/2, SEEK_SET);
    long location_in_second_half = sentence_appears_once_in_file(file, file_len/2, sentence); //search sencond half

    if (location_in_first_half != -1 && location_in_second_half != -1) {
        printf("location in first half: %ld\n", location_in_first_half);
        printf("location in second half: %ld\n", location_in_second_half);
        return 1;
    }

    return 0;
}

long get_file_len(FILE *file) {
    fseek(file, 0, SEEK_END);
    long file_len = ftell(file);
    rewind(file);

    return file_len;
}
