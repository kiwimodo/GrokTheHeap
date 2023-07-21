#include <stdio.h>
#include <stdlib.h>

void main(void) {
	void *p[7];

	for(int i = 0; i < 7; i++)
		p[i] = malloc(32);
	for(int i = 0; i < 7; i++)
		free(p[i]);
	
	void *a = calloc(1, 32);

	free(a);
	free(a); // Will throw an error.
}
