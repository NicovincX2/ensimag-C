#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    char saisie[3];
    uint16_t value;
    printf("Je lis dans vos pensees.\nPensez a un chiffre entre 0 et 2.\nTapez le au clavier, je ne regarde pas !\n");
    fgets(saisie, 3, stdin);
    value = atoi(saisie);
    /*
        value = 0 assigne la valeur 0 à la variable value.
        value = 0 renvoie aussi la valeur assignée : 0.
        Le test finalement effectué est donc équivalent à if (0).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (0) est donc toujours FAUX.
        Les instructions de ce if ne sont donc jamais exécutées même si
        la valeur 0 est saisie au clavier.

        Dans un test, il faut utiliser l'opérateur de comparaison ==
        et non l'opérateur d'assignation =.
    */

    if (value = 0) {
        printf("Vous avez saisi la valeur 0\n");
    }
    /*
        value = 1 assigne la valeur 1 à la variable value.
        value = 1 renvoie aussi la valeur assignée : 1.
        Le test finalement effectué est donc équivalent à if (1).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (1) est donc toujours VRAI.
        Les instructions de ce if sont toujours exécutées quelque soit
        la valeur saisie au clavier.
    */

    if (value = 1) {
        printf("Vous avez saisi la valeur 1\n");
    }
    /*
        value = 2 assigne la valeur 2 à la variable value.
        value = 2 renvoie aussi la valeur assignée : 2.
        Le test finalement effectué est donc équivalent à if (2).
        if évalue une expression à VRAI quand elle est différente de 0.
        Dans ce cas, le test if (2) est donc toujours VRAI.
        Les instructions de ce if sont toujours exécutées quelque soit
        la valeur saisie au clavier.
    */

    if (value = 2) {
        printf("Vous avez saisi la valeur 2\n");
    }
    return EXIT_SUCCESS;
}
