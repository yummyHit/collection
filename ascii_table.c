/* Copyright 2019. yummyHit. All rights reserved.
 * Get ascii table for convenient
 * It needs when can not connect any network
 * @using: ./ascii_table
 */

#include <ctype.h>
#include <stdio.h>

int main(void) {
	int i = 0, count = 0;

	for(i = 0; i < 128; i++)
		if(isalnum(i)) {
			printf("0x%x:%c    ", i, i);
			count++;
			if(count % 5 == 0)
				printf("\n");
		}
	printf("\n");
	return 0;
}
