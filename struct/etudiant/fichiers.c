#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "fonctions.h"
#include "tri.h"

int get_line_number(FILE* file){
	int i = 0;
	char* tmp = malloc(260*sizeof(char));
		while(fgets(tmp,260,file) != NULL){
		i++;
	}
	free(tmp);
	return i;
}

void set_line(FILE* file, char* text){
	fprintf(file,"%s",text);
}

char** get_text(FILE* file){
	int line = get_line_number(file);
	
	char** text = allouer(line+1,260);
	int i = 0;
	rewind(file);
	while(fgets(text[i],260,file) != NULL){
		i++;
	}
	return text;
}

void tri_file(char* path, int option){
	FILE* file = fopen(path,"r");
	if(file == NULL){
		printf("Erreur d'ouvetrure\n");
		exit(0);
	}
	int line = get_line_number(file);
	rewind(file);
	char** text = get_text(file);
	fclose(file);
	
	tri_text(text,line,option);
	
	file = fopen(path,"w");
	fprintf(file,"Noms;Prénoms;Contacts;Mails;Adresses;Dates_de_naissance;Lieux_de_naissance;Année_bacc;Genres\n");
	for(int i=1 ; i<line ; i++){
		fprintf(file,"%s",text[i]);
	}
	fclose(file);
	free(text);
}


