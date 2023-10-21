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

void log_out(){
	FILE* file = fopen("connected","w");
	fprintf(file,"\n");
	fclose(file);
}
