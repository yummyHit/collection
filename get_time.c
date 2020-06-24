/* Copyright 2019. yummyHit. All rights reserved.
 * get time every 1 second
 * @using: ./get_time
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MSG_SIZE 256

char *get_nowtime(char *msg) {
	struct tm *date; 
	const time_t t = time(NULL); 
	date = localtime(&t); 
	memset(msg, 0, 256);
	sprintf(msg, "Current Time.... %d:%d:%d\n\n", date->tm_hour, date->tm_min, date->tm_sec);
	return msg;
}

long long time_diff(unsigned flag) {
	const long long nanosec = 1000000000LL;
	static struct timespec s, e;
	static long long diff = 0;
	if(flag) {
		if(clock_gettime(CLOCK_MONOTONIC, &e) == -1)
			printf("clock_gettime error\n");
		diff = nanosec * (e.tv_sec - s.tv_sec) + (e.tv_nsec - s.tv_nsec);
	} else {
		diff = 0;
		if(clock_gettime(CLOCK_MONOTONIC, &s) == -1)
			printf("clock_gettime error\n");
	}

	return diff / 1000000;
}

int main(int argc, char **argv) {
	char msg[MSG_SIZE] = {0,};
	time_diff(0);
	printf("%s", get_nowtime(msg));
	usleep(1000000);
	printf("%s", get_nowtime(msg));
	usleep(1000000);
	printf("%s", get_nowtime(msg));
	printf("Total elapsed: %lld ms\n", time_diff(1));
	return 0;
}

