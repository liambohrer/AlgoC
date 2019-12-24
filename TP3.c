#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x = 50, y = 100;
int pourcentageObstacles = 30;

void initNull(char tabC[x][y], int tabI[x][y]);
void showTabChar(char tabC[x][y]);
void showTabInt(int tabI[x][y]);
void updateTab(char tabC[x][y], int tabI[x][y]);
void addObstacles(int tabI[x][y]);
void addEndAndStart(int tabI[x][y], int* xs, int* xe, int* ys, int* ye);
void addBorder(int tabI[x][y]);
int findTheWayMyFriend(int tab[x][y], int* xe, int* ye);
int goToHome(int tab[x][y], int* xs, int* ys);

int main(int argc, char const *argv[]) {



// ------------------- DECLARATION ------------------- //



  srand(time(NULL));

  int tabI[x][y];
  char tabC[x][y];

  int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0, ret = 0, xEndFound = 0, yEndFound = 0, xStartFound = 0, yStartFound = 0;


// ------------------- MAIN ------------------- //



  initNull(tabC, tabI);
  addBorder(tabI);
  addObstacles(tabI);
  addEndAndStart(tabI, &xStart, &xEnd, &yStart, &yEnd);
  updateTab(tabC, tabI);
  //showTabInt(tabI);
  showTabChar(tabC);
  ret = findTheWayMyFriend(tabI, &xEndFound, &yEndFound);
  ret = goToHome(tabI, &xStartFound, &yStartFound);
  


// ------------------- AFFICHAGE ------------------- //



  printf("\n");
  for (int i = 0; i < y; i++)
  {
    printf("*");
  }
  printf("\n");

  printf("\nLe point de départ est à la ligne %d colonne %d\n", xStart+1, yStart+1);
  printf("Le point d'arrivée est à la ligne %d colonne %d\n", xEnd+1, yEnd+1);

  printf("C'est ok ? %d xe = %d, ye = %d\n\n", ret, xEndFound+1, yEndFound+1);
  updateTab(tabC, tabI);
  showTabChar(tabC);
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
      if (tabI[i][j] <= 9 && tabI[i][j] >= 0){
        printf(" %d ", tabI[i][j]);
      }else
      {
        printf("%d ", tabI[i][j]);
      }
    }
    printf("\n");
  }
}




void updateTab(char tabC[x][y], int tabI[x][y]){
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      switch(tabI[i][j]){
        case 1 : 
          tabC[i][j] = 'D';
          break;

        case 0:
          break;

        case (-1) :
          tabC[i][j] = '#';
          break;
        
        case -2 : 
          tabC[i][j] = 'A';
          break;
      
        case -3 : 
          tabC[i][j] = '0';
          break;
        
        default:
          tabC[i][j] = '.';
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

  do{
    *xs = (rand() % (x-2)) + 1;
    *ys = (rand() % (y-2)) + 1;
    tabI[*xs][*ys] = 1;
    //printf("\nrandX = %d, randY = %d, case update to %d\n", randX, randY, tabI[randX][randY]);
  }while(*xs == *xe && *ys == *ye);
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
      tabC[i][j] = ' ';  
    }
  }
}



int findTheWayMyFriend(int tab[x][y], int* xe, int* ye){
  int count = 0, ret = 0;
  while (ret == 0){
    count++;
    ret = -1;
    for (int i = 1; i < x-1 && ret != 1; i++){
      for (int j = 1; j < y-1 && ret != 1; j++){
        if (tab[i][j] == count){

          if (tab[i+1][j] == 0){
            tab[i+1][j] = count+1;
            ret = 0;
          }
          if (tab[i-1][j] == 0){
            tab[i-1][j] = count+1;
            ret = 0;
          }
          if (tab[i][j-1] == 0){
            tab[i][j-1] = count+1;
            ret = 0;
          }
          if (tab[i][j+1] == 0){
            tab[i][j+1] = count+1;
            ret = 0;
          }          

          if (tab[i+1][j] == -2){
            *xe = i+1;
            *ye = j;
            ret = 1;
          }
          else if (tab[i-1][j] == -2){
            *xe = i-1;
            *ye = j;
            ret = 1;
          }
          else if (tab[i][j-1] == -2){
            *xe = i;
            *ye = j-1;
            ret = 1;
          }
          else if (tab[i][j+1] == -2){
            *xe = i;
            *ye = j+1;
            ret = 1;
          }
        }
      }
    }
  }
  return ret == -1 ? ret : count;
}


int goToHome(int tab[x][y], int* xs, int* ys){
  int ret = 0;
  for (int i = 1; i < x-1; i++){
    for (int j = 1; j < y-1; j++){
      if (tab[i][j] == -2){
        int min, newX, newY;

        while (tab[i][j] != 1){

          ret++;
          min = 0;
          newX = 0;
          newY = 0;

          if(tab[i+1][j] >= 1){
            min = tab[i+1][j];
            newX = i+1;
            newY = j;
          }
          
          if(tab[i-1][j] >= 1 && (min > tab[i-1][j] || min == 0)){
            min = tab[i-1][j];
            newX = i-1;
            newY = j;
          }
          
          if(tab[i][j-1] >= 1 && (min > tab[i][j-1] || min == 0)){
            min = tab[i][j-1];
            newX = i;
            newY = j-1;
          }
          
          if(tab[i][j+1] >= 1 && (min > tab[i][j+1] || min == 0)){
            min = tab[i][j+1];
            newX = i;
            newY = j+1;
          }

          if (newX == 0 && newY == 0){
            return -1;
          }else{
            i = newX;
            j = newY;
            if (tab[i][j] == 1){
              *xs = i;
              *ys = j;
              return ret;
            }else{
              tab[i][j] = -3;
            }
          }
        }
      }
    }
  }
  return ret;
}