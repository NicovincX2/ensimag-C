/*
    Enoncé :

    L'objectif de cet exercice est de calculer la somme des 5000
    premiers entiers impairs strictement positifs. On utilisera un
    tableau pour stocker ces entiers, et on calculera ainsi la somme de
    ses éléments. Vous devrez déclarer une constante TAILLE_TAB
    représentant la taille du tableau.

    On vous demande ici d'implémenter deux fonctions dans ce même
    fichier, en plus de la fonction main :

        void init_tab(uint32_t tab[], size_t length);

    qui initialise le tableau passé en paramètre avec les valeurs des
    "length" premiers entiers impairs strictement positifs.

        uint32_t somme_tab(uint32_t tab[], size_t length);

    qui retourne la somme des éléments du tableau "tab" passé en
    paramètre.

    Le résultat sera affiché sur la sortie standard.

    Compétences : 16,23,66,67,70,74
    Difficulté : 1
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void init_tab(uint32_t tab[], size_t length)
{
    for (uint32_t i = 0; i < length; i++) {
        tab[i] = 2 * i + 1;
    }
}

static uint32_t somme_tab(uint32_t tab[], size_t length)
{
    uint32_t somme = 0;
    for (uint32_t i = 0; i < length; i++) {
        somme += tab[i];
    }
    return somme;
}

int main(void)
{
    const uint16_t TAILLE_TAB = 5000;
    uint32_t somme = 0;
    uint32_t tab[TAILLE_TAB];
    
    init_tab(tab, TAILLE_TAB);
    somme = somme_tab(tab, TAILLE_TAB);
    
    printf("Somme des 5000 premiers entiers impairs strictement positifs = %u.\n", somme);

    return EXIT_SUCCESS;
}
