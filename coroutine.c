#include <stdio.h>

#define crBegin static int state=0; \
	switch(state) { \
	case 0:
		#define crReturn(i, x) do { \
			state = i; \
			return x; \
			case i:; \
	} while (0)
	#define crFinish \
}

int loop() {
	static int i;
	crBegin;
	for(i = 1; i < 10; i++)
		crReturn(1, i);
	crFinish;
}

int main() {
	int i = 0;

	for(;i = loop();) 
		if(i > 100) break;
		else printf("%d\n", i); 

	return 0;
}
