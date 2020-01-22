#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x = 50, y = 100;
int pourcentageObstacles = 35;

void initNull(char tabC[x][y], int tabI[x][y]);
void showTabChar(char tabC[x][y]);
void showTabInt(int tabI[x][y]);
void updateTab(char tabC[x][y], int tabI[x][y]);
void addObstacles(int tabI[x][y]);
void addEndAndStart(int tabI[x][y], int* xs, int* xe, int* ys, int* ye);
void addBorder(int tabI[x][y]);
int findTheWayMyFriend(int tab[x][y], int* xe, int* ye);
int goToHome(int tab[x][y], int* xs, int* ys);

int Controleur(int tab[x][y], int pile[256][3]);
int findTheWayMyFriendButStockThemInAPile(int tab[x][y], int pile[256][3], int* xToCheck, int* yToCheck, int count);
int checkAroundYou(int tab[x][y], int pile[256][3], int xToCheck, int yToCheck, int count);


void empile(int x, int y, int count, int pile[256][3]);
void depile(int* x, int* y, int* count, int pile[256][3]);
int isPileEmpty(int pile[256][3]);

int main(int argc, char const *argv[]) {



// ------------------- DECLARATION ------------------- //



  srand(time(NULL));

  int tabI[x][y];
  char tabC[x][y];

  int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0, ret = 0, xEndFound = 0, yEndFound = 0, xStartFound = 0, yStartFound = 0;
  int pile[256][3] = {-1};

// ------------------- MAIN ------------------- //



  initNull(tabC, tabI);
  addBorder(tabI);
  addObstacles(tabI);
  addEndAndStart(tabI, &xStart, &xEnd, &yStart, &yEnd);
  updateTab(tabC, tabI);
  //showTabInt(tabI);
  showTabChar(tabC);
  ret = findTheWayMyFriend(tabI, &xEndFound, &yEndFound);
  //ret = Controleur(tabI, pile);


// ------------------- AFFICHAGE ------------------- //



  printf("\n");
  for (int i = 0; i < y; i++)
  {
    printf("*");
  }
  printf("\n");

  printf("\nLe point de départ est à la ligne %d colonne %d\n", xStart+1, yStart+1);
  printf("Le point d'arrivée est à la ligne %d colonne %d\n", xEnd+1, yEnd+1);

  ret = goToHome(tabI, &xStartFound, &yStartFound);
  updateTab(tabC, tabI);
  showTabChar(tabC);
  
  if (ret != -1){
    printf("L'arrivée a été trouvée à la ligne %d colonne %d\n", xEndFound+1, yEndFound+1);
  }else{
    printf("L'arrivée n'a pas été trouvée ...\n");
  }
  
  
  if (ret != -1){
    printf("La distance du chemin de retour est de %d case%c\n", ret, (ret <= 1)?' ':'s');
  }else{
    printf("Il y a donc pas de chemin de retour ...\n");
  }
  
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
          tabC[i][j] = '0';
          break;
        
        case -2 : 
          tabC[i][j] = 'A';
          break;
      
        case -3 : 
          tabC[i][j] = '#';
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



int Controleur(int tab[x][y], int pile[256][3]){
  int count = 1, xToCheck = 1, yToCheck = 1, ret = 0;
  for (; (xToCheck < x-1) && (tab[xToCheck][yToCheck] != 1); xToCheck++){
    for (; (yToCheck < y-1) && (tab[xToCheck][yToCheck] != 1); yToCheck++);    
  }
  empile(xToCheck, yToCheck, count, pile);
  while (!isPileEmpty || ret != 1){
    depile(&xToCheck, &yToCheck, &count, pile);
    ret = findTheWayMyFriendButStockThemInAPile(tab, pile, &xToCheck, &yToCheck, count+1);
  }
}



int findTheWayMyFriendButStockThemInAPile(int tab[x][y], int pile[256][3], int* xToCheck, int* yToCheck, int count){
  int ret = 0, retNow;

  &xToCheck + 1;
  retNow = checkAroundYou(tab, pile, *xToCheck, *yToCheck, count);
  ret = retNow;
  if (ret){
    return ret;
  }else if(ret == 0){
    empile(*xToCheck, *yToCheck, count, pile);
  }
  
  &xToCheck - 2;
  retNow = checkAroundYou(tab, pile, *xToCheck, *yToCheck, count);
  ret = (ret == 0) ? 0 : retNow;
  if (ret){
    return ret;
  }else if(ret == 0){
    empile(*xToCheck, *yToCheck, count, pile);
  }
  
  &xToCheck + 1;
  &yToCheck - 1;
  retNow = checkAroundYou(tab, pile, *xToCheck, *yToCheck, count);
  ret = (ret == 0) ? 0 : retNow;
  if (ret){
    return ret;
  }else if(ret == 0){
    empile(*xToCheck, *yToCheck, count, pile);
  }
  
  &yToCheck + 2;
  retNow = checkAroundYou(tab, pile, *xToCheck, *yToCheck, count);
  ret = (ret == 0) ? 0 : retNow;
  if (ret){
    return ret;
  }else if(ret == 0){
    empile(*xToCheck, *yToCheck, count, pile);
  }
    
  &yToCheck - 1;
  return ret;
}

int checkAroundYou(int tab[x][y], int pile[256][3], int xToCheck, int yToCheck, int count){
  if (tab[xToCheck][yToCheck] == 0){
    tab[xToCheck][yToCheck] = count;
    return 0;
  }else if (tab[xToCheck][yToCheck] == -2){
    return 1;
  }else return -1;
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
        }else if(tab[i][j] == -2){
            *xe = i;
            *ye = j;
            ret = 1;
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

void empile(int xToStore, int yToStore, int count, int pile[256][3]){
  int i = 0;
  for (; pile[i][0] != -1; i++);
  pile[i][0] = xToStore;
  pile[i][1] = yToStore;
  pile[i][2] = count;
}

void depile(int* xToGet, int* yToGet, int* count, int pile[256][3]){
  *xToGet = pile[0][0];
  *yToGet = pile[0][1];
  *count = pile[0][2];

  for (int i = 1; pile[i][0] != -1; i++){
    pile[i-1][0] = pile[i][0];
    pile[i-1][1] = pile[i][1];
    pile[i-1][2] = pile[i][2];
  }
}

int isPileEmpty(int pile[256][3]){
 return (pile[0][0] == -1) ? 1 : 0;
}