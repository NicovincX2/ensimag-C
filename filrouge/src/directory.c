#include <stdlib.h>
#include <stdio.h>

#include <directory.h>
#include <contact.h>
#include <hash.h>
#include <utils.h>

#define HT_CAPACITE_BASE_INITIALE 50
#define HT_CAPACITE_MAX 1000000


char *dir_insert(dir *ht, const char *cle, const char *valeur); // pour la fonction resize_dir


/*
  Initialise une nouvelle table de hachage avec une valeur size qui correspond
  au nombre d'éléments que nous pouvons stocker
  calloc, qui remplit la mémoire allouée avec les octets NULL
  On n'altère pas les chaînes originales
*/
static dir *dir_create_dynamic(const size_t capacite_base) {
    dir *ht = malloc(sizeof *ht);
    if (ht == NULL) {
        return NULL;
    }
    // check for capacite_base upper bound
    if (capacite_base > HT_CAPACITE_MAX) {
        ht->capacite_base = HT_CAPACITE_MAX;
    } else {
        ht->capacite_base = capacite_base;
    }

    ht->capacite = next_prime(ht->capacite_base);

    ht->taille = 0;
    ht->contacts = calloc(ht->capacite, sizeof(dir_item *));
    if (ht->contacts == NULL) {
        free(ht); // dealing with memory leaks if calloc fails
        return NULL;
    }
    return ht;
}

