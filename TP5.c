#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char c;
    int nbOccur;
} Symbole;
 
Symbole* FileStat(FILE *fich, int *nbSymbole);
void InitTab(Symbole *T, int taille);
void AfficheTab(Symbole *T, int nbSymbole);
void Tri(Symbole *t);

int main(int argc, char const *argv[])
{
    FILE *file;
    int nbSymbole;
    if ((file = fopen("EncryptedFile", "r")) == NULL) {
        printf("Erreur ouverture du fichier !");
        return -1;
    }

    Symbole* tabSym = FileStat(file, &nbSymbole);
    
    AfficheTab(tabSym,nbSymbole);
    Tri(tabSym);
    AfficheTab(tabSym,nbSymbole);
   
    free(tabSym);
    return 0;
}

Symbole* FileStat(FILE *fich, int *nbSymbole){
    int bufferLength = 255, sizeOfTab = 26;
    char buffer[bufferLength];
    Symbole* tabSym = malloc(sizeOfTab*sizeof(Symbole*));

    InitTab(tabSym, sizeOfTab);

    while(fgets(buffer, bufferLength, fich)) {
        printf("%s", buffer);
        for (int i = 0; buffer[i] != '\0'; i++){
            printf("%d",i);
            if (buffer[i] <= 90 && buffer[i] >= 65) buffer[i] += 32;
            if (buffer[i] <= 122 && buffer[i] >= 97){
                int j = 0; 
                for (j = 0; j < sizeOfTab && tabSym[j].c != '\0'; j++){
                    if (buffer[i] == tabSym[j].c){
                        tabSym[j].nbOccur++;
                    }
                }
                if (tabSym[j].c == '\0'){
                    tabSym[j].c = buffer[i];
                    tabSym[j].nbOccur += 1;
                }
            }
            *nbSymbole = i;
        }
        printf("\n");
    }
    return tabSym;
}

void InitTab(Symbole *T, int taille){
    for (int i = 0; i < taille; i++)
    {
        T[i].c = '\0';
        T[i].nbOccur = 0;
    }
}

void AfficheTab(Symbole *T, int nbSymbole){
    printf("\n-------------- Affiche tableau symboles --------------\n\n");
    for (int i = 0; i < 26; i++)
    {
        printf("Symbole %d : '%c' --- Occurende : %d --- Proba : %f\n", i, T[i].c, T[i].nbOccur, (float)T[i].nbOccur/nbSymbole);
    }    
    printf("------------------------------------------------------\n\n");
}

void Tri(Symbole *t){
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++){
            while (t[i].nbOccur > t[j].nbOccur){
                int intTmp = t[i].nbOccur;
                char charTmp = t[i].c;
                t[i].nbOccur = t[j].nbOccur;
                t[i].c = t[j].c;
                t[j].nbOccur = intTmp;
                t[j].c = charTmp;
            }
        }
    }
}