#include <stdio.h>

void EncryptLigne1(char *T);
void EncryptLigne2(char *T, unsigned int dec);

void LUT(char lut[2][26], char *cle);
void AfficheLUT(char lut[2][26]);

void main(){

    char str[100];

    /*printf("Entrer une phrase : ");
    scanf("%50[^\n]", str);*/

    /*EncryptLigne1(str);
    printf("\nPhrase cryptée : \"%s\"\n", str);
    EncryptLigne1(str);
    printf("\nPhrase decryptée : \"%s\"\n", str);*/

    /*EncryptLigne2(str, 13);
    printf("\nPhrase cryptée : \"%s\"\n", str);
    EncryptLigne2(str, 13);
    printf("\nPhrase decryptée : \"%s\"\n", str);*/


    char cle[] = "ocean";
    char lut[][26] = {"abcdefghijklmnopqrstuvwxyz",{'\0'}};

    printf("\n%c  %c\n", lut[0][1], lut[0][2]);

    LUT(lut, cle);
    
    printf("\n%c  %c\n", lut[0][1], lut[0][2]);

    AfficheLUT(lut);

}

void EncryptLigne1(char *T){
    for(int i = 0; T[i] != '\0'; i++){
        if (T[i] <= 122 && T[i] >= 97)
        {
            T[i] = (((T[i] - 84) % 26) + 97);
        }
        if (T[i] <= 90 && T[i] >= 65)
        {
            T[i] = (((T[i] - 52) % 26) + 65);
        }
    }
}

void EncryptLigne2(char *T, unsigned int dec){
    for(int i = 0; T[i] != '\0'; i++){
        if (T[i] <= 122 && T[i] >= 97)
        {
            T[i] = (((T[i] - (97 - (dec % 26))) % 26) + 97);
        }
        if (T[i] <= 90 && T[i] >= 65)
        {
            T[i] = (((T[i] - (65 - (dec % 26))) % 26) + 65);
        }
    }
}

void LUT(char lut[2][26], char *cle){
    int j = 0;
    for(; cle[j] != '\0'; j++){
        lut[1][j] = cle[j];
    }
    int bool;
    for(int i = j; i < 26; i++){
        bool = 1;
        for(int n = 0; cle[j] != '\0'; n++){
            if (cle[n] == lut[0][i-(j)])
            {
                bool = 0;
            }
        }
        if (bool)
        {
            lut[1][i] = lut[0][i-(j)];
        }else
        {
            j--;
        }
    }
}


void AfficheLUT(char lut[2][26]){
    printf("\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            printf("%c", lut[i][j]);
        }
        printf("\n");
    }        
}