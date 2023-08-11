#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int decomposition(int a){
	int i=-1;
	while(a!=0){
		a=a/10;
		i++;
	}
	
	if(i==-1) i++;
	return i;
}

int puissance(int iva,int avo){
	int nombre=1;
	for(int i=0;i<avo;i++){
		nombre=nombre*iva;
	}
	return nombre;
}

char* intToCharEtoile(int a,int zero){
	int degreMax=decomposition(a)+zero;
	
	int signe = 0;
	if(a<0){
		signe = 1;
		a*=-1;
	}
	
	int nombreIndex=degreMax+1 + signe;
	char* tab = (char*)malloc(sizeof(char)*nombreIndex);
	
	for(int i=0;i<=degreMax;i++){
		int puissance10=puissance(10,degreMax-i);
		tab[i]=(a/(puissance10))+48;
		a=a-((a/puissance10)*puissance10);
	}
	tab[nombreIndex]='\0';
	
	if (signe == 1){
		for(int i=nombreIndex-1;i>0;i--){
			tab[i] = tab[i-1];
		}
		tab[0] = '-';
	}
	
	return tab;
}

char* doubleToCharEtoile(double nombre){
	int partieDecimale = (nombre - (int)nombre)*1000000;
	if (partieDecimale < 0) partieDecimale *=-1;
	
	int partieEntiere = (int)nombre;
	char* entiere = intToCharEtoile(partieEntiere,0);
	
	int degre = decomposition(partieDecimale) + 1;
	char* decimale = intToCharEtoile(partieDecimale,6-degre);
	
	int len = strlen(entiere) + 8;
	char* tab = (char*)calloc(len,sizeof(char));
	
	strcat(tab,entiere);
	strcat(tab,".");
	strcat(tab,decimale);
	
	// sprintf(tab,"%s.%s",entiere,decimale);
	
	free(entiere);
	free(decimale);
	
	return tab;
}

int main(){
	float nombre = -15.0235468;
	float nombre2 = 56;
	char* text = doubleToCharEtoile(nombre);
	printf("%s\n",text);
	char* text2 = doubleToCharEtoile(nombre2);
	printf("%s\n",text2);
	
	return 0;
}
