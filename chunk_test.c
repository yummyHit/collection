/* Copyright 2019. yummyHit. All rights reserved.
 * Test file for chunk definition
 * It seems like list and node
 * @using: ./chunk_test
 */

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Chunk {
	int size;
	int start;
	struct Chunk *link;
} Chunk;

void init(int request_size) {
	printf("start: %d\n", 0);
	printf("size: %d\n", request_size);
}

Chunk *create(int data, element v_start, element v_size, Chunk *link) {
	Chunk *new_node = (Chunk *)malloc(sizeof(Chunk));
	element a, b, c;
	element r_start;
	v_start = data;
	v_size -= data;

	new_node->start = v_start;
	new_node->size = v_size;
	new_node->link = link;
	printf("start: %d\n", new_node->start);
	printf("size: %d\n", new_node->size);
	printf("---------------\n");

	return new_node;
}

Chunk *place(Chunk *p, int n) {
	for(int i = 2; i < n; i++)
		p = p->link;

	return p;
}

void* myalloc(Chunk **available, Chunk *new, int pos) {
	Chunk *p = NULL;

	if(*available == NULL) {
		*available = new;
		new->link = NULL;
	} else if(pos == 1) {
		new->link = *available;
		*available = new;
	} else {
		p = place(*available, pos);
		new->link = p->link;
		p->link = new;
	}
}

void myfree(Chunk *p) {
	if(p) {
		memset(p, 0, sizeof(Chunk));
		free(p->link);
		free(p);
	}
}

int main(void) {
	Chunk *a = NULL;
	Chunk *b = NULL;
	Chunk *c = NULL;
	Chunk *init = NULL;
	int request_size = 0;
	int pos = 0;
	int sum_data = 0, data;

	//전체 메모리 크기 입력
	printf("input memory size: ");
	scanf("%d", &request_size);
	getchar();
	const int zero = request_size;

	data = 0;
	init = myalloc(&a, create(sum_data, 0, request_size, NULL), pos++);

	data = 30;
	sum_data += data;
	a = myalloc(&a, create(sum_data, 30, request_size, NULL), pos);

	data = 10;
	sum_data += data;
	b = myalloc(&a, create(sum_data, 10, request_size, NULL), pos);

	data = 10;
	sum_data += data;
	c = myalloc(&a, create(sum_data, 10, request_size, NULL), pos--);

	myfree(a);

	data = 40;
	sum_data += data;
	a = myalloc(&a, create(sum_data, 40, request_size, NULL), pos);

	myfree(a);
	myfree(init);

	return 0;
}
