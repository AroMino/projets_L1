#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "log.h"

bool log_in(char* login, char* pass){
	FILE* file = fopen("./log.txt","r");
	if(file == NULL){ 
		printf("<h1>Erreur d'ouverture</h1>");
		exit(1);
	}
	char* line = calloc(257,sizeof(char));
	char* l = calloc(100,sizeof(char));
	char* p = calloc(100,sizeof(char));
	
	while(fgets(line,256,file) != NULL){
		sscanf(line,"%s %s",l,p);
		if(strcmp(login,l) == 0 && strcmp(pass,p) == 0) return CORRECT;
	}
	free(line);
	free(l);
	free(p);
	return INCORRECT;
}

bool is_loged(char* pseudo){
	FILE* file = fopen("./authentification/connected","r");
	fscanf(file,"%s",pseudo);
	if(strcmp(pseudo,"") != 0) return 1;
	fclose(file);
	return 0;
}

bool is_admin(char* pseudo){
	FILE* file = fopen("./admin","r");
	char* text = calloc(100,sizeof(char));
		while(fgets(text,100,file)){
			if(strcmp(text,pseudo) == 0) return 1;
		}
	free(text);
	fclose(file);
	return 0;
}

void log_out(){
	FILE* file = fopen("./connected","w");
	fprintf(file,"\n");
	fclose(file);
}
