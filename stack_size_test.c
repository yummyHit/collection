/* Copyright 2019. yummyHit. All rights reserved.
 * How can use stack size with file io
 * can't believe ulimit's size, this source can help that solution
 * @using: ./stack_size_test
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_STACK_SIZE 65536

int main(int argc, char **argv) {
	char filename[100];
	char command[128];
	int ret = 0;

	for(size_t i = 0; i < MAX_STACK_SIZE; i++) {
		memset(filename, 0, sizeof(filename));
		sprintf(filename, "/tmp/%010ld.txt", i);
		FILE *fp = fopen(filename, "w");

		if (fp == NULL) {
			printf("fp(count: %ld): failed!\n", i);
			return ret;
		} else {
			memset(command, 0, sizeof(command));
			sprintf(command, "rm %s 2>/dev/null", filename);
			ret = WEXITSTATUS(system(command));
			if(ret == 127)
				printf("can't execute /bin/sh. Last failed command is (%s)\n", command);
			else if(ret == -1)
				printf("fork() error\n");
		}

		if (i % 100 == 0)
			printf("fp(count: %ld) = %p: ok.\n", i, fp);
	}

	return 0;
}
