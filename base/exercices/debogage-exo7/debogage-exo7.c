#include <stdio.h>

int main()
{
    int i;
    /*
      Le ";" à la fin de la boucle for termine cette boucle
      qui n'effectue donc aucun traitement, si ce n'est i++.
      A la sortie de la boucle, i vaut 43.
    */
    for (i = 0; i <= 42; i++);
    {
        /*
    	  Ce printf est en dehors de la boucle.
    	  Il n'est donc exécuté qu'une seule fois.
    	*/

    	printf("i=%d\n", i);
    }
    return 0;
}

