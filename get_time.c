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

int main(int argc, char **argv) {
	char msg[MSG_SIZE] = {0,};
	printf("%s", get_nowtime(msg));
	usleep(1000000);
	printf("%s", get_nowtime(msg));
	usleep(1000000);
	printf("%s", get_nowtime(msg));
	return 0;
}

