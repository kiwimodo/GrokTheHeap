#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

void main(void) {

	printf("Current PID: %d\n", getpid());
	printf("About to call mmap\n");
	getchar();

	void *addr = NULL;
	addr = mmap(NULL, (size_t)132*1024, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	if (addr == MAP_FAILED) {
		printf("mmap failed\n");
		return;
	}
	
	printf("Successfully called mmap\n");
	printf("About to call munmap\n");
	getchar();

	if (munmap(addr, (size_t)132*1024) == -1) {
		printf("munmap failed\n");
		return;
	}

	printf("Successfully called munmap\n");
	getchar();
	return;
}


