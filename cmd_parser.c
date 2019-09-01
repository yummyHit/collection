/* Copyright 2019. yummyHit. All rights reserved.
 * Use popen() for get the system stdout value
 * for need to print out when system function or exec() functions
 * @using: ./cmd_parser "commands (with option ok)"
 * @function: popen_used()
 *  param 1. use command for system
 *  param 2. get print out in prompt
 *  param 3. get buffer length
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_STACK 1024
#define MAX_STACK 65536

int popen_used(const char *cmd, char *buf, size_t buf_len) {
	FILE *fp = NULL;

	memset(buf, 0x00, buf_len);

	fp = popen(cmd, "r");
	if(fp == NULL) {
		perror("errno : ");
		exit(0);
	}

	char *p = buf;
	int len = 0;
	int remain = buf_len;

	while(!feof(fp) && remain > 0)  {
		len = fread(p, 1, remain, fp);
		p+=len;
		remain -= len;
	}
	*p = 0;
	pclose(fp);

	return len;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *output = (char*)malloc(sizeof(char) * MAX_STACK);
	char *get_cmd = NULL;
	int output_len = MAX_STACK, cmd_len = 0, count = 0;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <cmd>\n", argv[0]);
		exit(0);
	}

	get_cmd = (char*)calloc(strlen(argv[1]), sizeof(char));
	snprintf(get_cmd, strlen(argv[1]), "%s", argv[1]);

#if 0
	fp = popen(get_cmd, "r");
	if(fp == NULL) {
		perror("errno: ");
		exit(0);
	}

	while(!feof(fp) && output_len > 0) {
		cmd_len = fread(output, 1, output_len, fp);
		output += cmd_len;
		output_len -= cmd_len;
		count++;
	}

	pclose(fp);
	printf("%s\n", output - (cmd_len * count));
#endif

	popen_used(get_cmd, output, output_len);
	printf("%s\n", output);

	return 0;
}
