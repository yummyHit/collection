#include <stdio.h>
#include <string.h>

#define SIZE_1K 1024

int main(void) {
	char str[SIZE_1K];
	int len;
	while(1) {
		scanf("%[^\n]s", str);

		if(strncmp(str, "END", 3) == 0)
			return 0;
		len = strlen(str);
		for(int i = len - 1; i >= 0; i--) {
			printf("%c", str[i]);
		}
		__fpurge(stdin);
		printf("\n");
	}
	return 0;
}
