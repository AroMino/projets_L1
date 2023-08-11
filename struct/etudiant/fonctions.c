#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "var.h"

char** allouer(int ligne,int colonne){
	char **tab=NULL;
	tab=(char**)calloc(ligne,sizeof(char*));
	for(int i=0;i<ligne;i++){
		*(tab+i)=(void*)calloc(colonne,sizeof(char));
	}
	return tab;
}

char* get_path(){
	char* path = malloc(100*sizeof(char));
	printf("\nEntrez le chemin de la liste : ");
	scanf("%s",path);
	return path;
}


void afficher_text(char** text, int line){
	int i = 1;
	printf("_________________________________________________\n\n");
	while(i < line){
		printf("pc n°%d : %s",i,text[i]);
		i++;
	}
	printf("_________________________________________________\n");
}

void initialisation_etudiant(Etudiant* etudiant){
	strcpy(etudiant->noms,"");
	strcpy(etudiant->prenoms,"");
	strcpy(etudiant->contact,"");
	strcpy(etudiant->mail,"");
	strcpy(etudiant->adresse,"");
	strcpy(etudiant->date_de_naissance,"");
	strcpy(etudiant->lieu_de_naissance,"");
	strcpy(etudiant->annee_bacc,"");
	strcpy(etudiant->genre,"");
}
