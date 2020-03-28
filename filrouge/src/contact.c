#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "contact.h"
#include "hash.h"


/*
  Allocation mémoire à la taille d'un contact et enregistrement d'une copie
  des chaines cle et valeur dans cet emplacement mémoire.
  strdup permet de dupliquer une chaîne de caractères (à libérer ensuite)
  On n'altère pas les chaînes originales
*/
contact *contact_create(const char *cle, const char *valeur) {
    // Le contact
    contact *c = malloc(sizeof *c);
    if (c == NULL) {
        return NULL;
    }

    c->cle = strdup(cle);
    c->valeur = strdup(valeur);
    c->suivant = NULL; // TODO: revoir l'initialisation
    c->precedent = NULL;

    return c;
}

dir_item *liste_contacts_create(contact *c) {
    // La liste chaînee de contacts
    dir_item *lc = malloc(sizeof *lc);
    if (lc == NULL) {
        return NULL;
    }
    lc->tete = c;
    lc->queue = c;

    return lc;
}

/*
  Libération de la mémoire
*/
void contact_free(contact **c) {
    free((*c)->cle);
    (*c)->cle = NULL;
    free((*c)->valeur);
    (*c)->valeur = NULL;
    free(*c);
    *c = NULL;
}

void lcontact_free(dir_item **lc) {
    // lc est une liste chaînée
    if ((*lc) != NULL) {
        contact *courant = (*lc)->tete;
        while (courant != NULL) {
            contact *temp = courant;
            courant = courant->suivant;
            contact_free(&temp);
        }
    }
    free(*lc);
    *lc = NULL;
}

void contact_update(contact *c, const char *valeur) {
    free(c->valeur);
    c->valeur = strdup(valeur);
}

void contact_delete(dir_item *lc, contact *c) {
    if (c->suivant) {
        c->precedent->suivant = c->suivant;
        c->suivant->precedent = c->precedent;
    } else {
        // le contact est en tête
        lc->tete = c->suivant;
        lc->queue = c->precedent;
    }
    contact_free(&c);
}

void lcontact_add(dir_item *lc, contact *c) {
    if (lc->queue == NULL) {
        lc->tete = c;
        lc->queue = c;
    } else {
        lc->queue->suivant = c;
        lc->queue->precedent = lc->queue;
        lc->queue = c;
    }
}

/*
  Renvoie l'indice de la liste chaînee contenant le contact
  -1 si la clef n'est pas présente
*/
int trouver_contact(dir_item *lc, const char *cle) {
    int return_value = 0;
    contact *temp = lc->tete;
    while (temp != NULL) {
        if (strcmp(temp->cle, cle) == 0) {
            return return_value;
        }
        temp = temp->suivant;
        return_value++;
    }
    return -1;
}

/*
  renvoie le contact à l'indice indice_recherche
*/
contact *get_contact(dir_item *lc, int indice_recherche) {
    int indice = 0;
    contact *temp = lc->tete;
    while (indice != indice_recherche) {
        temp = temp->suivant;
        indice++;
    }
    return temp;
}
