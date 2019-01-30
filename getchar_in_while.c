#include <stdio.h>

int main() {
	int i = 0, chk = 0, flag = 0;
	char in[7] = {0,}, out[7] = {0,}, table[] = "afk";

	char a;
	printf("how many questions do you have?\n");

	scanf("%d", &a);
	printf("fi?:%c\n", a);

	while(getchar() != '\n') {
		chk = 1;
		printf("Enter word: ");
		for(i = 0; i < 7; i++) {
			scanf("%c", &in[i]);
			if(in[i] == 'a' || in[i] == 'f' || in[i] == 'k') {
				if(in[i] == 'a') out[i] = table[0];
				else if(in[i] == 'f') out[i] = table[1];
				else if(in[i] == 'k') out[i] = table[2];
			} else {
				printf("finale! welcome back, afk\n");
				flag = 1;
				return 1;
			}
		}
	}

	if(chk && !flag) printf("Success! Flag is... nothing\n");

	return 0;
}

