#include <stdio.h>

int main(int argc, char const *argv[]) {

  int end;
  char c1[100] = {'\0'}, c2[100] = {'\0'};

  printf("Entrer la première chaine de caractères : ");
  scanf("%s", c1);

  printf("Entrer la deuxième chaine de caractères : ");
  scanf("%s", c2);

  for (end = 0; c1[end] != '\0' && c2[end] != '\0' && c1[end] == c2[end]; end++);

  printf("Les chaines de caractères %s identiques\n", (c1[end] == '\0' && c2[end] == '\0') ? "sont" : "ne sont pas");

  return 0;
}
