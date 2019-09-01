/* Copyright 2019. yummyHit. All rights reserved.
 * check current std libc version for compile environment
 * using gcc_version.sh, not this
 */

#include <stdio.h>

int main(void) {
#ifdef __STDC_VERSION__
	printf("__STDC_VERSION__ = %ld \n", __STDC_VERSION__);
#endif
#ifdef __STRICT_ANSI__
	puts("__STRICT_ANSI__");
#endif
	return 0;
}
