#include <stdio.h>
#include <stdlib.h>

static void f1(void) {
    printf("%s is working!\n", __FUNCTION__);
}

static void f2(void) {
    printf("%s is working!\n", __FUNCTION__);
}

static void f3(void) {
    printf("%s is working!\n", __FUNCTION__);
}

int main() {

    puts("Begin!");

    atexit(f1);
    atexit(f2);
    atexit(f3);

    puts("End!");
    exit(0);
}
