#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "prime.h"
#include "contact.h"
#include "hash.h"

#define HT_CAPACITE_BASE_INITIALE 50

struct _contact {
    char *cle;
    char *valeur;
    struct _contact *suivant;
    struct _contact *precedent;
};

struct _hash_table_item {
    contact *tete;
    contact *queue;
};

struct _hash_table {
    size_t capacite_base;
    size_t capacite; // nombre de contacts qu'il est possible de stocker
    size_t taille; // nombre de listes chaînees pour le redimensionnement
    hash_table_item **contacts; // tableau de pointeurs sur les contacts
};

static void resize_up(hash_table *ht); // pour la fonction inserer_contact

/*
  Allocation mémoire à la taille d'un contact et enregistrement d'une copie
  des chaines cle et valeur dans cet emplacement mémoire.
  strdup permet de dupliquer une chaîne de caractères (à libérer ensuite)
  On n'altère pas les chaînes originales
*/

char *strdup (const char *str) {
    size_t len = strlen(str) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, str, len);
}

static contact *creer_contact(const char *cle, const char *valeur) {
    // Le contact
    contact *c = malloc(sizeof(contact));
    assert(c != NULL);

    c->cle = strdup(cle);
    c->valeur = strdup(valeur);
    c->suivant = NULL; // TODO: revoir l'initialisation
    c->precedent = NULL;

    return c;
}

static hash_table_item *creer_liste_contact(contact *c) {
    // La liste chaînee de contacts
    hash_table_item *lc = malloc(sizeof(hash_table_item));
    assert(lc != NULL);
    lc->tete = c;
    lc->queue = c;

    return lc;
}

/*
  Initialise une nouvelle table de hachage avec une valeur size qui correspond 
  au nombre d'éléments que nous pouvons stocker
  calloc, qui remplit la mémoire allouée avec les octets NULL
  On n'altère pas les chaînes originales
*/
static hash_table *creer_dynamic_hash_table(const size_t capacite_base) {
    hash_table *ht = malloc(sizeof(hash_table));
    assert(ht != NULL);
    ht->capacite_base = capacite_base;
    
    ht->capacite = next_prime(ht->capacite_base);
    
    ht->taille = 0;
    ht->contacts = calloc(ht->capacite, sizeof(hash_table_item *));
    
    return ht;
}

static hash_table *creer_hash_table(void) {
    return creer_dynamic_hash_table(HT_CAPACITE_BASE_INITIALE);
}

/*
  Libération de la mémoire
*/
static void libere_contact(contact *c) {
    free(c->cle);
    free(c->valeur);
    free(c);
}

static void libere_lcontact(hash_table_item *lc) {
    // lc est une liste chaînée
    if (lc != NULL) {
        contact *courant = lc->tete;
        while (courant != NULL) {
            contact *temp = courant;
            courant = courant->suivant;
            libere_contact(temp);
        }
    }
    free(lc);
}

static void libere_hash_table(hash_table *ht) {
    for (size_t i = 0; i < ht->capacite; i++) {
        hash_table_item *lc = ht->contacts[i];
        libere_lcontact(lc);
    }
    free(ht);
}

/*
  Renvoie l'indice de la liste chaînee contenant le contact
  -1 si la clef n'est pas présente
*/
static int trouver_contact(hash_table_item *lc, const char *cle)
{
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
static contact *get_contact(hash_table_item *lc, int indice_recherche)
{
    int indice = 0;
    contact *temp = lc->tete;
    while (indice != indice_recherche) {
        temp = temp->suivant;
        indice++;
    }
    return temp;
}

/*
  On récupère le hash
*/
static unsigned long get_hash(const char *str) {
    unsigned long ht_hash = hash((const unsigned char *)str);
    return ht_hash;
}

/*
  Méthode de la table de hachage
  Pour l'insertion on calcule l'index associé à la clef.
  Traitement des collisions par méthode de chaînage.
*/
void inserer_contact(hash_table *ht, const char *cle, const char *valeur) {
    const int load = (int)(ht->taille * 100 / ht->capacite);
    if (load > 75) {
        resize_up(ht);
    }
    
    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    // Liste chaînee si présente à l'indice donné
    hash_table_item *lcontact_courant = ht->contacts[indice];

    // Création du contact à insérer dans la table de hashage
    contact *c = creer_contact(cle, valeur);
    hash_table_item *lc = creer_liste_contact(c);

    if (lcontact_courant == NULL) {
        // pas de contact à l'indice donné
        // fait dans creer_liste_contact(c)
        // lc->tete = c;
        // lc->queue = c;
        ht->contacts[indice] = lc;
        ++(ht->taille);
    } else {
        // une liste chaînee est presente
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche == -1) {
            // clef non trouvee, on l'ajoute à la fin
            if ((ht->contacts[indice])->queue == NULL) {
                (ht->contacts[indice])->tete = c;
                (ht->contacts[indice])->queue = c;
            } else {
                (ht->contacts[indice])->queue->suivant = c;
                (ht->contacts[indice])->queue->precedent = (ht->contacts[indice])->queue;
                (ht->contacts[indice])->queue = c;
            }
            // ++(ht->taille); // commenté car taille n'est pas le nombre de cellules
        } else {
            // clef deja presente, on supprime le contact et on le recrè
            // car pas de const dans struct et on a const char *valeur
            contact *recherchee = get_contact(lcontact_courant, indice_recherche);
            // ce que l'on pourrait faire directement sans prbl des const
            // recherchee->valeur = valeur;
            // ce que l'on fait plutot : remplacer recherchee par c
            if (recherchee->suivant) {
                recherchee->precedent->suivant = c;
                recherchee->suivant->precedent = c;
            } else {
                // le contact est en tête
                (ht->contacts[indice])->tete = c;
                (ht->contacts[indice])->queue = c;
            }
            libere_contact(recherchee);
        }
    }
}

