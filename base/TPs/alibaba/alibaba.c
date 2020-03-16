#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "alibaba.h"


// Liste doublement chaînée circulaire


struct _cellule {
    uint32_t val;
    struct _cellule *suiv, *prec;
};

/*
    Notre liste aura deux points d'entrée un en tête de liste l'autre en fin de liste.
    Pour éviter de traîner deux pointeurs, nous les mettrons dans une structure.
    Ceci aura pour avantage de n'avoir qu'une seule variable à traiter par liste.
*/
struct _ldc {
    cellule *tete, *queue;
    uint32_t taille;
};

// insere la valeur n en fin (ou début car ciruclaire) de la liste pointee par l
void ldc_insere_fin(ldc **pl, uint32_t n) {
    cellule *queue = (cellule *)malloc(sizeof(cellule));
    assert(queue != NULL);
    queue->val = n;
    if ((*pl)->queue) {
        queue->suiv = (*pl)->tete;
        queue->prec = (*pl)->queue;
        (*pl)->queue->suiv = queue;
    } else {
        queue->suiv = queue;
        queue->prec = queue;
        (*pl)->tete = queue;
    }
    (*pl)->queue = queue;
    ++((*pl)->taille);
}

// affiche le contenu de la liste l
void ldc_affiche(ldc *l) {
    cellule *tete = l->tete;
    uint32_t taille = l->taille;
    printf("Taille : %i \n", taille);
    while (taille != 0) {
        printf("%i -> ", tete->val);
        tete = tete->suiv;
        --taille;
    }
    printf("\n");
}

// supprime l'element e de la liste pointee par pl.
// precondition: *pl non vide, e non null, e dans *pl
void ldc_supprime(ldc **pl, uint32_t e) {
    uint32_t taille = (*pl)->taille;
    cellule *avant_recherchee = (*pl)->tete;
    assert(taille != 0);

    while (avant_recherchee->suiv != NULL && taille != 0 && avant_recherchee->suiv->val != e) {
        avant_recherchee = avant_recherchee->suiv;
        --taille;
    }

    if (avant_recherchee->suiv != NULL) {
        // on a trouve la cellule recherchée dans la liste
        cellule *recherchee = avant_recherchee->suiv;
        avant_recherchee->suiv = recherchee->suiv;
        recherchee->suiv->prec = avant_recherchee;
        if (recherchee == (*pl)->tete) {
            (*pl)->tete = recherchee->suiv;
        }
        if (recherchee == (*pl)->queue) {
            (*pl)->queue = avant_recherchee;
        }
        free(recherchee);
        --((*pl)->taille);
    }

}

// vide la liste pointee par pl, et libere la memoire.
// En sortie, pl == NULL
void ldc_libere(ldc **pl) {
    cellule *current = (*pl)->tete;
    uint32_t taille = (*pl)->taille;
    while (taille != 0) {
        cellule *temp = current;
        current = current->suiv;
        free(temp);
        --taille;
    }
    *pl = NULL;
}

void ldc_init(ldc **pl) {
    if (*pl == NULL) {
        *pl = (ldc *)malloc(sizeof(ldc));
    }
    (*pl)->tete = NULL;
    (*pl)->queue = NULL;
    (*pl)->taille = 0;
}

int main(void) {

#ifdef TESTS
    printf("Entrée dans les tests \n");
    ldc *liste = NULL;
    ldc_init(&liste);
    
    ldc_affiche(liste);
    ldc_insere_fin(&liste, 1);
    ldc_affiche(liste);
    ldc_supprime(&liste, 1);
    ldc_affiche(liste);
    ldc_insere_fin(&liste, 2);
    ldc_affiche(liste);
    ldc_insere_fin(&liste, 3);
    ldc_insere_fin(&liste, 4);
    ldc_insere_fin(&liste, 5);
    ldc_affiche(liste);
    ldc_supprime(&liste, 3);
    ldc_affiche(liste);
    ldc_supprime(&liste, 5);
    ldc_affiche(liste);
    ldc_supprime(&liste, 2);
    ldc_affiche(liste);
    ldc_insere_fin(&liste, 3);
    ldc_insere_fin(&liste, 4);
    ldc_insere_fin(&liste, 5);
    ldc_libere(&liste);
#else
    ldc *voleurs = NULL;
    ldc_init(&voleurs);

    for (uint32_t i = 1; i <= 41; i++) {
        ldc_insere_fin(&voleurs, i);
    }
    printf("Affichage des voleurs \n");
    ldc_affiche(voleurs);

    ldc *perdants = NULL;
    ldc_init(&perdants);
    uint32_t arbitre = 3;

    while (voleurs->taille > 2) {
        ldc_supprime(&voleurs, arbitre);
        ldc_insere_fin(&perdants, arbitre);
        arbitre += 3;
        arbitre %= 41;
    }
    printf("Affichage des voleurs \n");
    ldc_affiche(voleurs);
    printf("Affichage des perdants \n");
    ldc_affiche(perdants);
    ldc_libere(&voleurs);
    ldc_libere(&perdants);

#endif

    return EXIT_SUCCESS;
}
