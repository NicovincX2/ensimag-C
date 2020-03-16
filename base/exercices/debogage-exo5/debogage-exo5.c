#include <stdio.h>

/*
  a et b sont 2 variables (pointeurs) globales.
  Elles ont une existence durant toute la vie de ce programme.
*/
int *a, *b;

void f(int x)
{
    /*
      i est un tableau local à la fonction f.
      i n'a d'existence et de mémoire réservée pour lui qu'à l'intérieur
      de cette fonction f. Dès la sortie de f, la mémoire attribuée à i
      est libérée automatiquement.
    */
    int i[3];
    i[0] = x;
    i[1] = x + 1;
    i[2] = x + 2;
    /*
      a pointe sur l'adresse de i.
      i étant libéré à la sortie de f, a pointera à la sortie de f
      sur une zone mémoire qui n'est plus attribuée au programme.
    */
    a = i;
}

void g(int x)
{
    /*
      i est un tableau local à la fonction g.
      i n'a d'existence et de mémoire réservée pour lui qu'à l'intérieur
      de cette fonction g. Dès la sortie de g, la mémoire attribuée à i est
      libérée automatiquement. Le problème ici est que le tableau i reprend
      "par hasard" la zone mémoire libérée par le tableau i de la fonction f.
      Cette zone mémoire sur laquelle pointe aussi a est modifiée par la
      fonction g, d'où l'affichage final.
    */
    int i[3];
    i[0] = x;
    i[1] = x + 1;
    i[2] = x + 2;
    b = i;
}

int main()
{
    f(1); /* Modifie a */
    printf("a = {%d,%d,%d}\n", a[0], a[1], a[2]);
    g(2); /* Modifie b */
    printf("Abracadabrantesque, a = {%d,%d,%d}\n", a[0], a[1], a[2]);
    return 0;
}

