#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {

    FILE *sfp, *dfp;
    char *buf = NULL;
    int res, count = 0;
    size_t len = 0;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source_path> <dest_path>\n", argv[0]);
        exit(1);
    }

    sfp = fopen(argv[1], "r");
    dfp = fopen(argv[2], "w");

    // 读10行
    while(1) {
        res = getline(&buf, &len, sfp);
        count++;
        if (res < 0)
            break;
        if (count == 10)
            continue;
        fputs(buf, dfp);
    }

    fclose(dfp);
    fclose(sfp);

    exit(0);
}
