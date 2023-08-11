#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* inverserTab(char* tab);
char* generateur(int coeff,int puissance,char* tab);
char* translate(char* nombre);
char* genererBase(char* partie0);
char* genererMillion(char* partie1);
char* genererMilliard(char* partie2);

int main(){
	char isa[100];
	FILE* file = fopen("/home/arrow/manisa.txt","w");
	
	for (int i = 1000000000 ; i<100010000 ; i++){
		sprintf(isa,"%d",i);
		char* soratra = translate(isa);
		fprintf(file,"%s : %s\n",isa,soratra);
		free(soratra);
	}
	fclose(file);
	return 0;
}

char* inverserTab(char* tab){
	int len = strlen(tab);
	char* bat = (char*)calloc(len,len*sizeof(char));
	
	for(int i=0;i<len;i++){
		bat[i]=tab[len-i-1];
	}
	return bat;
}

char** allouer(int line,int col){
	char** tab=(char**)malloc(line*sizeof(char*));
	
	for (int i=0; i<line ; i++){
		*(tab+i)=(char*)malloc(col*sizeof(char));
	}
	return tab;
}

void manalaCaractere(char* tab){
	for (int i=0 ; i<strlen(tab) ;i++){
		if((tab[i]<'0' || tab[i]>'9')){
			tab[i] = '\0';
		}
	}
}

char** getPartie(char* nombreInverse){
	char** partie = allouer (3,35);
	
	for(int i=0 ; i<6 ; i++){
		partie[0][i] = nombreInverse[i];
	}
	for(int i=0 ,j=6 ; j<9 ; i++,j++){
		partie[1][i] = nombreInverse[j];
	}
	
	if (strlen(nombreInverse)<6){
		strcpy(partie[1],"");
	}
	manalaCaractere(partie[1]);
	
	
	strcpy(partie[2],"");
	int i=9;
	int j=0;
	while(nombreInverse[i] != '\0'){
		partie[2][j] = nombreInverse[i];
		i++; 
		j++;
	}
	if (strlen(nombreInverse)<9){
		strcpy(partie[2],"");
	}
	manalaCaractere(partie[2]);
	
	
	return partie;
}

void manambatra(char* soratra, char* tab1, char* tab2, char* tab3){
	int a = strlen(tab1);
	int b = strlen(tab2);
	int c = strlen(tab3);
	
	if(a>2 && b>2 && c>2){
		sprintf(soratra,"%s sy %s sy %s", tab1,tab2,tab3);
	}
	if(a>2 && b>2 && c<=2){
		sprintf(soratra,"%s sy %s",tab1,tab2);
	}
	if(a>2 && b<=2 && c>2){
		sprintf(soratra,"%s sy %s",tab1,tab3);
	}
	if(a>2 && b<=2 && c<=2){
		sprintf(soratra,"%s",tab1);
	}
	
	if(a<=2 && b>2 && c>2){
		sprintf(soratra,"%s sy %s",tab2,tab3);
	}
	if(a<=2 && b>2 && c<=2){
		sprintf(soratra,"%s",tab2);
	}
	if(a<=2 && b<=2 && c>2){
		sprintf(soratra,"%s",tab3);
	}
	if(a<=2 && b<=2 && c<=2){
		sprintf(soratra," ");
	}
}

char* translate(char* nombre){
	
	char* nombreInverse = inverserTab(nombre);
	char** partie = getPartie(nombreInverse);
	char* partieBase = genererBase(partie[0]);
	char* partieMillion = genererMillion(partie[1]);
	
	
	char* partieMilliard = genererMilliard(partie[2]);
	
	int len = strlen(partieBase) + strlen(partieMillion) + strlen(partieMilliard);
	char* soratra = (char*)calloc(len,len*sizeof(char));
	
	manambatra(soratra,partieBase,partieMillion,partieMilliard);
	
	free(partieBase);
	free(partieMillion);
	free(partieMilliard);
	free(partie);
	free(nombreInverse);
	
	int lenSoratra = strlen(soratra);
	if(lenSoratra<2) sprintf(soratra,"aotra");
	
	return soratra;
}

