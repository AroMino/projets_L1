#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int charToInt(char* nombreT);
int puissance(int iva,int avo);
int len(char* tab);

int mijerySigne(char* nombreChar){
	int signe=0;
	if(nombreChar[0]=='-') signe=1;
	
	return signe;
}

int main(){
	char Atransf[]="-3";
	int nombre=charToInt(Atransf);
	printf("ty le izy %d",nombre);
	return 0;
}

int charToInt(char* nombreT){
	int nb=0;
	int longueur=0;
	int signe = mijerySigne(nombreT);
	longueur=len(nombreT);
	for (int i=longueur-1,j=0 ; i>=0+signe ; i--,j++){
		int x=nombreT[i]-48;
		int puissance10 = puissance(10,j);
			x*=puissance10;
			nb=nb+x;

	}
	if(signe==1) nb*=-1;
	return nb;
}

int len(char* tab){
	int i=0;
	while(tab[i] != '\0'){
		i++;
	}
	return i;
}

int puissance(int iva,int avo){
	int nombre=1;
	for(int i=0;i<avo;i++){
		nombre=nombre*iva;
	}
	return nombre;
}
