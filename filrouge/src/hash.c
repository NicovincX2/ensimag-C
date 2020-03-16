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

#ifdef UNIT_TEST
int main(void) {
    unsigned long h;
    const unsigned char *test = (const unsigned char *)"Le module hash devra contenir l'implémentation de cette fonction de hachage. Bien qu'elle ne soit utilisée que par le module directory, on décide ici de placer cette fonction dans un module à part, ce qui permettrait d'étendre votre projet en ajoutant d'autres fonctions de hachage pour évaluer leur impact sur la façon dont se remplit votre table de hachage. Les fonctions de hachage sont aussi indépendantes du reste du projet, et peuvent de fait être testées de manière autonome.";
    
    h = hash(test);
    printf("Hash de notre string: '%li'\n", h);
    
    return EXIT_SUCCESS;
}
#endif