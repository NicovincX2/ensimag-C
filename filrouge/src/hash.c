#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

unsigned long hash(const unsigned char *str)
{
    unsigned long hash = 5381;
    unsigned int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

int main(void) {
    unsigned long h;
    const unsigned char *test = (const unsigned char *)"test";
    
    h = hash(test);
    printf("Hash de 'test': '%li'\n", h);
    
    return EXIT_SUCCESS;
}