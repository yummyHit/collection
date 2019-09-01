/* Copyright 2019. yummyHit. All rights reserved.
 * safe memory free for use after free vulnerability
 * @using: ./safe_free
 * @function: safe_free()
 *  param 1. character pointer
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define safe_free(ptr) ({ if(ptr != NULL) { memset(ptr, 0, strlen(ptr)); free(ptr); } NULL; })

int main() {
	char *ptr1 = NULL, *ptr2 = NULL;
	unsigned num = 123;
	ptr2 = (char*)malloc(sizeof(char) * sizeof(num));
	*ptr2 = num;

	printf("num: %u\n", num);
	printf("&num: %p\n", &num);
	printf("ptr2: %p\n", ptr2);
	printf("*ptr2: %u\n", *ptr2);
	printf("ptr1: %p\n", ptr1);

	printf("_____safe_free_____\n");
	printf("safe_free(ptr1): %p\n", safe_free(ptr1));
	printf("safe_free(ptr2): %p\n", safe_free(ptr2));
	
	return 0;
}
