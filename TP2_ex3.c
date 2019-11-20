#include <stdio.h>

int main(int argc, char const *argv[]) {

  int nombre, j = 0;
  char cinvert[100] = {'\0'}, c[100] = {'\0'};

  printf("Saisir un nombre entier positif : ");
  scanf("%d", &nombre);
  printf("\n")
  ;
  for (int i = 1; nombre/i > 0; i *= 10) {
    printf("%d   %d   %d   %d\n", ((nombre/i) % 10), (nombre/i), i, j);
    cinvert[j] = ((nombre/i) % 10) + 48;
    j++;
  }

  printf("\nInvertion du tab char : \n\n");

  for (int i = j-1; i >= 0; i--) {
    printf("%d   %d\n", i, j-i-1);
    c[i] = cinvert[j-i-1];
  }

  printf("\nAffichage du nombre converti en tableau de char :\n");
  for (int i = j+1; i >= 0; i--) {
    printf("_");
  }
  printf("\n|%s|\n", c);
  for (int i = j+1; i >= 0; i--) {
    printf("‾");
  }
  printf("\n");

  return 0;
}