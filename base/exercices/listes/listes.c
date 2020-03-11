#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

/* Structure de données décrivant un élément d'une liste. */
struct cellule
{
    /* La valeur d'une cellule est un entier. */
    int32_t val;
    /* Pointeur vers la cellule suivant dans la liste. */
    struct cellule *suiv;
};

/*
    Affiche sur la sortie standard les valeurs des cellules de la liste
    pointée par l.
*/
static void afficher(struct cellule *l)
{
    // l est la valeur du pointeur l
    while (l != NULL) {
        printf("%i -> ", l->val); // attribut val du contenu de la mémoire pointée par le pointeur l
        l = l->suiv;
    }
    printf("FIN\n");
}

/*
    Crée une nouvelle cellule contenant la valeur v et l'insère en tête
    de la liste pointée par pl.
*/
static void inserer_tete(struct cellule **pl, uint32_t v)
{
    /* 
    Comme cette fonction modifie la liste (la première cellule),
    la fonction appelante doit passer l'adresse de la liste pour pouvoir
    observer les changements (cf fiche passage de paramètres du kit de
    démarrage). Ainsi pl contient l'adresse de la liste et *pl désigne la
    liste (cad l'adresse de la première cellule).
    */
    // allocation d'une nouvelle cellule, tête de la nouvelle liste
    struct cellule *liste = (struct cellule *)malloc(sizeof(struct cellule));
    assert(liste != NULL);
    liste->val = v; 
    liste->suiv = *pl;
    /* On fait pointer l'argument pl vers la nouvelle liste */
    *pl = liste;
}

/*
    Crée une nouvelle cellule contenant la valeur v et l'insère en queue
    de la liste pointée par pl.
*/
static void inserer_queue(struct cellule **pl, uint32_t v)
{
    /* 
        On place une sentinelle de manière à gérer à l'identique tous les cas
        incluant le cas liste vide. Le champ suiv de notre sentinelle sera la
        liste que l'on voudra retourner.
    */
    struct cellule sentinelle = { -1, *pl }; // sentinelle de tête
    struct cellule *queue = &sentinelle; // queue pointe vers l'adresse de sentinelle
    
    while (queue->suiv != NULL) {
        queue = queue->suiv; // (*queue).suiv contient sentinelle.suivant ie. un pointeur vers la cellule suivant sentinelle
    }
    
    queue->suiv = (struct cellule *)malloc(sizeof(struct cellule));
    assert(queue->suiv != NULL);
    
    queue->suiv->val = v;
    queue->suiv->suiv = NULL;
    
    /* On fait pointer l'argument pl vers la nouvelle liste */
    *pl = sentinelle.suiv;
}

/*
    Supprime de la liste pointée par pl la première occurrence de cellule
    contenant la valeur v.
*/
static void supprimer_premiere_occurrence(struct cellule **pl, int32_t v)
{
    struct cellule sentinelle = { -1, *pl};
    struct cellule *avant_recherchee = &sentinelle;
    
    while (avant_recherchee->suiv != NULL && avant_recherchee->suiv->val != v) {
        avant_recherchee = avant_recherchee->suiv;
    }
    // on a trouve la cellule recherchée dans la liste
    if (avant_recherchee->suiv != NULL) {
        // On rechaine les 2 cellules de la liste entourant l'occurrence et on libère la cellule trouvée.
        struct cellule *style = avant_recherchee->suiv;
        avant_recherchee->suiv = style->suiv;
        free(style);
    }
    *pl = sentinelle.suiv;
}

int main(void)
{
    /*
        Rappel : une liste est définie comme un pointeur vers la première
        cellule.
    */
    struct cellule *liste = NULL; // NULL pointer, pointe vers rien
    for (int32_t i = 6; i < 10; i++) {
        inserer_queue(&liste, i); // adresse mémoire où est stockée le pointeur liste
        afficher(liste); // pointeur (ie. adresse mémoire), NULL si aucune allocation
    }
    for (int32_t i = 5; i > 0; i--) {
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
