#include <stdio.h>
#include <stdlib.h>

void getMax(int* tab,int taille,int* Max,int nbMax);
void remplirTab(int* tab,int taille);
void afficheMax(int* Max,int nbMax);

int main(){
	int taille=5;
	int nbMax=3;
	int* tab=(int*)malloc(sizeof(int)*taille);
	int* Max=(int*)malloc(sizeof(int)*nbMax);
	
	remplirTab(tab,taille);
	getMax(tab,taille,Max,nbMax);
	afficheMax(Max,nbMax);
	
	
	return 0;
}

void afficheMax(int* Max,int nbMax){
	printf("Les %d maximum(s) sont \n",nbMax);
	for (int i=0;i<nbMax;i++){
		printf("Max[%d] = %d\n",i,*(Max+i));
	}
}

void remplirTab(int* tab,int taille){
	for(int i=0;i<taille;i++){
		printf("tab[%d] = ",i);
		scanf("%d",(tab+i));
	}
}

void getMax(int* tab,int taille,int* Max,int nbMax){
	
	for(int i=0;i<nbMax;i++){
		int tmp=tab[i];
		for (int j=i;j<taille;j++){
			if(tab[j]>tmp){
				tab[i]=tab[j];
				tab[j]=tmp;
				tmp=tab[i];
			}
			Max[i]=tab[i];
		}
	}
}
