/* Copyright 2019. yummyHit. All rights reserved.
 * Execute brute force for not having dictionary file
 * This program need only test reversing contents
 * Some fix for string length and memory allocation
 * Solution maybe add to files io for maximum memory size
 * @using: ./bruteforce <target binary> <length>
 * @compile: gcc -o bruteforce bruteforce.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

static void generate(char *file_path, int bf_strlen);
int my_popen(char *cmd, char *buf, size_t buf_len);
char *replace(const char *s, char ch, const char *repl);
char *get_nowtime(char *msg);
//void buffer_init(char ****************buffer, int bf_strlen, int alphaLen);

const char *alphabet = "abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789"
"!@#$%^&()-_=+\\|`~[{]};:'\",<.>/?";

int main(int argc, char *argv[]) {
	char *file_path = NULL;
	int bf_strlen = 0;

	if(argc != 3) {
		fprintf(stderr, "Argument Count Error. Please check using this program.\nUsage: %s <BruteForce File> <String Length>\nEx) %s /root/yummyHit/file 5\n", argv[0], argv[0]);
		exit(1);
	} else {
		if(strncmp(argv[1], "/", 1) && strncmp(argv[1], "./", 2)) {
			fprintf(stderr, "Brute Force File Path is unset.\nPlease write absolute path or relative path for file path.\n");
			exit(1);
		}
		file_path = (char*)malloc(strlen(argv[1]));
		strncpy(file_path, argv[1], strlen(argv[1]));
		bf_strlen = strtol(argv[2], (char**)NULL, 10); 
	}
	
	generate(file_path, bf_strlen);
	return 0;
}

static void generate(char *file_path, int bf_strlen) {
	int alphaLen = strlen(alphabet);
	unsigned long long int bufLen = (bf_strlen + 1) * (unsigned long long int)pow(alphaLen, bf_strlen);
	char *buffer = (char*)malloc(sizeof(char) * bufLen);
//	char ****************buffer = NULL;
	char msg[256] = {0,}, use_cmd[1024] = {0,}, get_stdout[1024] = {0,};
	char *ptr = NULL, *rptr = NULL;

	printf("bufLen: %lld\n", bufLen);

//	buffer_init(buffer, bf_strlen, alphaLen);

	printf("buffer size: %zd\n", malloc_usable_size(buffer));

	if(buffer == NULL) {
		fprintf(stderr, "Not enough memory.\n");
		exit(1);
	}

	printf("Start (%dbytes) %s", bf_strlen, get_nowtime(msg));

	if(bf_strlen == 2) {
		for(int i = 0, let0 = 0, let1 = 0; i < bufLen; i += (bf_strlen + 1)) {
			buffer[i] = alphabet[let0];
			buffer[i+1] = alphabet[let1++];
			buffer[i+2] = '\n';
			if(let1 == alphaLen) {
				let1 = 0;
				let0++;
				if(let0 == alphaLen) let0 = 0;
			}
		}
	} else if(bf_strlen == 3) {
		for(int i = 0, let0 = 0, let1 = 0, let2 = 0; i < bufLen; i += (bf_strlen + 1)) {
			buffer[i] = alphabet[let0];
			buffer[i+1] = alphabet[let1];
			buffer[i+2] = alphabet[let2++];
			buffer[i+3] = '\n';
			if(let2 == alphaLen) {
				let2 = 0;
				let1++;
				if(let1 == alphaLen) {
					let1 = 0;
					let0++;
					if(let0 == alphaLen) let0 = 0;
				}
			}
		}
	} else if(bf_strlen == 4) {
		for(int i = 0, let0 = 0, let1 = 0, let2 = 0, let3 = 0; i < bufLen; i += (bf_strlen + 1)) {
			buffer[i] = alphabet[let0];
			buffer[i+1] = alphabet[let1];
			buffer[i+2] = alphabet[let2];
			buffer[i+3] = alphabet[let3++];
			buffer[i+4] = '\n';
			if(let3 == alphaLen) {
				let3 = 0;
				let2++;
				if(let2 == alphaLen) {
					let2 = 0;
					let1++;
					if(let1 == alphaLen) {
						let1 = 0;
						let0++;
						if(let0 == alphaLen) let0 = 0;
					}
				}
			}
		}
	} else if(bf_strlen == 5) {
		for(int i = 0, let0 = 0, let1 = 0, let2 = 0, let3 = 0, let4 = 0; i < bufLen; i += (bf_strlen + 1)) {
			buffer[i] = alphabet[let0];
			buffer[i+1] = alphabet[let1];
			buffer[i+2] = alphabet[let2];
			buffer[i+3] = alphabet[let3];
			buffer[i+4] = alphabet[let4++];
			buffer[i+5] = '\n';
			if(let4 == alphaLen) {
				let4 = 0;
				let3++;
				if(let3 == alphaLen) {
					let3 = 0;
					let2++;
					if(let2 == alphaLen) {
						let2 = 0;
						let1++;
						if(let1 == alphaLen) {
							let1 = 0;
							let0++;
							if(let0 == alphaLen) let0 = 0;
						}
					}
				}
			}
		}
	} else if(bf_strlen == 6) {
		for(int i = 0, let0 = 0, let1 = 0, let2 = 0, let3 = 0, let4 = 0, let5 = 0; i < bufLen; i += (bf_strlen + 1)) {
			buffer[i] = alphabet[let0];
			buffer[i+1] = alphabet[let1];
			buffer[i+2] = alphabet[let2];
			buffer[i+3] = alphabet[let3];
			buffer[i+4] = alphabet[let4];
			buffer[i+5] = alphabet[let5++];
			buffer[i+6] = '\n';
			if(let5 == alphaLen) {
				let5 = 0;
				let4++;
				if(let4 == alphaLen) {
					let4 = 0;
					let3++;
					if(let3 == alphaLen) {
						let3 = 0;
						let2++;
						if(let2 == alphaLen) {
							let2 = 0;
							let1++;
							if(let1 == alphaLen) {
								let1 = 0;
								let0++;
								if(let0 == alphaLen) let0 = 0;
							}
						}
					}
				}
			}
		}
	}

	for(ptr = strtok_r(buffer, "\n", &rptr); ptr; ptr = strtok_r(NULL, "\n", &rptr)) {
		ptr = replace(ptr, '\\', "\\\\");
		ptr = replace(ptr, '"', "\\\"");
		ptr = replace(ptr, '$', "\\$");
		ptr = replace(ptr, '`', "\\`");
		sprintf(use_cmd, "echo \"%s\" | %s", ptr, file_path);
		my_popen(use_cmd, get_stdout, sizeof(get_stdout));
		if(strstr(get_stdout, "Output >> TAXI")) {
			printf("find ptr: %s\nfind cmd: %s\n", ptr, use_cmd);
			write(STDOUT_FILENO, get_stdout, sizeof(get_stdout));
			printf("Find it!! %s", get_nowtime(msg));
		}
	}

	printf("Program Finished %s", get_nowtime(msg));

	free(buffer);
}

int my_popen(char *cmd, char *buf, size_t buf_len) {
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

	while (!feof(fp) && remain > 0)  {
		len = fread(p, 1, remain, fp);
		p+=len;
		remain -= len;
	}
	*p = 0;
	pclose(fp);

	return len;
}

char *replace(const char *s, char ch, const char *repl) {
	int count = 0;
	const char *t;
	for(t = s; *t; t++) count += (*t == ch);

	size_t rlen = strlen(repl);
	char *res = malloc(strlen(s) + (rlen-1) * count + 1);
	char *ptr = res;
	for(t = s; *t; t++) {
		if(*t == ch) {
			memcpy(ptr, repl, rlen);
			ptr += rlen;
		} else {
			*ptr++ = *t;
		}
	}
	*ptr = 0;
	return res;
}

char *get_nowtime(char *msg) {
	struct tm *date; 
	const time_t t = time(NULL); 
	date = localtime(&t); 
	memset(msg, 0, 256);
	sprintf(msg, "Current Time.... %d:%d:%d\n\n", date->tm_hour, date->tm_min, date->tm_sec);
	return msg;
}

#if 0
void buffer_init(char ****************buffer, int bf_strlen, int alphaLen) {
	switch(bf_strlen) {
		case 16:
			buffer = (char****************)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 15:
			buffer = (char***************)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 14:
			buffer = (char**************)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 13:
			buffer = (char*************)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 12:
			buffer = (char************)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 11:
			buffer = (char***********)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 10:
			buffer = (char**********)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 9:
			buffer = (char*********)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 8:
			buffer = (char********)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 7:
			buffer = (char*******)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 6:
			buffer = (char******)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 5:
			buffer = (char*****)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 4:
			buffer = (char****)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 3:
			buffer = (char***)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 2:
			buffer = (char**)malloc(sizeof(char) * alphaLen * 2);
			break;
		case 1:
			buffer = (char*)malloc(sizeof(char) * alphaLen * 2);
			break;
		default:
			buffer = (char)malloc(sizeof(char) * alphaLen * 2);
			break;
	}

	if(!buffer) buffer_init(buffer, bf_strlen, alphaLen);
	else {
		fprintf(stderr, "buffer memory allocation error!!\n");
		exit(1);
	}
}
#endif
