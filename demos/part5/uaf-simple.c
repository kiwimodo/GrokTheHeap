#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    char *first;
    char *second;

    first = malloc(9);
    strcpy(first, "hello!!!");
    printf("Malloc'd first: %p\n with data: %s\n\n", first, first);

    free(first);
    printf("Free'd first.\n\n");

    second = malloc(9);
    strcpy(second, "goodbye.");
    printf("Malloc'd second with: %p\n with data: %s\n\n", second, second);    

    printf("Printing first data after free...\n");
    printf("%s\n", first);
}