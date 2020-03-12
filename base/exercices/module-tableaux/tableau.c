/* L'énoncé de l'exercice se trouve dans le fichier test_tableau.c.  */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "tableau.h"

void affiche(int32_t tab[], uint32_t taille)
{
    for (uint32_t i = 0; i < taille; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void init_interactive(int32_t tab[], uint32_t taille)
{
    char tampon[11]; // buffer de taille 10
    printf("Entrer %d valeurs entieres\n", taille);
    for (uint32_t i = 0; i < taille; i++) {
        tab[i] = atoi(fgets(tampon, 11, stdin));
    }
}

void init_aleatoire(int32_t tab[], uint32_t taille)
{
    for (uint32_t i = 0; i < taille; i++) {
        tab[i] = (rand() % 100) - 50; // on veut des nombres entre -50 et 50
    }
}

void tri_insertion(int32_t tab[], uint32_t taille)
{
    /*
        Si taille <= 1, le tableau est deja trié.
        Sinon, on parcourt du 2eme au dernier élément.
    */
    for (uint32_t i = 1; i < taille; i++) {
        // tableau trié de 0 à i - 1
        int32_t tmp = tab[i];
        int32_t j = i - 1;

        while (j >= 0 && tab[j] > tmp) {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = tmp;
    }
}
