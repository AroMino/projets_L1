#include <stdio.h>

void choix(int a, int b, int * compteur, int max, int min){				//a: borne sup ; b: borne inf ; *compteur: compteur de tour
	int centre = b+((a-b)/2);											//centre de l'intervalle
	printf ("Le nombre est il supérieur (1) ou égal (2) ou inférieur (3) à %d : ",centre);	
	//printf ("a=%d	b=%d : ",a,b);
	int rep=0;
	
	
	
	scanf ("%d",&rep);
	*compteur += 1;
	
	switch (rep){
		case 1:
		if (centre==max){
			printf("\n\n\tLe nombre est %d\nNombre de tentative : %d",centre+1,*compteur);
			}
		else{
			b=centre;
			choix (a,b,compteur,max,min);
		}
		break;
		
		
		case 2:
		printf("Le nombre est %d\nNombre de tentative : %d",centre,*compteur);
		break;
		
		case 3:
		if (centre==min){
			printf("\n\n\tLe nombre est %d\n\tNombre de tentative : %d",centre-1,*compteur);
			}
		else{
			a=centre;
			choix (a,b,compteur,max,min);
		}
		break;
	}
	

}

int main(){
	
	int a = 2000, b = 0;
	printf("\t\tPenser à un nombre entre %d et %d\n",b,a);
	int max = a - 1, min = b + 1;
	int compteur = 0;
	choix(a,b,&compteur,max,min);
	
	return 0;
}
