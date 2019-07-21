#include <stdio.h>
#include <stdlib.h>

#define MIN_NUM_ARGS (3)

int main(int argc, char **argv) {
    int i;
    FILE* file;

    if (argc < MIN_NUM_ARGS) {
        fprintf(stderr, "Error");
        exit(1);
    }

    for (i=2; i<argc; i++) {
        file = fopen(argv[i], "w");
        if (file) {
            fprintf(file, "%s", argv[1]);
        } else {
            fprintf(stderr, "Error printing to %s\n", argv[i]);
        }
    }

    return 0;
}
