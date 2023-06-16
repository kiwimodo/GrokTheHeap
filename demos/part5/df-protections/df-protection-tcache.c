#include <stdio.h>
#include <stdlib.h>

void main(void) {
	void *p = malloc(32);

	free(p);
	free(p);
}
