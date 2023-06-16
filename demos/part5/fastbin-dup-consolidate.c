#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void main() {
	void *ptr[7];

	for(int i = 0; i < 7; i++)
		ptr[i] = malloc(0x40);
	for(int i = 0; i < 7; i++)
		free(ptr[i]);

	void* p1 = calloc(1,0x40);
  	free(p1); // Inserts into fastbin

  	void* p3_target = malloc(0x400); // Trigger fastbin consolidation
	assert(p1 == p3_target);

	free(p1); // Vuln inserts our target into tcache

	void *p4 = malloc(0x400);
	assert(p4 == p3_target);

	printf("p3_target=%p, p4=%p\n\n",p3_target, p4);
}