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

int main(){
	char* login = calloc(100,sizeof(char));
	char* password = calloc(100,sizeof(char));
	char* url = getenv("QUERY_STRING");
	sscanf(url,"%*[^=]=%[^&]&%*[^=]=%s",login,password);
	if(log_in(login,password) == CORRECT){
		printf("Location: http://www.session.mg/cgi-bin/page?status=1&user=a0l0l\n\n");
	}
	else {
		printf("Location: http://www.session.mg\n\n");
	}
	
	free(login);
	free(password);
	return 0;
}
