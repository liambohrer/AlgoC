#include <stdio.h>

int caractereCounter(char* str);

int main(int argc, char const *argv[]) {
  char str[100] = {'\0'};
  printf("Entrer votre chaine de caractères : ");
  scanf("%s", str);
  int nbChar = caractereCounter(str);
  char p = 's';
  if (nbChar == 1) {
    p = ' ';
  }
  printf("La chaine de caractère \"%s\" fait %d caractère%c\n", str, nbChar, p);
}

int caractereCounter(char* str){
  int i = 0;
  for (; str[i] != '\0'; i++);
  return i;
}
