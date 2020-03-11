#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum jour
{
    lundi = 1,
    mardi,
    mercredi,
    jeudi,
    vendredi,
    samedi,
    dimanche
};

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier. */
    int32_t nombre = atoi(argv[1]);
    
    switch(nombre) {
        case lundi:
        case mardi:
        case mercredi:
        case jeudi:
        case vendredi:
            /* Notez l'enchainement de constructions 'case' ici: cela
             * signifie qu'on effectue la même opération si la valeur de
             * 'nombre' est égale à lundi, mardi, mercredi, jeudi ou
             * vendredi. */
            printf("Le nombre entré correspond à un jour de semaine.\n");
            /* break permet de sortir du switch. */
            break;
        case samedi:
        case dimanche:
            /* Même astuce pour samedi et dimanche. */
            printf("Le nombre entré correspond à un jour du week-end.\n");
            break;
        default:
            /* On tombe ici si la valeur de 'nombre' ne correspond à
             * aucun des cas énumérés ci-dessus. */
            printf("Le nombre entré doit être compris entre 1 et 7!\n");
            /* Pas besoin de break ici, puisqu'on sort du switch tout de
             * suite après. */
    }

    return EXIT_SUCCESS;
}
