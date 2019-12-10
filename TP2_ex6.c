#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ex1(char* str);
void ex2(char* str);
void ex3(char* str);
void ex4(char* str);
void ex5(char* str);
int getInt();
void rmBuffer();
int isPalindrome(char* c);
void rmPonct(char* c, char* cTampon);

int main(int argc, char const *argv[]) {
    char str[100] = {'\0'};
    int nbex = 0;
    printf("Quel exercice veux tu ? ");
    nbex = getInt();
    switch(nbex){
        case 1 :
            ex1(str);
            break;
        
        case 2 :
            ex2(str);
            break;
        
        case 3 :
            ex3(str);
            break;
        
        case 4 :
            ex4(str);
            break;
        
        case 5 : 
            ex5(str);
            break;
        
        default :
            printf("ERROR !");
    }
}

void ex1(char* str){
    printf("Entrer votre chaine de caractères : ");
    scanf("%s", str);
    printf("La chaine de caractère \"%s\" fait %ld caractère%c\n", str, strlen(str), (strlen(str) == 1) ? ' ' : 's');
}



void ex2(char* str){
	int c_int = 0, i = 0;

	printf("Entrer un mot caractère par caractère : \n");

	do{
		scanf("%c", &str[i]);
        rmBuffer();
		i++;
	}while(str[i-1] != '\n' && str[i-1] >= '0' && str[i-1] <= '9');

	str[i-1] = '\n';
	printf("Chaine de caractère : %s\n",str);
	c_int = atoi(str);
	printf("Tableau de int : ");
	printf("%d\n",c_int);
}

void ex3(char* str){
    int nombre, j = 0;
    char cinvert[100] = {'\0'}, c[100] = {'\0'};

    printf("Saisir un nombre entier positif : ");
    scanf("%d", &nombre);
    printf("\n");
    
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
}

void ex4(char* str){
    int end;
    char strbis[100] = {'\0'};

    printf("Entrer la première chaine de caractères : ");
    scanf("%s", str);

    printf("Entrer la deuxième chaine de caractères : ");
    scanf("%s", strbis);

    printf("Les chaines de caractères %s identiques\n", (strcmp(str, strbis) == 0) ? "sont" : "ne sont pas");
}

void ex5(char* str){
    char palindrome[100] = {'\0'};
    printf("Entrer votre phrase : ");
    scanf("%50[^\n]", str);
    rmPonct(str, palindrome);
    printf("%s un palindrome !\n", isPalindrome(palindrome) ? "C'est" : "Ce n'est pas");
}





int getInt(){
  char c;
  do{
    scanf("%c", &c);
    rmBuffer();
  } while(c < '1' || c > '5' || c == '\n'); // on check si c est un chiffre
  return (int) c - 48; // 0 en ASCII = 48 donc on enlève 48 à c pour retrouver un enrier
}

void rmBuffer(){
    char d;
	while((d = getchar()) != '\n' && d != EOF);
}

int isPalindrome(char* c){
  int nbChar = strlen(c)-1, n = 0;
  for(; c[n] == c[nbChar-n] && c[n] != '\0'; n++);
  return n-1 == nbChar;
}

void rmPonct(char* c, char* cTampon){
  int offset = 0;
  for(int i = 0; c[i] != '\0'; i++){
    if(c[i] == ' ' || c[i] == '.' || c[i] == ',' || c[i] == '!' ){
      offset++;
    }else{
      cTampon[i-offset] = c[i];
    }
  }
}