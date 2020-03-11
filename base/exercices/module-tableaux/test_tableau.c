#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "tableau.h"

int main(void)
{
    printf("nb d'elements?\n");
    char tampon[11];
    fgets(tampon, 11, stdin);
    uint32_t n = atoi(tampon);
    /* Définition d'un tableau de dimension variable*/
    int32_t tab[n];

#ifdef INTERACTIF
    /*
        On peut utiliser le préprocessur pour compiler le code avec cette
        version en ajoutant -DINTERACTIF comme option dans la ligne de
        compilation.
    */
    init_interactive(tab, n);
#else
    srand(time(NULL)); // initialisation du générateur pseudo-aléatoire
    init_aleatoire(tab, n);
#endif

    affiche(tab, n);
    tri_insertion(tab, n);
    affiche(tab, n);
    return EXIT_SUCCESS;
}
