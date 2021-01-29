#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main() {

	char buf[BUFSIZE];
	int year = 2021, month = 1, day = 12;
	sprintf(buf, "%d-%d-%d", year, month, day);
	puts(buf);

	exit(0);
}
