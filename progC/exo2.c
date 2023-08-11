#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int charToInt(char* nombreT);
double charToDouble(char* nombreT);
int puissance(int iva,int avo);
int len(char* tab);
char** allouer(int line,int col);
char** separer(char* tab,int positionV);
int repereVirgule(char* tab);

int main(){
	//char Atransf[]="23";
	//double nombre = charToDouble(Atransf);
	//printf("ty le izy %f",nombre);
	return 0;
}

double charToDouble(char* nombreT){
	double nombre=0;
	
	int positionV = positionV=repereVirgule(nombreT);
	char** nombresT = separer(nombreT,positionV);
	int entiere=charToInt(nombresT[0]);
	int decimale=charToInt(nombresT[1]);
	int lenDecimale=len(nombresT[1]);
	
	double deci=decimale*pow(10,-lenDecimale);
	nombre=entiere+deci;
	free(nombresT);
	return nombre;
}

int charToInt(char* nombreT){
	int nb=0;
	int longueur=0;
	
	longueur=len(nombreT);
	for (int i=longueur-1,j=0 ; i>=0 ; i--,j++){
		int x=nombreT[i]-48;
		int puissance10 = puissance(10,j);
		if (x>=10){
			return -5;
		}
		else if (x<0){
			return -5;
		}
		else{
			x*=puissance10;
			nb=nb+x;
		}
	}
	return nb;
}

int len(char* tab){
	int i=0;
	while(tab[i] != '\0') i++;
	return i;
}

int puissance(int iva,int avo){
	int nombre=1;
	for(int i=0;i<avo;i++){
		nombre=nombre*iva;
	}
	return nombre;
}

int repereVirgule(char* tab){
	int indexV=-1;
	int nbVirgule=0;
	int i=0;
	while(tab[i] != '\0'){
		if(tab[i]=='.' || tab[i]==','){
			indexV=i;
			nbVirgule++;
		}
		if((tab[i] != '.' && tab[i] != ',') && (tab[i]<48 || tab[i]>57)){
			nbVirgule=2;
		}
		i++;
	}
	
	if(nbVirgule>1){
		printf("Mauvais saisi !\n");
		exit(1);
	}
	
	if(indexV<1) return i;
	else return indexV;
}

char** separer(char* tab,int positionV){
	int line=2,
		col=50;
	char** nombresT=allouer(line,col);
	
	for (int i=0 ; i<positionV ; i++){
		nombresT[0][i]=tab[i];
	}
	
	int i=positionV+1;
	while (tab[i] != '\0'){
		nombresT[1][i-positionV-1] = tab[i];
		i++;
	}
	return nombresT;
}

char** allouer(int line,int col){
	char** tab=(char**)malloc(line*sizeof(char*));
	
	for (int i=0; i<line ; i++){
		*(tab+i)=(char*)malloc(col*sizeof(char));
	}
	return tab;
}
