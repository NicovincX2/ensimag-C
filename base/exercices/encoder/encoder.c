#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void verif_params(int argc, char **argv)
{
    if (argc != 4 || atoi(argv[3]) < 1 || atoi(argv[3]) > 25) {
        fprintf(stderr, "Usage: %s input.txt output.txt key\n", argv[0]);
        fprintf(stderr, "où:\n");
        fprintf(stderr, "\t- input.txt est le nom du fichier texte a coder ;\n");
        fprintf(stderr, "\t- output.txt est le nom du fichier dans lequel enregistrer le texte codé ;\n");
        fprintf(stderr, "\t- key est un entier compris entre 1 et 25.\n");
        exit(EXIT_FAILURE);
    }
}

static char coder_lettre(char c, uint8_t cle)
{
    /* Pour que le compilateur soit content. */
    return c;
}


int main(int argc, char **argv)
{
    verif_params(argc, argv);


    return EXIT_SUCCESS;
}
