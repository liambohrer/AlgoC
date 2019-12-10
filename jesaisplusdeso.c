#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x = 30, y = 25;
int pourcentageObstacles = 20;

void initNull(char tabC[x][y], int tabI[x][y]);
void showTab(char tabC[x][y], char tabI[x][y]);
void updateTab(char tabC[x][y], int tabI[x][y]);
void makeObstacles(int tabI[x][y]);
void addEndAndStart(int tabI[x][y]);
void addBorder(int tabI[x][y]);

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  int tabI[x][y];
  char tabC[x][y];

  initNull(tabC, tabI);
  addBorder(tabI);
  addEndAndStart(tabI);
  makeObstacles(tabI);
  updateTab(tabC, tabI);
  showTab(tabC, tabI);

  return 0;
}

void showTab(char tabC[x][y], char tabI[x][y]){
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%c", tabC[i][j]);
    }
    printf("\n");
  }
    printf("\n");
    printf("oui\n");
    printf("\n");
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%d", tabI[i][j]);
    }
    printf("\n");
  }
}

void updateTab(char tabC[x][y], int tabI[x][y]){
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      switch(tabI[x][y]){
        case -1 :
          tabC[x][y] = '#';
          break;
        
        case -2 : 
          tabC[x][y] = 'A';
          break;
      
        case 1 : 
          tabC[x][y] = 'D';
          break;

        default :
          tabC[x][y] = ' ';
          break;
      }
    }
  }
}

void makeObstacles(int tabI[x][y]){
  for (int i = 1; i < x-1; i++) {
    for (int j = 1; j < y-1; j++) {
      tabI[i][j] = (rand() % 100 < pourcentageObstacles) ? -1 : 0;  
    }
  }
}

void addEndAndStart(int tabI[x][y]){
  int randX = (rand() % (x-2)) + 1;
  int randY = (rand() % (y-2)) + 1;
  tabI[randX][randY] = -2;

  randX = (rand() % (x-2)) + 1;
  randY = (rand() % (y-2)) + 1;
  tabI[randY][randX] = 1;
}
 
void addBorder(int tabI[x][y]){
  for (int i = 0; i < x; i++) {
    tabI[i][0] = -1;
    tabI[i][y-1] = -1;
  }
  for (int i = 0; i < y; i++) {
    tabI[0][i] = -1;
    tabI[x-1][i] = -1;
  }
}

void initNull(char tabC[x][y], int tabI[x][y]){
  for (int i = 1; i < x-1; i++) {
    for (int j = 1; j < y-1; j++) {
      tabI[i][j] = 0;  
      tabC[i][j] = '.';  
    }
  }
}
