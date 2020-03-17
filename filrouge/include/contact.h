#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
typedef struct _contact contact; // item de la table de hashage
typedef struct _hash_table_item hash_table_item;
typedef struct _hash_table hash_table;

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */
extern void inserer_contact(hash_table *ht, const char *cle, const char *valeur);
extern char *rechercher_hash_table(hash_table *ht, const char *cle);
extern void supprimer_hash_table(hash_table *ht, const char *cle);

#endif /* _CONTACT_H_ */
