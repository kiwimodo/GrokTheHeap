#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	setbuf(stdout, NULL);

	void *ptrs[8];
	for (int i=0; i<8; i++) {
		ptrs[i] = malloc(8);
	}
	for (int i=0; i<7; i++) {
		free(ptrs[i]);
	}

	int *a = calloc(1, 8);
	int *b = calloc(1, 8);
	int *c = calloc(1, 8);

	printf("a: %p\n", a);
	printf("b: %p\n", b);
	printf("c: %p\n", c);

	free(a);

	// free(a);

	free(b);

	free(a);

	a = calloc(1, 8);
	b = calloc(1, 8);
	c = calloc(1, 8);
	
	printf("a: %p\n", a);
	printf("b: %p\n", b);
	printf("c: %p\n", c);

	assert(a == c);
}
