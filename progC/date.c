#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char** allouer(int line,int col);
char** recupereChamp(char* dateBrute);
char* transformation(char* dateBrute);
int len(char* tab);
int puissance(int iva,int avo);
int repereVirgule(char* tab);
char** separer(char* tab,int positionV);
double charEtoileToDouble(char* tab);

int main(){
	char dateBrute[]="29/14/22";
	char* dateFinale=NULL;
	dateFinale=transformation(dateBrute);
	printf("%s",dateFinale);
	return 0;
}

void traitementMoisEtAnnee(double* dateTraite){
	int increAnnee = 0;
	int resteMois = 0;
	
	if((int)dateTraite[1] > 12){
		increAnnee = dateTraite[1] / 12;
		resteMois = (int)dateTraite[1] % 12;
		dateTraite[2] += increAnnee;
		dateTraite[1] = resteMois + (dateTraite[1] - (int)dateTraite[1]);
	}
	else if((int)dateTraite[1]<1){
		increAnnee = dateTraite[1] / 12;
		resteMois = (int)dateTraite[1] % 12;
		dateTraite[2] += increAnnee - 1;
		dateTraite[1] = resteMois + 12 + (dateTraite[1] - (int)dateTraite[1]);
	}
}

void traitementJoursEtMois(double* dateTraite){
	int nbJoursMois[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(((int)dateTraite[2]%4)==0) nbJoursMois[2]=29;
	
		int indexMois=(int)dateTraite[1];
		dateTraite[0] = dateTraite[0] + ((dateTraite[1] - (int)dateTraite[1])*nbJoursMois[indexMois]);
		dateTraite[1] = (int)dateTraite[1];
		if ((int)dateTraite[0]>0){
		while((int)dateTraite[0]>nbJoursMois[indexMois]){
			dateTraite[0] -= nbJoursMois[indexMois];
			dateTraite[1] +=1;
			traitementMoisEtAnnee(dateTraite);
			indexMois=(int)dateTraite[1];
		}
	}
	while((int)dateTraite[0]<1){
		dateTraite[1] -=1;
		if (dateTraite[1] == 0){
			dateTraite[1] = 12;
			dateTraite[2] --;
		}
		indexMois=(int)dateTraite[1];
		dateTraite[0] += nbJoursMois[indexMois];
	}
}

double* traitementDate(double* date){
	double* dateTraite = (double*)malloc(3*sizeof(double));
	dateTraite[2] = (int)date[2];
	dateTraite[1] = ((date[2] - (int)date[2])*12) + date[1];
	dateTraite[0] = date[0];
	
	traitementMoisEtAnnee(dateTraite);
	traitementJoursEtMois(dateTraite);
	
	return dateTraite;
}

double doubleJourToSeconde(double jourDouble){
	double seconde = jourDouble*3600*24;
	return seconde;
}

void conversionHMS (int* heure){
	if(heure[2] >= 3600){
		heure[0] = heure[2]/3600;
		heure[2] =heure[2] % (heure[0]*3600);
	}

	if(heure[2] >= 60){
		heure[1]= heure[2] / 60;
		heure[2] = heure[2] % (heure[1]*60);
	}
}

int* traitementHeure(double jour){
	int* heure = (int*)malloc(3*sizeof(int));
	heure[2] = doubleJourToSeconde(jour-(int)jour);
	
	conversionHMS(heure);
	return heure;
}

char* transformation(char* dateBrute){
	char* dateFinale=malloc(50*sizeof(char));
	
	char** champ=NULL;
	champ=recupereChamp(dateBrute);
	
	double date[3];
	date[0] = charEtoileToDouble(champ[0]);
	date[1] = charEtoileToDouble(champ[1]);
	date[2] = charEtoileToDouble(champ[2]);
	
	double* dateTraite=traitementDate(date);
	int* heure = traitementHeure(dateTraite[0]);
	dateTraite[0] = (int)dateTraite[0];
	
	int jour = dateTraite[0];
	int mois = dateTraite[1];
	int annee = dateTraite[2];
	
	int h = heure[0];
	int m = heure[1];
	int s = heure[2];
	
	sprintf(dateFinale,"%02d/%02d/%02d %02d:%02d:%02d",jour,mois,annee,h,m,s);
	return dateFinale;
}

int mijerySigne(char* nombreChar){
	int signe=0;
	if(nombreChar[0]=='-') signe=1;
	
	return signe;
}

int charEtoileToInt(char* nombreT){
	int nb=0;
	int longueur=0;
	
	longueur=len(nombreT);
	int signe=mijerySigne(nombreT);
	
	for (int i=longueur-1,j=0 ; i>=0+signe ; i--,j++){
		int x=nombreT[i]-48;
		int puissance10 = puissance(10,j);
		x*=puissance10;
		nb=nb+x;
	}
	
	if(signe==1) nb*=-1;
	
	return nb;
}

double charEtoileToDouble(char* tab){
	double nombre=0;
	
	int positionVirgule = positionVirgule=repereVirgule(tab);
	char** nombresT = separer(tab,positionVirgule);
	int entiere=charEtoileToInt(nombresT[0]);
	
	int signe = mijerySigne(nombresT[0]);
	if(signe==1) entiere*=-1;
	
	int decimale=charEtoileToInt(nombresT[1]);
	int lenDecimale=len(nombresT[1]);
	
	double flottante = decimale*pow(10,-lenDecimale);
	nombre=entiere+flottante;
	free(nombresT);
	
	if (signe==1) nombre*=-1;
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
	
	/*if(nbVirgule>1){
		printf("Mauvais saisi !\n");
		exit(1);
	}*/
	
	if(indexV<1) return i;
	else return indexV;
}


char** recupereChamp(char* dateBrute){
	char** champ=allouer(3,10);
	int i=0;
	while (dateBrute[i] != '/'){
		champ[0][i]=dateBrute[i];
		i++;
	}
	i++;
	int j=0;
	while (dateBrute[i] != '/'){
		champ[1][j]=dateBrute[i];
		i++;
		j++;
	}
	i++;
	int k=0;
	while (dateBrute[i] != '\0'){
		champ[2][k]=dateBrute[i];
		i++;
		k++;
	}
	
	return champ;
}

char** allouer(int line,int col){
	char** tab=(char**)malloc(line*sizeof(char*));
	
	for (int i=0; i<line ; i++){
		*(tab+i)=(char*)malloc(col*sizeof(char));
	}
	return tab;
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

char** separer(char* tab,int positionV){

	char** nombresT=allouer(2,10);
	
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
