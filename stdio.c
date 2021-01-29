#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {

	FILE *fp = NULL;

	fp = fopen("test", "r");
	if (fp == NULL) {
		// fprintf(stderr, "errno = %d\n", errno);
		// perror("fopen()");
		fprintf(stderr, "fopen(): %s\n", strerror(errno));
		exit(1);
	}


	fclose(fp);

	exit(0);
}
