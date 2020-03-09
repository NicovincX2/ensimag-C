#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static bool est_palindrome(const char *mot)
{
    return true;
}

/*
    Ce prototype de fonction main permet de récupérer les arguments
    passés au programme sur la ligne de commande (ici, le mot sur
    lequel travailler).
*/
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s mot\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}
