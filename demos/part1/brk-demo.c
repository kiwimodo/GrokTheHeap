#include <stdio.h>
#include <unistd.h>

void main(void)
{
	void *new_brk, *old_brk = NULL;

	printf("Current PID: %d\n", getpid());
	
	// Get current program break location
	old_brk = sbrk(0);
	printf("Pre-brk program break location: %p\n", old_brk);
	getchar();

	// Increase program break location
	new_brk = old_brk + 4096;
	brk(new_brk);
	new_brk = sbrk(0);
	printf("Post-brk program break location: %p\n", new_brk);
	getchar();

	// Restore program break location
	brk(old_brk);
	new_brk = sbrk(0);
	printf("Restored program break location: %p\n", new_brk);
	getchar();
}

