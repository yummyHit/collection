#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_STACK 65536

void cmd_parser(char *cmd, char *options[], char *envp[], char *data) {
	int	ret = 0, bytes = 0;
	char *buf = (char*)calloc(MAX_STACK, sizeof(char*));
	pid_t pid_child;
	posix_spawn_file_actions_t act;

	if(posix_spawn_file_actions_init(&act) != 0) {
		fprintf(stderr, "Fail: file_action_init:%s \n", buf);
		exit(EXIT_FAILURE);
	}

	int in[2], out[2];

	pipe(in), pipe(out);

	posix_spawn_file_actions_addclose(&act, in[0]);
	posix_spawn_file_actions_addclose(&act, out[0]);

	posix_spawn_file_actions_adddup2(&act, in[1], 0);
	posix_spawn_file_actions_adddup2(&act, out[1], 1);

	posix_spawn_file_actions_addclose(&act, in[1]);
	posix_spawn_file_actions_addclose(&act, out[1]);

	if(posix_spawn(&pid_child, cmd, &act, NULL, options, envp) != 0)
		fprintf(stderr, "posix_spawn() failed...\n");

	close(in[1]), close(out[1]);

	while(bytes < MAX_STACK) {
		int end = read(out[0], buf + bytes, MAX_STACK - bytes);
		if(end == 0) break;
		bytes += end;
	}

	strncpy(data, buf, bytes);

	waitpid(pid_child, &ret, 0);
	posix_spawn_file_actions_destroy(&act);
}

char **split_data(char *data, const char *delim, int *index) {
	char *ptr = NULL, *rptr = NULL;
	int i = 0;

	for(i = 0, *index = 0; data[i]; i++) if((data[i] == ' ' || data[i] == '\t' || data[i] == '\n') && (data[i+1] != ' ' && data[i+1] != '\t' && data[i+1] != '\n')) (*index)++;
	char **item = (char**)calloc(*index, sizeof(char**));

	for(i = 0, ptr = strtok_r(data, delim, &rptr); ptr; ptr = strtok_r(NULL, delim, &rptr))
		if(ptr && strlen(ptr) > 0 && *ptr > 0x20) {
			int len = strlen(ptr);
			*(item + i) = (char*)calloc(len, sizeof(char*));
			strncpy(*(item + i), ptr, len);
			i++;
		}

	return item;
}

int main(int argc, char *argv[], char *envp[]) {
	char *get_cmd = NULL;
	char *options[MAX_STACK / 64] = {0,};
	char data[MAX_STACK] = {0,};
	int ret = 2;

	if(argc < 3) {
		fprintf(stderr, "Usage: %s `which command` <command> [ <option1> <option2> ... ]\n", argv[0]);
		fprintf(stderr, "       ex) `which ls` ls -l\n");
		exit(0);
	} else {
		get_cmd = (char*)calloc(strlen(argv[1]), sizeof(char*));
		strncpy(get_cmd, argv[1], strlen(argv[1]));
		int len = argc - 1;
		while(--len) {
			options[ret - 2] = (char*)calloc(strlen(argv[ret]), sizeof(char*));
			strncpy(options[ret - 2], argv[ret], strlen(argv[ret]));
			ret++;
		}
	}

	int size = 0, i = 0;
	char *rptr = NULL;

#if 0	// if you want to use file I/O, zero flag to set!

	FILE *fp = fopen("./test.txt", "r");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	char *data = (char*)calloc(size, sizeof(char));
	fread(data, 1, size, fp);
	fclose(fp);

#else

	cmd_parser(get_cmd, options, envp, data);

#endif
	char **item = split_data(data, " \t\n", &size);

	for(i = 0; i < size; i++) {
		printf("item[%d]: %s\n", i, item[i]);
		memset(item[i], '\0', strlen(item[i]));
		free(item[i]);
	}

	memset(item, '\0', i - 1);
	free(item);

#if 0	// if you want to use file I/O, zero flag to set!
	memset(data, '\0', strlen(data));
	free(data);
#endif

	return 0;
}
