#include <stdio.h>

int isPalindrome(char* c);
int getSizeOfString(char* c);
void rmPonct(char* c, char* cTampon);

void main(){
  char palindrome[100] = {'\0'}, palindromeRmPonct[100] = {'\0'};
  printf("Entrer votre phrase : ");
  scanf("%50[^\n]", palindrome);
  rmPonct(palindrome, palindromeRmPonct);
  printf("%s un palindrome !\n", isPalindrome(palindromeRmPonct) ? "C'est" : "Ce n'est pas");
}

int getSizeOfString(char* c){
  int n = 0;
  for(; c[n] != '\0'; n++);
  return n;
}

int isPalindrome(char* c){
  int nbChar = getSizeOfString(c)-1, n = 0;
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