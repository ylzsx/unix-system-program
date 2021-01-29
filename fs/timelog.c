#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"
#define BUFSIZE 1024

int main() {

    FILE *fp;
    int count = 0;
    char buf[BUFSIZE];
    time_t stamp;
    struct tm *tm;

    fp = fopen(FNAME, "a+");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fp) != NULL)
        count++;

    while (1) {
        time(&stamp);
        tm = localtime(&stamp);
        strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S", tm);
        fprintf(fp, "%-4d%s\n", ++count, buf);
        fflush(fp); // 默认为全缓冲模式

        sleep(1);
    }

    fclose(fp);
    exit(0);
}
