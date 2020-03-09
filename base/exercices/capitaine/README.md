# Enoncé

Cet exercice vous fera manipuler les opérateurs d'incrémentation et
d'affectation composée. Le but du jeu est de rétablir un affichage
correct (au niveau du sens de l'histoire). Rien de bien compliqué à
priori, alors pour corser un peu l'affaire, vous n'avez le droit
d'insérer dans le code ci-dessous que les caractères suivants :

```c
++
--
+=
*=
/=
2
3
5
```

A noter que `+` tout seul ne fait pas partie de cette liste, et donc
que vous ne pouvez pas écrire `age + 5`. Bad luck!

Le point de départ pour cet exercice (squelette de code, énoncé) se trouve dans `exercices/base/capitaine/`.

# Ressources associées

Le PAPL [Les opérateurs du langage C](http://formationc.pages.ensimag.fr/prepa/prof/#papl/operateurs/) vous apprendra tout ce qu'il y a à savoir sur... euh... les opérateurs du langage C.

# Indices

<details>
<summary>Cliquez ici pour révéler des indices sur cet exercice.</summary>
<br>

* un opérateur peut être vu comme une fonction, et de ce fait être
  passé en paramètre d'une autre fonction (comme `printf`). Ex:
```c
printf("x+1 = %u", ++x);
```
* trouver la différence entre `x++` et `++x`

</details>

# Compétences

* Opérateurs d'incrémentation
* Opérateurs d'affectation composée

# Difficulté

:star:
# Correction

<details>
<summary>Cliquez ici pour révéler la correction de l'exercice.</summary>
#### Corrigé du fichier Makefile

```make
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g

all: capitaine

.PHONY: clean
clean:
	rm -f *~ *.o capitaine

```

#### Corrigé du fichier capitaine.c

```c
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static void correction(void)
{
    uint8_t age = 25;

    printf("Le capitaine a %u ans.\n", age);
    /* ++age signifie qu'un incrémente d'abord la valeur de la variable avant de l'afficher. */
    printf("C'est son anniversaire! Il a maintenant %u ans.\n", ++age);
    /* Ici, on ajoute 5 à la variable age à l'aide de l'opérateur d'affectation composée +=. */
    printf("5 ans plus tard, alors qu'il a %u ans, il tombe sur une potion de jouvence...\n", age += 5);
    /* Même chose que ++age, sauf qu'on décrémente la variable cette fois-ci. */
    printf("Boire cette potion le fait rajeunir d'un an! Il a maintenant %u ans.\n", --age);
    printf("Il s'est mis à chercher d'autres potions de ce type, mais s'est arrêté quand il a eu le double de l'âge qu'il avait juste après avoir bu la première potion.\n");
    /* On utilise l'opérateur d'affectation composée *= pour faire l'équivalent de age = age * 2; */
    printf("Ca lui fait quel âge maintenant? Ah oui! %u ans.\n", age *= 2);
    printf("Il commence à se faire vieux, et regrette le temps où il avait le tiers de son âge.\n");
    /* Même chose pour la division! */
    printf("Un temps que les moins de 2 fois %u ans ne peuvent pas connaitre.\n", age /= 3);
}

int main(void)
{
    uint8_t age = 25;

    printf("Le capitaine a %u ans.\n", age);
    printf("C'est son anniversaire! Il a maintenant %u ans.\n", age);
    printf("5 ans plus tard, alors qu'il a %u ans, il tombe sur une potion de jouvence...\n", age);
    printf("Boire cette potion le fait rajeunir d'un an! Il a maintenant %u ans.\n", age);
    printf("Il s'est mis à chercher d'autres potions de ce type, mais s'est arrêté quand il a eu le double de l'âge qu'il avait juste après avoir bu la première potion.\n");
    printf("Ca lui fait quel âge maintenant? Ah oui! %u ans.\n", age);
    printf("Il commence à se faire vieux, et regrette le temps où il avait le tiers de son âge.\n");
    printf("Un temps que les moins de 2 fois %u ans ne peuvent pas connaitre.\n", age);

    printf("\n\nVersion prof: \"Oh Captain! My Captain!\"\n");
    correction();
    return EXIT_SUCCESS;
}

```


</details>
