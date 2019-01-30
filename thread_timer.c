#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>				// 구조체, 시간함수를 사용하기 위하여 헤더파일 선언
#include <pthread.h>

static void* plus() {			// 쓰레드를 생성할 때 호출할 함수 정의
	int i = 0;
	while (i<5000000) {			// 500만번 덧셈 연산
		i++;
	}
}

int main() {
	pthread_t t1[50];			// 쓰레드 구조체 변수 50개
	int i;						// 반복문에 사용할 변수
	clock_t time1, time2;		// 시간 비교에 사용할 변수 (long 타입)
	struct tms mytms;			// 시간 비교에 사용할 구조체 변수

	time1 = times(&mytms);		// 현재시간을 time1에 저장 (시작시간)

	for (i = 0;i < 50;i++) {		// 쓰레드 50개 생성
		pthread_create(&t1[i], NULL, plus, "ab");
	}

	for (i = 0;i < 50;i++) {		// 쓰레드 50개 종료 대기
		pthread_join(t1[i], NULL);
	}

	time2 = times(&mytms);		// 현재시간을 time2에 저장 (종료시간)

	printf("Real time : %.1f sec\n", (double)(time2 - time1) / CLOCKS_PER_SEC);	// 실제 걸린 시간 출력, windows: CLK_TCK, *nix: CLOCKS_PER_SEC

	printf("User time : %.1f sec\n", (double)mytms.tms_utime / CLOCKS_PER_SEC);	// 사용자 모드 실행시간 출력

	printf("System time : %.1f sec\n", (double)mytms.tms_stime / CLOCKS_PER_SEC);	// 시스템 모드 실행시간 출력
}
