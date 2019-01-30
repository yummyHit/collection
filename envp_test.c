#include <stdio.h>

int main(int argc, char *argv[], char **envp) {
	int i = 1;
	char **env = NULL, *thisEnv = NULL;

	for(env = envp; *env != 0; env++) {
		thisEnv = *env;
		printf("envp: %s, envp address: %p\n", thisEnv, thisEnv);
	}

	for(env = envp; *env != 0; env++, i++) {
		printf("argv[%d]: %s, argv[%d] address: %p\n", i, argv[argc + i], i, argv[argc + i]);
	}

	printf("\n\n...All variable..\n\ni address: %p\nenv address: %p\nthisEnv address: %p\nenvp[0] address: %p\nargv[argc + 1] address: %p\n", &i, *env, thisEnv, envp[0], argv[argc + 1]);

	return 0;
}
