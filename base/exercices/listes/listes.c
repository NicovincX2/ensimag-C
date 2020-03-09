#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

/* Structure de données décrivant un élément d'une liste. */
struct cellule
{
    /* La valeur d'une cellule est un entier. */
    uint32_t val;
    /* Pointeur vers la cellule suivant dans la liste. */
    struct cellule *suiv;
};

/*
    Affiche sur la sortie standard les valeurs des cellules de la liste
    pointée par l.
*/
static void afficher(struct cellule *l)
{
    /* A implémenter! */
}

/*
    Crée une nouvelle cellule contenant la valeur v et l'insère en tête
    de la liste pointée par pl.
*/
static void inserer_tete(struct cellule **pl, uint32_t v)
{
    /* A implémenter! */
}

/*
    Crée une nouvelle cellule contenant la valeur v et l'insère en queue
    de la liste pointée par pl.
*/
static void inserer_queue(struct cellule **pl, uint32_t v)
{
    /* A implémenter! */
}

/*
    Supprime de la liste pointée par pl la première occurrence de cellule
    contenant la valeur v.
*/
static void supprimer_premiere_occurrence(struct cellule **pl, uint32_t v)
{
    /* A implémenter! */
}

int main(void)
{
    struct cellule *liste = NULL;
    for (uint32_t i = 6; i < 10; i++) {
        inserer_queue(&liste, i);
        afficher(liste);
    }
    for (uint32_t i = 5; i > 0; i--) {
        inserer_tete(&liste, i);
        afficher(liste);
    }

    /*
        Initialisation du générateur de nombres aléatoires
        (nécessaire pour que rand() retourne des valeurs différentes à chaque
        exécution du programme).
    */
    srand(time(NULL));

    while (liste != NULL) {
        supprimer_premiere_occurrence(&liste, rand() % 10);
        afficher(liste);
    }
    return EXIT_SUCCESS;
}
