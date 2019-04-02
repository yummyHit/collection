#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	char *output = (char*)malloc(sizeof(char) * 1024);
	char *get_cmd = NULL;
	int output_len = 1024, cmd_len = 0, count = 0;

	if(argc != 2) {
		fprintf(stderr, "Usage: %s <cmd>\n", argv[0]);
		exit(0);
	}

	get_cmd = (char*)calloc(strlen(argv[1]), sizeof(char));
	snprintf(get_cmd, 1024, "%s", argv[1]);

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
	return 0;
}
