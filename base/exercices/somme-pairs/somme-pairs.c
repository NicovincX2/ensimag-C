/*
    Enoncé :

    L'objectif de cet exercice est de calculer la somme des 10 premiers entiers
    pairs positifs (0 compris). On utilisera un tableau pour stocker ces
    entiers, et on calculera ainsi la somme de ses éléments.  Le résultat sera
    affiché sur la sortie standard.

    Compétences : 16,66,67
    Difficulté : 1
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    uint8_t tab[] = { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 };
    
    uint8_t somme = 0;
    for (uint8_t i = 0; i < 10; i++) {
        somme += tab[i];
    }

    printf("Valeur attendue: %u.\n", somme);
    
    return EXIT_SUCCESS;
}
