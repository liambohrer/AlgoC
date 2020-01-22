#include <stdio.h>

void EncryptLigne1(char *T);
void EncryptLigne2(char *T, unsigned int dec);
void EncryptLigne3(char *T, char *cle);

void DecryptLigne1(char *T);
void DecryptLigne2(char *T, unsigned int dec);
void DecryptLigne3(char *T, char *cle);

void EncryptFile(FILE *in, FILE *out, int methode);
void DecryptFile(FILE *in, FILE *out, int methode);

void LUT(char lut[2][26], char *cle);
void AfficheLUT(char lut[2][26]);

int main(){
  char str[100], filePath[100];
  FILE *in, *out;

  //printf("Entrer une phrase : ");
  //scanf("%50[^\n]", str);

  char d;
  int init = 0;
  do{
    if (init) {
      printf("Le nom de votre fichier n'est pas correct \n");
    }
    printf("Entrer le nom de votre fichier : ");
    scanf("%s", str);
    while((d = getchar()) != '\n' && d != EOF);
    init = 1;
  }while ((in = fopen(str, "r")) == NULL);

  init = 0;
  char c;
  do {
    if (init) {
      printf("Réponse incorrecte \n");
    }
    printf("Voulez-vous encripter ou décripter votre fichier ? (e/d) \n");
    scanf("%c", &c);
    while((d = getchar()) != '\n' && d != EOF);
    init = 1;
  } while(c != 'e' && c != 'd');

  if (c == 'e') {
    if ((out = fopen("EncryptedFile", "w")) == NULL) {
      printf("Erreur création du fichier !");
      return -1;
    }
  } else if (c == 'd') {
    if ((out = fopen("DecryptedFile", "w")) == NULL) {
      printf("Erreur création du fichier !");
      return -1;
    }
  } else {
    printf("Erreur de saisie\n");
    return -1;
  }

  init = 0;
  int met = 1;
  do {
    if (init) {
      printf("Désolée mais cette méthode n'existe pas \n");
    }
    printf("Quelle méthode voulez-vous utiliser ? (1, 2 ou 3) : ");
    scanf("%d", &met);
    while((d = getchar()) != '\n' && d != EOF);
    init = 1;
  } while(met < 1 && met > 3);

  if (c == 'e') {
    EncryptFile(in, out, met);
  } else if (c == 'd') {
    DecryptFile(in, out, met);
  } else {
    printf("Erreur de saisie\n");
    return -1;
  }

  fclose(in);
  fclose(out);

  return 1;
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
    char lut[2][26] = {"abcdefghijklmnopqrstuvwxyz", {'\0'}};
    LUT(lut,cle);
    for(int i = 0; T[i] != '\0'; i++){
        if (T[i] <= 122 && T[i] >= 97)
        {
            T[i] = lut[1][T[i]-97];
        }
        if (T[i] <= 90 && T[i] >= 65)
        {
            T[i] = lut[1][T[i]-65] - 32;
        }
    }
}

void EncryptFile(FILE *in, FILE *out, int methode){
  int bufferLength = 255, num;
  char buffer[bufferLength], cle[26], d;
  char lut[][26] = {"abcdefghijklmnopqrstuvwxyz", {'\0'}};

  switch (methode) {
    case 2:
      printf("Entrer un nombre entre 0 et 25 : ");
      scanf("%d", &num);
      while((d = getchar()) != '\n' && d != EOF);
      break;

    case 3:
      printf("Entrer votre clef secrète : ");
      scanf("%s", cle);
      break;
  }

  printf("\n-------- Fichier à encrypter ---------\n");
  while(fgets(buffer, bufferLength, in)) {
    printf("%s", buffer);
    switch (methode) {
      case 1:
        EncryptLigne1(buffer);
        break;

      case 2:
        EncryptLigne2(buffer, num);
        break;

      case 3:
        EncryptLigne3(buffer, cle);
        break;
    }
    fprintf(out, "%s", buffer);
  }
  printf("--------------------------------------\n");

  fclose(out);
  printf("\n---------- Fichier encrypté ----------\n");
  out = fopen("EncryptedFile", "r");
  while(fgets(buffer, bufferLength, out)) {
    printf("%s", buffer);
  }
  printf("--------------------------------------\n");
}

void DecryptLigne1(char *T){
  EncryptLigne1(T);
}

void DecryptLigne2(char *T, unsigned int dec){
  EncryptLigne2(T, 26-(dec%26));
}

void DecryptLigne3(char *T, char *cle){
  char lut[2][26] = {"abcdefghijklmnopqrstuvwxyz", {'\0'}};
  int n;

  LUT(lut,cle);
  for(int i = 0; T[i] != '\0'; i++){
      if (T[i] <= 122 && T[i] >= 97)
      {
        for (n = 0; lut[1][n] != T[i]; n++);
        T[i] = lut[0][n];
      }
      if (T[i] <= 90 && T[i] >= 65)
      {
        for (n = 0; lut[1][n] - 32 != T[i]; n++);
        T[i] = lut[0][n] - 32;
      }
  }
}

void DecryptFile(FILE *in, FILE *out, int methode){
  int bufferLength = 255, num;
  char buffer[bufferLength], cle[26], d;

  switch (methode) {
    case 2:
      printf("Entrer un nombre entre 0 et 25 : ");
      scanf("%d", &num);
      while((d = getchar()) != '\n' && d != EOF);
      break;

    case 3:
      printf("Entrer votre clef secrète : ");
      scanf("%s", cle);
      break;
  }

  printf("\n-------- Fichier à decrypter ---------\n");
  while(fgets(buffer, bufferLength, in)) {
    printf("%s", buffer);
    switch (methode) {
      case 1:
        DecryptLigne1(buffer);
        break;

      case 2:
        DecryptLigne2(buffer, num);
        break;

      case 3:
        DecryptLigne3(buffer, cle);
        break;
    }
    fprintf(out, "%s", buffer);
  }
  printf("--------------------------------------\n");

  fclose(out);
  printf("\n---------- Fichier decrypté ----------\n");
  out = fopen("DecryptedFile", "r");
  while(fgets(buffer, bufferLength, out)) {
    printf("%s", buffer);
  }
  printf("--------------------------------------\n");
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
    printf("Clef d'encription : \n");
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
