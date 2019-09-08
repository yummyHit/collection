/* Copyright 2019. yummyHit. All rights reserved.
 * byte swap without new variable
 * it use only exclusive or
 * compile with -D option for CHAR, STRING, DECIMAL(-D is pre-define)
 * @compile: gcc -o byte_swap byte_swap.c -DSTRING
 * @using: ./byte_swap
 */

#include <stdio.h>

int main() {
#if CHAR
	char a = 'a', b = 'Z';
	printf("a: %c, b: %c\n", a, b);
#elif STRING
#include <string.h>
	char a[] = "hello im yummyHit", b[] = "happy hacking";
	printf("a: %s, b: %s\n", a, b);
#else
	unsigned a = 123, b = 999;
	printf("a: %u, b: %u\n", a, b);
#endif

#if STRING
	for(unsigned i = 0; i < (strlen(a) < strlen(b) ? strlen(a) : strlen(b)); i++) {
		a[i] ^= b[i];
		b[i] ^= a[i];
		a[i] ^= b[i];
	}
#else
	a ^= b;
	b ^= a;
	a ^= b;
#endif

#if CHAR
	printf("a: %c, b: %c\n", a, b);
#elif STRING
	printf("a: %s, b: %s\n", a, b);
#else
	printf("a: %u, b: %u\n", a, b);
#endif
	return 0;
}
