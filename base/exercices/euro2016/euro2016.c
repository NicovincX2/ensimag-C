#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

struct equipe;


static void jouer_match(struct equipe *e1, struct equipe *e2)
{
}

static void afficher_equipe(struct equipe *e)
{
}

int main(void)
{
    /* Initialisation du générateur de nombres aléatoires, utilisé
     * dans jouer_match(). */
    srand(time(NULL));


    return EXIT_SUCCESS;
}
