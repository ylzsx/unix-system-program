#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <glob.h>

#define BUFSIZE 1024

static int path_noloop(const char *path) {
    
    char *pos; 
    pos = strrchr(path, '/');
    
    if (pos == NULL)
        exit(1);
    if (strcmp(pos + 1, ".") == 0 || strcmp(pos + 1, "..") == 0)
        return 0;
    return 1;
}


static int errfunc_(const char *epath, int eerrno) {

    puts(epath);
    fprintf(stderr, "Error Msg: %s\n", strerror(eerrno));
    return 0;
}


static int64_t mydu(const char *path) {

    static struct stat statres;
    static char nextpath[BUFSIZE];
    glob_t globres;
    int i;
    static int err;
    int64_t sum;

    if (lstat(path, &statres) < 0) {
        fprintf(stderr, "%s lstat(): %s\n", path, strerror(errno));
        exit(1);
    }

    if (!S_ISDIR(statres.st_mode)) {    // 非目录
        return statres.st_blocks;
    }

    strncpy(nextpath, path, BUFSIZE);
    strncat(nextpath, "/*", BUFSIZE);
    err = glob(nextpath, GLOB_NOSORT, errfunc_, &globres);
    if (err != 0) {
        fprintf(stderr, "Error Code: %d\n", err);
        exit(1);
    }

    strncpy(nextpath, path, BUFSIZE);
    strncat(nextpath, "/.*", BUFSIZE);
    err = glob(nextpath, GLOB_NOSORT|GLOB_APPEND, errfunc_, &globres);
    if (err != 0) {
        fprintf(stderr, "Error Code: %d\n", err);
        exit(1);
    }

    sum = statres.st_blocks;
    for (i = 0; i < globres.gl_pathc; i++) {
        if (path_noloop(globres.gl_pathv[i]))
            sum +=  mydu(globres.gl_pathv[i]);
    }

    globfree(&globres);

    return sum;
}

static char *getpwd(char *buf, size_t size) {

    if(getcwd(buf, size) == NULL) {
        perror("getpwd");
        exit(1);
    }

    return buf;
}

int main(int argc, char **argv) {

    int64_t blocks;
    char path[BUFSIZE];
    int i = 1;

    if (argc == 1) {
        getpwd(path, BUFSIZE);
        blocks = mydu(path) / 2;
        printf("%s: %ld\n", path, blocks);
    } else {
        while (1) {
            if (argv[i] == NULL)
                break;
            blocks = mydu(argv[i]) / 2;
            printf("%s: %ld\n",argv[i], blocks);
            i++;
        }
    }


    exit(0);
}
