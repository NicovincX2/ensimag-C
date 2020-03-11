#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    /* Affiche un message d'erreur si l'utilisateur oublie l'argument
     * à passer en ligne de commandes. */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s nombre\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Convertit l'argument passé par l'utilisateur en entier unsigned. */
    int32_t au_cas_ou = atoi(argv[1]);
    if (au_cas_ou < 1) {
        fprintf(stderr, " on a dit \"strictement positif\", le nombre! Pas %d...\n", au_cas_ou);
        exit(EXIT_FAILURE);
        /* Tiens et si ca tient pas sur 32 bits? A voir... */
    }
    // conversion explicite en entier signé (ie. positif)
    uint32_t nombre = (uint32_t) au_cas_ou;

    /* On compte le nombre de diviseurs entre 2 et nombre-1 */
    uint32_t nb_diviseurs = 0;
    for (uint32_t n = 2; n < nombre; n++) {
        /* % est l'opérateur modulo. */
        // printf("%u\n", n);
        if (nombre % n == 0) {
            printf("%u est un diviseur de %u.\n", n, nombre);
            nb_diviseurs++;
        }
    }

    if (nb_diviseurs == 0) {
        printf("%u est premier!\n", nombre);
    }

    return EXIT_SUCCESS;
}
