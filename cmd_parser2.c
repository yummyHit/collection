/* Copyright 2019. yummyHit. All rights reserved.
 * Use posix library for system print out in prompt
 * for need to print out when system function or exec() functions
 * @using: ./cmd_parser2 "commands (with option ok)"
 */

#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_STACK 65536

int main(int argc, char *argv[], char *envp[]) {
	char *get_cmd = NULL;
	char *options[MAX_STACK] = {0,};
	char buf[MAX_STACK] = {0,};
	int	ret = 2, bytes = 0;
	pid_t pid_child;
	posix_spawn_file_actions_t act;

	if(argc < 3) {
		fprintf(stderr, "Usage: %s `which command` <command> [ <option1> <option2> ... ]\n", argv[0]);
		fprintf(stderr, "       ex) `which ls` ls -l\n");
		exit(0);
	} else {
		get_cmd = (char*)calloc(strlen(argv[1]), sizeof(char));
		strncpy(get_cmd, argv[1], strlen(argv[1]));
		int len = argc - 1;
		while(--len) {
			options[ret - 2] = (char*)calloc(strlen(argv[ret]), sizeof(char));
			strncpy(options[ret - 2], argv[ret], strlen(argv[ret]));
			ret++;
		}
	}

	memset(buf, 0, sizeof(buf));

	if(posix_spawn_file_actions_init(&act) != 0) {
		fprintf(stderr, "Fail: file_action_init:%s \n", buf);
		exit(EXIT_FAILURE);
	}

#if 0 // if you want to use file I/O, zero flag to set!
//	char * const file_path = "/root/test/spawn.txt";	// absolute path
	char * const file_path = "./spawn.txt";		// relative path

	posix_spawn_file_actions_addopen(&act, STDOUT_FILENO, file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	posix_spawn_file_actions_addopen(&act, STDERR_FILENO, "/dev/null", O_WRONLY, 0);

//	if(posix_spawn(&pid_child, get_cmd, &act, NULL, options, envp) != 0)	// when absolute path
	if(posix_spawnp(&pid_child, get_cmd, &act, NULL, options, envp) != 0)	// when relative path
		fprintf(stderr, "posix_spawn() failed...\n");

#else // it use input variable to output data like popen or fork-exec.

	int in[2], out[2];

	pipe(in);
	pipe(out);

	posix_spawn_file_actions_addclose(&act, in[0]);
	posix_spawn_file_actions_addclose(&act, out[0]);

	posix_spawn_file_actions_adddup2(&act, in[1], 0);
	posix_spawn_file_actions_adddup2(&act, out[1], 1);

	posix_spawn_file_actions_addclose(&act, in[1]);
	posix_spawn_file_actions_addclose(&act, out[1]);

	if(posix_spawn(&pid_child, get_cmd, &act, NULL, options, envp) != 0)
		fprintf(stderr, "posix_spawn() failed...\n");

	close(in[1]), close(out[1]);

	while(bytes < MAX_STACK) {
		int end = read(out[0], buf + bytes, MAX_STACK - bytes);
		if(end == 0) break;
		bytes += end;
	}

	printf("out[0] buf is.. \n%s\n", buf);

#endif

	waitpid(pid_child, &ret, 0);
	posix_spawn_file_actions_destroy(&act);

	return 0;
}
