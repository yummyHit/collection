#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/times.h>
#include <pthread.h>

static void plus() {			// 호출할 함수 정의
	int i = 0;
	while (i<5000000) {			// 500만번 덧셈 연산
		i++;
	}
}

int main(void) {
	pid_t current_pid, child_pid;
	int i = 0, k = 0;
	int state;
	struct tms mytms;
	clock_t t1, t2;

	t1 = times(&mytms);

	for (i = 0;i<50;i++) {

		if ((current_pid = fork()) == 0) {

			plus();

			exit(0);
		}

		else if (current_pid < 0) {
			printf("Error\n");
			exit(1);
		}

	}

	while ((child_pid = wait(&state)) > 0) {

	}

	if (child_pid == -1) {
		t2 = times(&mytms);
		printf("Real time : %.1f sec\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
		printf("User time : %.1f sec\n", (double)mytms.tms_utime / CLOCKS_PER_SEC);
		printf("System time : %.1f sec\n", (double)mytms.tms_stime / CLOCKS_PER_SEC);
		printf("child_pid: %d\n", child_pid);
	}
}
