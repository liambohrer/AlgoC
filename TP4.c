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

  char d, c;
  int init = 0, stop = 0;

  do{

    init = 0;

    do{
      printf("Voulez-vous traiter un fichier ou une phrase (f/p) ? ");
      scanf("%c", &c);
      while((d = getchar()) != '\n' && d != EOF);
    } while (c != 'f' && c != 'p');

    if (c == 'f'){
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
      do {
        if (init) {
          printf("Réponse incorrecte \n");
        }
        printf("Voulez-vous encripter ou décripter votre fichier (e/d) ? ");
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
          printf("Cette méthode n'existe pas !\n");
        }
        printf("Quelle méthode voulez-vous utiliser ? (1, 2 ou 3) : ");
        scanf("%d", &met);
        while((d = getchar()) != '\n' && d != EOF);
        init = 1;
      } while(met < 1 || met > 3);

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
    }else{
      printf("Entrer votre phrase : ");
      scanf("%50[^\n]", str);    
      while((d = getchar()) != '\n' && d != EOF);

      init = 0;
      int met = 1;
      do {
        if (init) {
          printf("Cette méthode n'existe pas !\n");
        }
        printf("Quelle méthode voulez-vous utiliser ? (1, 2 ou 3) : ");
        scanf("%d", &met);
        while((d = getchar()) != '\n' && d != EOF);
        init = 1;
      } while(met < 1 || met > 3);

      int num; 
      char cle[26], lut[][26] = {"abcdefghijklmnopqrstuvwxyz", {'\0'}};       
      switch (met){
        case 1 :
          EncryptLigne1(str);
          break;
        
        case 2 :
          printf("Entrer un nombre entre 0 et 25 : ");
          scanf("%d", &num);
          while((d = getchar()) != '\n' && d != EOF);
          EncryptLigne2(str,num);
          break;
        
        case 3 :
          printf("\nEntrer votre clef secrète : ");
          scanf("%s", cle);
          while((d = getchar()) != '\n' && d != EOF);
          LUT(lut,cle);
          AfficheLUT(lut);
          EncryptLigne3(str,cle);
          break;
        
        default:
          break;
      }

      printf("Phare encriptée : %s", str);

      printf("\nVoulez-vous la décriptée (o/n) ? ");

      do{
        scanf("%c", &c);
        while((d = getchar()) != '\n' && d != EOF);
      } while(c != 'o' && c != 'n');
      if (c == 'o'){
        switch (met){
          case 1 :
            DecryptLigne1(str);
            break;
          
          case 2 :
            DecryptLigne2(str,num);
            break;
          
          case 3 :
            DecryptLigne3(str,cle);
            break;
          
          default:
            break;
        }
        printf("Phare decriptée : %s", str);
      }
    }

    printf("\nVoulez-vous continuer (o/n) ? ");
    do{
      scanf("%c", &c);
      while((d = getchar()) != '\n' && d != EOF);
    } while(c != 'o' && c != 'n');
    if (c == 'o'){
      stop = 0;
    }else{
      stop = 1;
    }
  } while (!stop);
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
      printf("\nEntrer votre clef secrète : ");
      scanf("%s", cle);
      while((d = getchar()) != '\n' && d != EOF);
      LUT(lut,cle);
      AfficheLUT(lut);
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
      while((d = getchar()) != '\n' && d != EOF);
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
	int taille;
	int i,j,k,l;

	for(i = 0; cle[i] != '\0' ; i++);
	taille = i;

	for(j = 0 ; j < taille ; j++){lut[1][j] = cle[j];}
	for(k = 0; k < 26 ; k++){
		for(l = 0; (lut[0][k] != lut[1][l]) &&  (l < taille) ; l++);
		if(l == taille){
			lut[1][taille] = lut[0][k];
			taille = taille + 1;
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
