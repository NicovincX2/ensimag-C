#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/

typedef struct contact {
    struct contact *suivant;
    struct contact *precedent;
    char *cle;
    char *valeur;
} contact;

typedef struct dir_item {
    contact *tete;
    contact *queue;
} dir_item;

/* TOUT DOUX: à compléter */
/* Profitez de cette période sombre pour braver les interdits et rétablir le contact. */
extern contact *contact_create(const char *cle, const char *valeur);
extern dir_item *liste_contacts_create(contact *c);

extern void contact_update(contact *c, const char *valeur);
extern void contact_delete(dir_item *lc, contact *c);
extern void lcontact_add(dir_item *lc, contact *c);

extern void contact_free(contact **c);
extern void lcontact_free(dir_item **lc);

extern int trouver_contact(dir_item *lc, const char *cle);
extern contact *get_contact(dir_item *lc, int indice_recherche);

#endif /* _CONTACT_H_ */