static void resize_hash_table(hash_table *ht, const size_t capacite_base) {
    if (capacite_base < HT_CAPACITE_BASE_INITIALE) {
        // on ne doit pas réduire la taille en dessous de son minimum
        return;
    }
    hash_table *new_ht = creer_dynamic_hash_table(capacite_base);
    for (size_t i = 0; i < ht->taille; i++) {
        hash_table_item *lc = ht->contacts[i];
        if (lc != NULL) {
            contact *courant = lc->tete;
            while (courant != NULL) {
                inserer_contact(new_ht, courant->cle, courant->valeur);
                courant = courant->suivant;
            }
        }
    }
    
    ht->capacite_base = new_ht->capacite_base;
    ht->taille = new_ht->taille;
    
    // delete new_ht
    const size_t capacite_temp = ht->capacite;
    ht->capacite = new_ht->capacite;
    new_ht->capacite = capacite_temp;
    
    hash_table_item **contacts_temp = ht->contacts;
    ht->contacts = new_ht->contacts;
    new_ht->contacts = contacts_temp;
    
    libere_hash_table(new_ht);
}

static void resize_up(hash_table *ht) {
    const size_t new_capacite = ht->capacite_base * 2;
    resize_hash_table(ht, new_capacite);
}

static void resize_down(hash_table *ht) {
    const size_t new_capacite = ht->capacite_base / 2;
    resize_hash_table(ht, new_capacite);
}

/*
  Méthode de la table de hachage
  On renvoie NULL si aucune valeur n'a été trouvée
*/
char *rechercher_hash_table(hash_table *ht, const char *cle) {
    
    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    hash_table_item *lcontact_courant = ht->contacts[indice];
    if (lcontact_courant != NULL) {
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche != -1) {
            return get_contact(lcontact_courant, indice_recherche)->valeur;
        }
    }
    return NULL;
}

/*
  Méthode de la table de hachage
  Si l'élément fait partie d'une chaîne de collision (ie. liste chaînee) on
  peut facilement le supprimer avec la méthode de la liste chainee
  Sans liste chaînee, l'enlever de la table va rompre cette chaîne et rendra 
  impossible la recherche d'éléments. On le marquerai alors simplement comme
  supprimé.
  static contact HT_DELETED_CONTACT = {NULL, NULL, NULL, NULL};
*/
void supprimer_hash_table(hash_table *ht, const char *cle) {
    const int load = (int)(ht->taille * 100 / ht->capacite);
    if (load < 25) {
        resize_down(ht);
    }
    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    hash_table_item *lcontact_courant = ht->contacts[indice];
    if (lcontact_courant != NULL) {
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche != -1) {
            // clef deja presente, on supprime le contact
            contact *recherchee = get_contact(lcontact_courant, indice_recherche);
            if (recherchee->suivant) {
                recherchee->precedent->suivant = recherchee->suivant;
                recherchee->suivant->precedent = recherchee->precedent;
            } else {
                // le contact est en tête
                (ht->contacts[indice])->tete = recherchee->suivant;
                (ht->contacts[indice])->queue = recherchee->precedent;
            }
            libere_contact(recherchee);
            // on décrémente le nombre de listes chainees si la liste chainee est vide
            if ((ht->contacts[indice])->tete == NULL) {
                (ht->taille)--;
            }
        }
    }
}


void afficher(hash_table *ht) {
    static unsigned int numero_affichage = 0;
    numero_affichage++;
    printf("Affichage n°%u\n", numero_affichage);
    for (size_t i = 0; i < ht->capacite; i++) {
        hash_table_item *lc = ht->contacts[i];
        if (lc != NULL) {
            contact *courant = lc->tete;
            while (courant != NULL) {
                printf("k : %s, v : %s\n", courant->cle, courant->valeur);
                courant = courant->suivant;
            }
        }
    }
}

int main(void) {
    hash_table *ht = creer_hash_table();
    afficher(ht);

    inserer_contact(ht, "bonjour", "Nicolas");
    inserer_contact(ht, "hello", "Nicolas");
    afficher(ht);

    supprimer_hash_table(ht, "bonjour");
    afficher(ht);

    inserer_contact(ht, "bonjour", "Samy");
    inserer_contact(ht, "bonjour", "Dominique");
    afficher(ht);

    inserer_contact(ht, "bonjour", "Nicolas");
    supprimer_hash_table(ht, "hello");
    afficher(ht);
    libere_hash_table(ht);
    
    hash_table *ht1 = creer_hash_table();
    printf("%d, %d, %d\n", (int)(ht1->capacite_base), (int)(ht1->capacite), (int)(ht1->taille));
    char buf[10];
    char *value;
    const int32_t nombre_insertions = 10000;

    for (int32_t i = 0; i < nombre_insertions; i++) {
        sprintf(buf, "%i", i);
        value = strdup(buf);
        inserer_contact(ht1, value, value);
    }
    // afficher(ht1);
    printf("%d, %d, %d\n", (int)(ht1->capacite_base), (int)(ht1->capacite), (int)(ht1->taille));
    libere_hash_table(ht1);

    return EXIT_SUCCESS;
}
