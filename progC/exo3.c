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
char** getChamp(char* date);
char* transformation(char* date);
void gestionErreur(char* date);
int conversionEnSeconde(double a);
char* conversionHMS(double jourDouble);
char* intToCharEtoile(int a,int b);
void enleverDecimale(char* tab);

int main(){
	char date[]="38.235/05/2023";
	char* valiny=transformation(date);
	printf("%s",valiny);
	free(valiny);
	return 0;
}

char* transformation(char* date){
	char** champ = NULL;
	champ=getChamp(date);
	double jourDouble = charToDouble(champ[0]);
	enleverDecimale(champ[0]);
	char* heureChar=conversionHMS(jourDouble-(int)jourDouble);
	char* valiny = (char*)malloc(50);
	sprintf(valiny,"%s/%s/%s %s",champ[0],champ[1],champ[2],heureChar);
	free(heureChar);
	free(champ);
	return valiny;
}

char* conversionHMS(double jourDouble){

	int seconde=conversionEnSeconde(jourDouble);
	
	int heure = 0;
	if(seconde >= 3600){
		heure = seconde/3600;
		seconde = seconde % (heure*3600);
	}
	int minute = 0;
	if(seconde >= 60){
		minute = seconde / 60;
		seconde = seconde % (minute*60);
	}
	
	char* heureC = NULL;
	char* minuteC = NULL;
	char* secondeC = NULL;
	int zero=1;
	if(heure>=10) zero=0;
	heureC=intToCharEtoile(heure,zero);
	if(minute>=10) zero=0;
	minuteC=intToCharEtoile(minute,zero);
	if(seconde>=10) zero=0;
	secondeC=intToCharEtoile(seconde,zero);
	char* heureChar=(char*)malloc(50);
	sprintf(heureChar,"%s:%s:%s",heureC,minuteC,secondeC);
	return heureChar;
}

void enleverDecimale(char* tab){
	int i=0;
	while(tab[i] != '\0'){
		if(tab[i] == '.'){
			tab[i]='\0';
		}
		if(tab[i] == ','){
			tab[i]='\0';
		}
		i++;
	}
}

int decomposition(int a){
	int i=-1;
	while(a!=0){
		a=a/10;
		i++;
	}
	
	if(i==-1) i++;
	return i;
}

char* intToCharEtoile(int a,int zero){
	int degreMax=decomposition(a)+zero;
	int nombreIndex=degreMax+1;
	char* tab = (char*)malloc(sizeof(char)*nombreIndex);
	
	for(int i=0;i<=degreMax;i++){
		int puissance10=puissance(10,degreMax-i);
		tab[i]=(a/(puissance10))+48;
		a=a-((a/puissance10)*puissance10);
	}
	tab[nombreIndex]='\0';
	
	return tab;
}

int conversionEnSeconde(double a){
	float seconde=0;
	seconde=a*24*3600;
	return seconde;
}

void gestionErreur(char* tab){
	int i=0;
	while (tab[i] != '\0'){
		if ((tab[i] != '/' && tab[i] != '.' && tab[i] != ',') && (tab[i]<48 || tab[i]>57)){
			printf("Mauvais saisi !\n");
			exit(1);
		}
		i++;
	}
}

char** getChamp(char* date){
	char** champ=allouer(3,50);
	int i=0;
	while (date[i] != '/'){
		champ[0][i]=date[i];
		i++;
	}
	i++;
	int j=0;
	while (date[i] != '/'){
		champ[1][j]=date[i];
		i++;
		j++;
	}
	i++;
	int k=0;
	while (date[i] != '\0'){
		champ[2][k]=date[i];
		i++;
		k++;
	}
	
	gestionErreur(champ[0]);
	
	return champ;
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
