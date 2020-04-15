#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <stdint.h>
#include <stdio.h>

#include "contact.h"

/*
  Structure de données représentant un annuaire.
  Son contenu est détaillé dans directory.c.
*/
typedef struct _dir {
    size_t capacite_base;
    size_t capacite; // nombre de contacts qu'il est possible de stocker
    size_t taille; // nombre de listes chaînees pour le redimensionnement
    dir_item **contacts; // tableau de pointeurs sur les contacts
} dir;


/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
extern dir *dir_create(const size_t capacite_base);


/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
extern char *dir_insert(dir *ht, const char *cle, const char *valeur);

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun
  contact ne correspond, retourne NULL.
*/
extern const char *dir_lookup_num(dir *ht, const char *cle);

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
extern void dir_delete(dir *ht, const char *cle);

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
extern void dir_free(dir *ht);

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
extern void dir_print(dir *ht);

#endif /* _DIRECTORY_H_ */
