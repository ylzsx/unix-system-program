#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

int main(int argc, char **argv) {

    time_t stamp;
    struct tm *tm;
    char fmstr[FMTSTRSIZE] = {'\0'};
    char timestr[TIMESTRSIZE];
    char c = '\0';
    FILE *fp = stdout;

    stamp = time(NULL);
    tm = localtime(&stamp);
    
    while(1) {
        c = getopt(argc, argv, "-Y:mdH:MS");
        if (c < 0)
            break;
        switch (c) {
            case 1:
                fp = fopen(argv[optind-1], "w");
                if (fp == NULL) {
                    perror("fopen()");
                    fp = stdout;
                }
                break;
            case 'Y':
                if (strcmp(optarg, "2") == 0)
                    strncat(fmstr, "%y ", FMTSTRSIZE);
                else if (strcmp(optarg, "4") == 0)
                    strncat(fmstr, "%Y ", FMTSTRSIZE);
                else 
                    fprintf(stderr, "Invalid argument of Y\n");
                break;
            case 'm':
                strncat(fmstr, "%m ", FMTSTRSIZE);
                break;
            case 'd':
                strncat(fmstr, "%d ", FMTSTRSIZE);
                break;
            case 'H':
                if (strcmp(optarg, "12") == 0)
                    strncat(fmstr, "%I(%P) ", FMTSTRSIZE);
                else if (strcmp(optarg, "24") == 0)
                    strncat(fmstr, "%H ", FMTSTRSIZE);
                else 
                    fprintf(stderr, "Invalid argument of H\n");
                break;
            case 'M':
                strncat(fmstr, "%M ", FMTSTRSIZE);
                break;
            case 'S':
                strncat(fmstr, "%S ", FMTSTRSIZE);
                break;
            default:break;
        }
    }

    strncat(fmstr, "\n", FMTSTRSIZE);
    strftime(timestr, TIMESTRSIZE, fmstr, tm);
    fputs(timestr, fp);
    
    if (fp != stdout)
        fclose(fp);

    exit(0);
}
