#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <glob.h>

#define DELIMS " \t\n"

struct cmd_st {
    glob_t globres;
};

static void prompt(void) {
    printf("mysh-0.1$ ");
} 

static void parse(char *line, struct cmd_st *res) {
    
    char *tok;
    int i = 0, tmp;

    while (1) {
        tok = strsep(&line, DELIMS);
        if (tok == NULL)
            break;
        if (tok[0] == '\0') // 空串
            continue;
        
        if ((tmp = glob(tok, GLOB_NOCHECK|GLOB_APPEND*i, NULL, &res->globres)) != 0) {
            fprintf(stderr, "glob() error: %d\n", tmp);
            exit(1);
        }
        i = 1;
    }
}


int main() {

    char *linebuf = NULL;
    size_t linebuf_size = 0;
    struct cmd_st cmd;
    pid_t pid;

    while (1) {
        
        prompt();

        if (getline(&linebuf, &linebuf_size, stdin) < 0) {
            perror("getline()");
            exit(1);
        }

        parse(linebuf, &cmd);
        
        if (0) {    // 内部命令
            // TODO: do something
        } else {    // 外部命令
            pid = fork();

            if (pid < 0) {
                perror("fork()");
                exit(1);
            }
            if (pid == 0) { // child
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp()");
                exit(1);
            } else {    // parent
                wait(NULL);
            }
        }
    
    }

    exit(0);
}
