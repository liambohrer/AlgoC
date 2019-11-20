#include <stdio.h>

void afficheChar(char);
char getChar();
int getInt();
void getParam(int* n, int* p, char* C1, char* C2);
void afficheDamierFor(int n, int p, char C1, char C2);
void afficheDamierWhile(int n, int p, char C1, char C2);
void afficheDamierDo(int n, int p, char C1, char C2);

int main(int argc, char const *argv[]) {
  int n = -1, p;
  char C1,C2,opt;

  printf("Bonjour et bienvenue sur DamierSimulator3030\n\n");

  while (n != 0) {

    if (opt == 0 || (opt != 'A' && opt != 'a' && opt != 'B' && opt != 'b' && opt != 'C' && opt != 'c')) {
      printf("Voulez-vous afficher le damier : \n- en utilisant la structure pour (réponse a ou A) \n- en utilisant la structure tant que (réponse b ou B) \n- en utilisant la structure pour (réponse c ou C) \n- acquérir de nouvelles valeurs pour n, p, C1 et C2 (réponse d ou D) : ");
      opt = getChar();
    }

    printf("\n");

    if ((opt == 'A' || opt == 'a') && n != -1) {
      afficheDamierFor(n,p,C1,C2);
      opt = 0;
    } else if ((opt == 'B' || opt == 'b') && n != -1) {
      afficheDamierWhile(n,p,C1,C2);
      opt = 0;
    } else if ((opt == 'C' || opt == 'c') && n != -1) {
      afficheDamierDo(n,p,C1,C2);
      opt = 0;
    } else if (opt == 'D' || opt == 'd') {
      getParam(&n, &p, &C1, &C2);
      printf("\n");
      opt = 0;
    } else if (n == -1) {
      printf("Vous devez d'abord acquérir des valeurs pour n, p, C1 et C2 : \n");
      getParam(&n, &p, &C1, &C2);
      printf("\n");
    }
  }

  printf("\n Merci et a bientot !\n");
  return 0;
}

void getParam(int* n, int* p, char* C1, char* C2){
  printf("Entrer un entier n : ");
  do {               // à enlever pour n impaire
    *n = getInt();
  } while(*n%2 == 1); // à enveler pour n impaire

  if (*n != 0) {

    printf("Entrer un entier p : ");
    *p = getInt();

    printf("Entrer un caractère C1 : ");
    *C1 = getChar();

    printf("Entrer un caractère C2 : ");
    do {
      *C2 = getChar();
    }while (*C2 == *C1); // on check si on à pas deux mêmes caractères
  }
}

char getChar(){
  char c;
  do{
    scanf("%c", &c);
    char temp;
    while ((temp = getchar()) != '\n' && temp != EOF) { }
  } while(c < ' ' || c > '~' || c == '\n'); // on check si c est un bien un caractère
  return c;
}

int getInt(){
  char c;
  do{
    scanf("%c", &c);
    char temp;
    while ((temp = getchar()) != '\n' && temp != EOF) { }
  } while(c < '0' || c > '9' || c == '\n'); // on check si c est un chiffre
  return (int) c - 48; // 0 en ASCII = 48 donc on enlève 48 à c pour retrouver un enrier
}

void afficheDamierFor(int n, int p, char C1, char C2){
  int invert = 0;
  printf("Damier4K.jpg :\n\n");
  for (int k = 0; k < n*p; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        if (invert == 0) {
          printf("%c", C1);
        } else {
          printf("%c", C2);
        }
      }
      if (!(n%2 == 1 && i == (n-1))) { // fonctionne avec n impaire, ca permet de ne pas inverser les caractères quand on arrive en fin de ligne
        invert = !invert;
      }
    }
    if (((k+1)%p) == 0) { // on inverse notre caractère tout les p lignes
      invert = !invert;
    }
    printf("\n");
  }
  printf("\nVoici votre damier pour les paramètres n = %d, p = %d, C1 = %c, C2 = %c\n\n", n, p, C1, C2);
}

void afficheDamierWhile(int n, int p, char C1, char C2){
  int invert = 0, k = 0, i = 0, j = 0;
  printf("Damier4K.jpg :\n\n");
  while (k < n*p) {
    while (i < n) {
      while (j < p) {
        if (invert == 0) {
          printf("%c", C1);
        } else {
          printf("%c", C2);
        }
        j++;
      }
      j = 0;
      //if (!(n%2 == 1 && i == (n-1))) { // fonctionne avec n impaire, ca permet de ne pas inverser les caractères quand on arrive en fin de ligne
      invert = !invert;
      //}
      i++;
    }
    i = 0;
    if (((k+1)%p) == 0) { // on inverse notre caractère tout les p lignes
      invert = !invert;
    }
    printf("\n");
    k++;
  }
  printf("\nVoici votre damier pour les paramètres n = %d, p = %d, C1 = %c, C2 = %c\n\n", n, p, C1, C2);
}

void afficheDamierDo(int n, int p, char C1, char C2){
  int invert = 0, k = 0, i = 0, j = 0;
  printf("Damier4K.jpg :\n\n");
  do {
    do {
      do {
        if (invert == 0) {
          printf("%c", C1);
        } else {
          printf("%c", C2);
        }
        j++;
      }while (j < p);
      j = 0;
      //if (!(n%2 == 1 && i == (n-1))) { // fonctionne avec n impaire, ca permet de ne pas inverser les caractères quand on arrive en fin de ligne
      invert = !invert;
      //}
      i++;
    } while (i < n);
    i = 0;
    if (((k+1)%p) == 0) { // on inverse notre caractère tout les p lignes
      invert = !invert;
    }
    printf("\n");
    k++;
  } while (k < n*p);
  printf("\nVoici votre damier pour les paramètres n = %d, p = %d, C1 = %c, C2 = %c\n\n", n, p, C1, C2);
}