dir *dir_create(const size_t capacite_base) {
    return dir_create_dynamic(capacite_base);
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/

void dir_free(dir *ht) {
    for (size_t i = 0; i < ht->capacite; i++) {
        lcontact_free(&(ht->contacts[i]));
    }
    free(ht->contacts);
    free(ht);
}

static void resize_dir(dir *ht, const size_t capacite_base) {
    if (capacite_base < HT_CAPACITE_BASE_INITIALE) {
        // on ne doit pas réduire la taille en dessous de son minimum
        return;
    }
    dir *new_ht = dir_create_dynamic(capacite_base);
    if (new_ht == NULL)
        return;
    for (size_t i = 0; i < ht->taille; i++) {
        dir_item *lc = ht->contacts[i];
        if (lc != NULL) {
            contact *courant = lc->tete;
            while (courant != NULL) {
                dir_insert(new_ht, courant->cle, courant->valeur);
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

    dir_item **contacts_temp = ht->contacts;
    ht->contacts = new_ht->contacts;
    new_ht->contacts = contacts_temp;

    dir_free(new_ht);
}

static void resize_up(dir *ht) {
    const size_t new_capacite = ht->capacite_base * 2;
    resize_dir(ht, new_capacite);
}

static void resize_down(dir *ht) {
    const size_t new_capacite = ht->capacite_base / 2;
    resize_dir(ht, new_capacite);
}

/*
  On récupère le hash
*/
static unsigned long get_hash(const char *str) {
    unsigned long ht_hash = hash((const unsigned char *)str);
    return ht_hash;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
  On détecte une erreur d'allocation en retournant -1
  Pour l'insertion on calcule l'index associé à la clef.
  Traitement des collisions par méthode de chaînage.
*/
char *dir_insert(dir *ht, const char *cle, const char *valeur) {
    const int load = (int)(ht->taille * 100 / ht->capacite);
    if (load > 75) {
        resize_up(ht);
    }

    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    // Liste chaînee si présente à l'indice donné
    dir_item *lcontact_courant = ht->contacts[indice];

    if (lcontact_courant == NULL) {
        // pas de contact à l'indice donné
        // Création du contact à insérer dans la table de hashage
        contact *c = contact_create(cle, valeur);
        // malloc issue
        if (c == NULL) {
            return NULL;
        }
        // fait dans liste_contacts_create(c)
        // lc->tete = c;
        // lc->queue = c;
        dir_item *lc = liste_contacts_create(c);
        if (lc == NULL) {
            contact_free(&c);
            return NULL;
        }
        ht->contacts[indice] = lc;
        ++(ht->taille);
        return NULL;
    } else {
        // une liste chaînee est presente
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche == -1) {
            // Création du contact à insérer dans la table de hashage
            contact *c = contact_create(cle, valeur);
            if (c == NULL) {
                return NULL;
            }
            // clef non trouvee, on l'ajoute à la fin
            lcontact_add(ht->contacts[indice], c);
            // ++(ht->taille); // commenté car taille n'est pas le nombre de cellules
            return NULL;
        } else {
            // clef deja presente
            contact *recherchee = get_contact(lcontact_courant, indice_recherche);
            printf("Valeur remplacée : %s\n", recherchee->valeur);
            // ce que l'on pourrait faire directement sans prbl des const
            // recherchee->valeur = valeur;
            char *numero = strdup(recherchee->valeur);
            contact_update(recherchee, valeur);

            return numero;
        }
    }
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact ne correspond, retourne NULL.
  All string literals are allocated at compile time. They already reside in a read-only section of the program memory when your program is started; they aren't allocated in runtime. You can regard them as constant character arrays. And like any const variable, they remain valid throughout the whole execution of the program.
*/
const char *dir_lookup_num(dir *ht, const char *cle) {

    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    dir_item *lcontact_courant = ht->contacts[indice];
    if (lcontact_courant != NULL) {
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche != -1) {
            return (const char *)(get_contact(lcontact_courant, indice_recherche)->valeur);
        }
    }
    return NULL;
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
  Si l'élément fait partie d'une chaîne de collision (ie. liste chaînee) on
  peut facilement le supprimer avec la méthode de la liste chainee
  Sans liste chaînee, l'enlever de la table va rompre cette chaîne et rendra
  impossible la recherche d'éléments. On le marquerai alors simplement comme
  supprimé.
  static contact HT_DELETED_CONTACT = {NULL, NULL, NULL, NULL};
*/
void dir_delete(dir *ht, const char *cle) {
    const int load = (int)(ht->taille * 100 / ht->capacite);
    if (load < 25) {
        resize_down(ht);
    }
    int32_t indice = (int32_t)(get_hash(cle) % ht->capacite);
    dir_item *lcontact_courant = ht->contacts[indice];
    if (lcontact_courant != NULL) {
        int indice_recherche = trouver_contact(lcontact_courant, cle);
        if (indice_recherche != -1) {
            // clef deja presente, on supprime le contact
            contact *recherchee = get_contact(lcontact_courant, indice_recherche);
            contact_delete(ht->contacts[indice], recherchee);
            // on décrémente le nombre de listes chainees si la liste chainee est vide
            if ((ht->contacts[indice])->tete == NULL) {
                (ht->taille)--;
            }
        }
    }
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(dir *ht) {
    static unsigned int numero_affichage = 0;
    numero_affichage++;
    printf("Affichage n°%u\n", numero_affichage);
    printf("%d, %d, %d\n", (int)(ht->capacite_base), (int)(ht->capacite), (int)(ht->taille));
    for (size_t i = 0; i < ht->capacite; i++) {
        dir_item *lc = ht->contacts[i];
        if (lc != NULL) {
            contact *courant = lc->tete;
            while (courant != NULL) {
                printf("k : %s, v : %s, indice : %i\n", courant->cle, courant->valeur, (int)i);
                courant = courant->suivant;
            }
        }
    }
}

#ifdef UNIT_TEST
int main(void) {
    dir *ht = dir_create(HT_CAPACITE_BASE_INITIALE);
    dir_print(ht);

    dir_insert(ht, "bonjour", "Nicolas");
    dir_insert(ht, "hello", "Nicolas");
    dir_print(ht);

    dir_delete(ht, "bonjour");
    const char *num = dir_lookup_num(ht, "hello");
    dir_print(ht);
    if (num != NULL) {
        printf("Lookup pour 'hello' : %s\n", num);
    }

    dir_insert(ht, "bonjour", "Samy");
    char *valeur1 = dir_insert(ht, "bonjour", "Dominique");
    printf("%s\n", valeur1);
    free(valeur1);
    dir_print(ht);

    char *valeur2 = dir_insert(ht, "bonjour", "Nicolas");
    printf("%s\n", valeur2);
    free(valeur2);
    dir_delete(ht, "hello");
    dir_print(ht);
    dir_free(ht);

    dir *ht1 = dir_create(HT_CAPACITE_BASE_INITIALE);
    dir_print(ht1);

    char buf[10];
    char *value;
    const int32_t nombre_insertions = 10000;

    for (int32_t i = 0; i < nombre_insertions; i++) {
        sprintf(buf, "%i", i);
        value = strdup(buf);
        char *valeur3 = dir_insert(ht1, value, value);
        if (valeur3 != NULL) {
            free(valeur3);
            valeur3 = NULL;
        }
        free(value);
        value = NULL;
    }
    // dir_print(ht1);
    printf("%d, %d, %d\n", (int)(ht1->capacite_base), (int)(ht1->capacite), (int)(ht1->taille));
    dir_free(ht1);

    return EXIT_SUCCESS;
}
#endif