char* genererMillion(char* partie1){
	
	int len = strlen(partie1);
	char* partieMillion = calloc(len*50,(len*50)*sizeof(char));
	char* baseMillion = calloc(len*50,(len*50)*sizeof(char));
	baseMillion = genererBase(partie1);
	
	if(strlen(partie1) != 0 && strcmp(partie1,"000")!=0){
		sprintf(partieMillion,"%s tapitrisa",baseMillion);
	}
	else{
		sprintf(partieMillion," ");
	}
	
	return partieMillion;
}

char* genererMilliard(char* partie2){
	
	int len = strlen(partie2);
	char* partieMilliard = calloc(len*60,(len*60)*sizeof(char));
	char* baseMilliard = calloc(len*50,(len*50)*sizeof(char));
	
	if(len <= 6){
		baseMilliard = genererBase(partie2);
	}
	else if(len> 6){
		char* sous_partie2 = inverserTab(partie2);
		baseMilliard = translate(sous_partie2);
		
	}
	
	int detecteur = 0;
	for(int i=0; i<strlen(partie2); i++){
		if(partie2[i] != '0'){
			detecteur = 1;
		}
	}
	
	if(strlen(partie2) != 0 && detecteur !=0){
		sprintf(partieMilliard,"%s lavitrisa",baseMilliard);
	}
	else{
		sprintf(partieMilliard," ");
	}
	
	return partieMilliard;
}

char* genererBase(char* partie0){
	
	int len = strlen(partie0);
	char* partieBase = calloc(len*40,(len*40)*sizeof(char));
	
	for (int i=0 ; i<len ; i++){
		int coeff = partie0[i] - 48;
		char* retour = generateur (coeff,i,partie0);
		strcat(partieBase,retour);
		free(retour);
	}
	
	return partieBase;
}

char* generateur(int coeff,int puissance,char* tab){
	char* retour = (char*)calloc(40,40*sizeof(char));
	char coefficient[11][10] = {{""},{"iray"},{"roa"},{"telo"},{"efatra"},{"dimy"},{"enina"},{"fito"},{"valo"},{"sivy"}};
	char unite[11][10] = {{""},{"polo"},{"njato"},{" arivo"},{" alina"},{" hetsy"}};
	char mpanohy[20] = " sy ";
	
	/// CONDITIONS MPANOHY
	if(puissance == 1){
		if (coeff == 1){
			strcpy(mpanohy," ambin'ny ");
		}
		else{
			strcpy(mpanohy," amby ");
		}
	}
	if(puissance == 2){
			strcpy(mpanohy," amby ");
	}
	
	int detecteur = 0;
	for (int i=0 ; i<puissance ; i++){
		if (tab[i] != '0'){
			detecteur++;
		}
	}
	
	if (detecteur == 0){
		strcpy(mpanohy,"");
	}
	if(coeff == 0){
		puissance = 0;
	}
	if (puissance == 0){
		strcpy(mpanohy,"");
	}
	
	/// CONDITIONS PUISSANCES ET COEFF
	
	if(coeff == 1 && (puissance == 2 || puissance == 3)){
		strcpy(unite[2],"zato");
		strcpy(unite[3],"arivo");
		strcpy(coefficient[1],"");
	}
	if((coeff == 5 ||coeff == 6 ||coeff == 4) && (puissance == 1 ||puissance == 2)){
		strcpy(coefficient[4],"efa");
		strcpy(coefficient[5],"dima");
		strcpy(coefficient[6],"eni");
	}
	if((coeff == 4) && (puissance == 2)){
		strcpy(coefficient[4],"efa");
		strcpy(unite[2],"jato");
	}
	
	if((coeff == 6) && puissance == 1){
		strcpy(coefficient[6],"enim");
	}
	if((coeff == 6) && puissance == 2){
		strcpy(coefficient[6],"enin");
	}
	if(coeff == 9 && (puissance == 1 ||puissance == 2)){
		strcpy(unite[1],"folo");
		strcpy(coefficient[9],"sivi");
	}
	if(coeff == 1 && puissance == 2){
		strcpy(unite[2],"zato");
		strcpy(coefficient[1],"");
	}
	if(coeff == 1 && puissance == 1){
		strcpy(unite[1],"folo");
		strcpy(coefficient[1],"");
	}
	
	sprintf(retour,"%s%s%s",mpanohy,coefficient[coeff],unite[puissance]);
	return retour;
}
