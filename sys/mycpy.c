#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {

	int sfd, dfd;
	char buf[BUFSIZE];
	int len, ret, pos;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <source_path> <dest_path>\n", argv[0]);
		exit(1);
	}

	sfd = open(argv[1], O_RDONLY);
	if (sfd < 0) {
		perror("source file open()");
		exit(1);
	}
	dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
	if (dfd < 0) {
		close(sfd);		// 防止内存泄漏
		perror("dest file open()");
		exit(1);
	}

	while (1) {
		len = read(sfd, buf, BUFSIZE);
		if (len < 0) {
			perror("read()");
			break;
		} else if (len == 0) {
			break;
		}

		pos = 0;
		while (len > 0) {
			ret = write(dfd, buf + pos, len);
			if (ret < 0) {
				perror("write()");
				exit(1);	// 这里会有内存泄漏现象
			}
			pos += ret;
			len -= ret;
		}
	}


	close(dfd);
	close(sfd);

	exit(0);
}
