#include <stdio.h>

int main(void)
{
	char c[100] = {'\0'},d;
	int c_int[100], i = 0;

	printf("Entrer un mot caractère par caractère : \n");

	do{
		scanf("%c", &c[i]);
		while((d = getchar()) != '\n' && d != EOF);
		i++;

	}while(c[i-1] != '\n' && c[i-1] >= '0' && c[i-1] <= '9');

	c[i-1] = '\n';
	printf("Chaine de caractère : %s\n",c);

	printf("Tableau de int : ");
	for(int j = 0 ; c[j] != '\n' ; j++){
		c_int[j] = c[j] - 48;
		printf("%d",c_int[j]);
	}c_int[j] = c[j] - 48;
		printf("%d",c_int[j]);
	printf("\n");

}
