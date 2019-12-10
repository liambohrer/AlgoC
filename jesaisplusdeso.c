#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x = 15, y = 10;

void afficheTab(char* c);
void obstacle(char* c);

int main(int argc, char const *argv[]) {
  int[x][y] tabI = {0};
  char[x][y] tabC = {' '};
  return 0;
}

void afficheTab(char* c){
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%c", c[i][j]);
    }
  }
}

void obstacle(char* c){
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {

    }
  }
}
