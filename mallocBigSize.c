/* Copyright 2019. yummyHit. All rights reserved.
 * How much use heap size with memory allocation
 * can't believe ulimit's size, this source can help that solution
 * @using: ./mallocBigSize
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void *malloc_wrap(size_t size) {
	void *p = malloc(size);
	if(p)
		printf("Allocated %zu bytes from %p to %p\n", size, p, p + size);
	else
		printf("Failed to allocated %zu bytes\n", size);
	return p;
}

int main() {
	size_t step = 0x100000;
	size_t size = step;
	size_t best = 0;
	while(step > 0) {
		void *p = malloc_wrap(size);
		if (p) {
			free(p);
			best = size;
		} else
			step /= 0x10;
		size += step;
	}
	printf("Best size is ...\n");
	void *p = malloc_wrap(best);
	if(p)
		return 0;
	else
		return 1;
}
