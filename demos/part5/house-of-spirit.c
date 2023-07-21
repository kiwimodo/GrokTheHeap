#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	setbuf(stdout, NULL);

	void *chunks[7];
	for(int i=0; i<7; i++) {
		chunks[i] = malloc(0x30);
	}
	for(int i=0; i<7; i++) {
		free(chunks[i]);
	}

	long fake_chunks[10] __attribute__ ((aligned (0x10)));
	fake_chunks[1] = 0x40;
	fake_chunks[9] = 0x1234;

	void *victim = &fake_chunks[2];
	free(victim);

	void *allocated = calloc(1, 0x30);

	assert(allocated == victim);
}