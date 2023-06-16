#include <stdio.h>
#include <stdlib.h>

void main(void) {
	void *a = malloc(5000);
	void *b = malloc(5000);
	void *c = malloc(5000);
	void *d = malloc(5000);

	free(a);
	free(b);
	free(c);
	free(d);
	free(b);
}
