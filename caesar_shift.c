#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	int shift_time = 0, i = 0, len = 0;
	char *str = NULL;

	if(argc < 3) {
		fprintf(stderr, "Usage: %s <string with double quotation> <shift times>\n", argv[0]);
		exit(1);
	}

	shift_time = strtol(argv[2], NULL, 10);
	while(shift_time < 0) shift_time += 26;
	while(shift_time > 26) shift_time -= 26;

	len = strlen(argv[1]);
	str = (char*)malloc(sizeof(char) * len);
	strncpy(str, argv[1], len);
	str[len] = '\0';
//	for(i = 0; *(str + i); i++)
//		if(islower(*(str + i)))
//			*(str + i) = *(str + i) - 'a' + 'A';
//		else
//			if(isupper(*(str + i)))
//				*(str + i) = *(str + i) - 'A' + 'a';
	printf("Shift String is...\n");
	i = 0;

	while(*(str + i)) {
		if(*(str + i) >= 'A' && *(str + i) <= 'Z') {
			if((*(str + i) + shift_time) > 'Z') {
				int diff_count = *(str + i) + shift_time - 90;
				printf("%c", 'A' + diff_count - 1);
			} else {
				printf("%c", *(str + i) + shift_time);
			}
		}
		else if(*(str + i) >= 'a' && *(str + i) <= 'z') {
			if((*(str + i) + shift_time) > 'z') {
				int diff_count = *(str + i) + shift_time - 122;
				printf("%c", 'a' + diff_count - 1);
			} else {
				printf("%c", *(str + i) + shift_time);
			}
		}
		i++;
	}
	printf("\n");

	return 0;
}

