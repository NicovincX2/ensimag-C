#include <stdio.h>

int main()
{
    /*
        age est un pointeur sur entier mais il n'est pas défini par un malloc par exemple.
		Il n'y a, à ce stade, aucune case mémoire réservée pour stocker un entier.
		gdb / ddd : age vaut 0x0 soit le pointeur NULL
		Message valgrind : uninitialzed value
	*/
	int *age;

	printf("Bonjour,\n");
	printf("Entrez votre age\n");
	/*
        La syntaxe est correcte car age est bien un pointeur.
		Mais comme age ne pointe sur aucune zone mémoire réservée/allouée.
		Il est impossible d'écrire une valeur dans cette zone mémoire non définie.
		Message valgrind : illegal write...
	*/
	scanf("%d", age);
	/*
        La syntaxe est correcte car *age désigne bien une valeur entière.
		Mais *age représente le contenu d'une zone mémoire non réservée/allouée.
		Il est impossible de lire une valeur dans cette zone mémoire non définie.
	*/
	printf("Vous avez %d ans\n", *age);
	return 0;

}
