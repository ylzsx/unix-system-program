#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

#define PAT "/etc/a*.conf"

static int errfunc_(const char *epath, int eerrno) {

    puts(epath);
    fprintf(stderr, "Error Msg: %s\n", strerror(eerrno));
    return 0;
}

int main() {

    glob_t globres;
    int err, i;

    err = glob(PAT, GLOB_NOSORT, errfunc_, &globres);
    if (err) {
        fprintf(stderr, "Error code = %d\n", err);
        exit(1);
    }

    for (i = 0; i < globres.gl_pathc; i++)
        puts(globres.gl_pathv[i]);
    
    globfree(&globres);

    exit(0);
}
