#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x = 30, y = 50;
int pourcentageObstacles = 20;

void initNull(char tabC[x][y], int tabI[x][y]);
void showTabChar(char tabC[x][y]);
void showTabInt(int tabI[x][y]);
void updateTab(char tabC[x][y], int tabI[x][y]);
void addObstacles(int tabI[x][y]);
void addEndAndStart(int tabI[x][y], int* xs, int* xe, int* ys, int* ye);
void addBorder(int tabI[x][y]);

int main(int argc, char const *argv[]) {



// ------------------- DECLARATION ------------------- //



  srand(time(NULL));

  int tabI[x][y];
  char tabC[x][y];

  int xStart, yStart, xEnd, yEnd;  



// ------------------- MAIN ------------------- //



  initNull(tabC, tabI);
  addBorder(tabI);
  addObstacles(tabI);
  addEndAndStart(tabI, &xStart, &xEnd, &yStart, &yEnd);
  updateTab(tabC, tabI);
  //showTabInt(tabI);
  showTabChar(tabC);
  


// ------------------- AFFICHAGE ------------------- //



  printf("\n");
  for (int i = 0; i < y; i++)
  {
    printf("*");
  }
  printf("\n");

  printf("\nLe point de départ est à la ligne %d colonne %d\n", xStart+1, yStart+1);
  printf("Le point d'arrivée est à la ligne %d colonne %d\n", xEnd+1, yEnd+1);

  return 0;
}




void showTabChar(char tabC[x][y]){
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%c", tabC[i][j]);
    }
    printf("\n");
  }
}

void showTabInt(int tabI[x][y]){
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
      switch(tabI[i][j]){
        case (-1) :
          tabC[i][j] = '#';
          break;
        
        case -2 : 
          tabC[i][j] = 'A';
          break;
      
        case 1 : 
          tabC[i][j] = 'D';
          break;

        default :
          tabC[i][j] = ' ';
          break;
      }
    }
  }
}




void addObstacles(int tabI[x][y]){
  for (int i = 1; i < x-1; i++) {
    for (int j = 1; j < y-1; j++) {
      tabI[i][j] = (rand() % 100 < pourcentageObstacles) ? -1 : 0;  
    }
  }
}

void addEndAndStart(int tabI[x][y], int* xs, int* xe, int* ys, int* ye){
  *xe = (rand() % (x-2)) + 1;
  *ye = (rand() % (y-2)) + 1;
  tabI[*xe][*ye] = -2;
  //printf("\nrandX = %d, randY = %d, case update to %d\n", randX, randY, tabI[randX][randY]);

  *xs = (rand() % (x-2)) + 1;
  *ys = (rand() % (y-2)) + 1;
  tabI[*xs][*ys] = 1;
  //printf("\nrandX = %d, randY = %d, case update to %d\n", randX, randY, tabI[randX][randY]);
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
