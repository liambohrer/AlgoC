#include <stdio.h>

void EncryptLigne1(char *T);
void EncryptLigne2(char *T, unsigned int dec);
void EncryptLigne3(char *T, char *cle);

void LUT(char lut[2][26], char *cle);
void AfficheLUT(char lut[2][26]);

void main(){

    char str[100];

    printf("Entrer une phrase : ");
    scanf("%50[^\n]", str);

    /*EncryptLigne1(str);
    printf("\nPhrase cryptée : \"%s\"\n", str);
    EncryptLigne1(str);
    printf("\nPhrase decryptée : \"%s\"\n", str);*/

    /*EncryptLigne2(str, 13);
    printf("\nPhrase cryptée : \"%s\"\n", str);
    EncryptLigne2(str, 13);
    printf("\nPhrase decryptée : \"%s\"\n", str);*/


    char cle[26];
    char lut[][26] = {"abcdefghijklmnopqrstuvwxyz",{'\0'}};

    printf("Entrer votre clef secrète : ");
    scanf("%s", cle);
    LUT(lut, cle);
    AfficheLUT(lut);
    EncryptLigne3(str, lut[1]);
    printf("Phrase cryptée : \"%s\"\n", str);

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

void EncryptLigne3(char *T, char *cle){
    for(int i = 0; T[i] != '\0'; i++){
        if (T[i] <= 122 && T[i] >= 97)
        {
            T[i] = cle[T[i]-97];
        }
        if (T[i] <= 90 && T[i] >= 65)
        {
            T[i] = cle[T[i]-65] - 32;
        }
    }
}

void LUT(char lut[2][26], char *cle){
    int j = 0, k = -1;
    for(; cle[j] != '\0'; j++){
        lut[1][j] = cle[j];
    }
    int bool;
    for(int i = j-1; i < 26+k; i++){
        bool = 1;
        for(int n = 0; cle[n] != '\0'; n++){
            if (cle[n] == lut[0][i-(j-1)])
            {
                bool = 0;
            }
        }
        if (bool)
        {
            lut[1][i-k] = lut[0][i-(j-1)];
        }else
        {
            k++;
        }
    }
}

void AfficheLUT(char lut[2][26]){
    for (int i = 0; i < 2; i++)
    {   
        printf("__________________________\n");

        for (int j = 0; j < 26; j++)
        {
            printf("%c", lut[i][j]);
        }
        printf("\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
    }        
}