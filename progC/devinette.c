#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void jeu();

int main(){
	printf("Ce programme est un jeu de devinette\nVous devez devinez le nombre entre 1 et 100 que le jeu génère aléatoirement\n");
	printf("Vous n'avez que 7 tentatives!\n");
	
	char a='a';
	scanf("%c",&a);

	system("clear");
	printf("C'est partie!\n");
	
	int option=1;
	
	while(option==1){
		jeu();
		printf("\n\n	Rejouer = 1");
		printf("\n	Quitter = 0\n");
		scanf("%d",&option);
		system("clear");
	}
	system("clear");
	printf("BYE BYE");
	return 0;
}
	
void jeu(){
		int valeurCache=0;
	int valeurEntre=3;
	int compteur=0;
	int i=0;
	srand(time(NULL));
	valeurCache=rand() %100 +1;
	
	while(valeurEntre!=valeurCache && compteur<7){
		i++;
		compteur++;
		printf("\nTentative %d: ",i);
		scanf("%d",&valeurEntre);
		if(valeurEntre>valeurCache){
				printf("Le nombre est inférieur à %d\n",valeurEntre);
		}
		else if(valeurEntre<valeurCache){
				printf("Le nombre est superieur à %d\n",valeurEntre);
		}
		else{
			printf("\n=====>>>>Félicitaions! Nombre trouvé \n");
			printf("=====>>>>Nombre de tentative : %d \n",compteur);
		}
	}
	printf("\nEchec. Le nombre est %d\n",valeurCache);
}
