#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	if (argc < 2) {
		fprintf(stderr, "Usage:%s <file_path>\n", argv[0]);
		exit(1);
	}

	FILE *fp = NULL;
	char *linebuf = NULL;
	size_t linesize = 0;


	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen()");
		exit(1);
	}

	while(1) {
		if (getline(&linebuf, &linesize, fp) < 0)
			break;
		printf("%ld\n", strlen(linebuf));
		printf("%ld\n", linesize);
 	}

//	free(linebuf);

	fclose(fp);
	exit(0);
}
