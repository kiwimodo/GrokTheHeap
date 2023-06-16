#include <stdio.h>
#include <stdlib.h>

void main(void) {
	setbuf(stdout, NULL);

	int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
	int *c = NULL;

	printf("a: %p\n", a);
	printf("b: %p\n", b);
	printf("c: %p\n\n", c);

	// Fill up the tcache
	void *p[8];
	for(int i = 0; i < 8; i++)
		p[i] = malloc(sizeof(int));

	for(int i = 0; i < 7; i++)
		free(p[i]);

	// Add to the fastbin	
	free(a);
	free(b);
	free(a); // Vuln

	// Pull from the tcache
	for(int i = 0; i < 7; i++)
                p[i] = malloc(sizeof(int));
	
	a = malloc(sizeof(int));
	b = malloc(sizeof(int));
	c = malloc(sizeof(int));

	printf("a: %p\n", a);
	printf("b: %p\n", b);
	printf("c: %p\n", c);
}
