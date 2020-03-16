#include <stdio.h>
#include <stdint.h>

int main()
{
    /*
      i est un entier non signé. Il ne sera jamais inférieur à 0.
    */
    uint16_t i;
    /*
      Quand i arrive à 0, --i affecte la borne maximale 65 535 du type uint16_t à i
      et non pas -1. Le test i >= 0 est donc toujours vrai, d'où la boucle infinie.
      i est décrémenté de façon infinie depuis cette borne maximale 65 535 jusqu'à 0.
    */
    for (i = 12; i >= 0; --i) {
        printf("i = %d\n", i);
    }

}


