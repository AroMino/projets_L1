#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "create.h"

int main(){
	char* login = calloc(100,sizeof(char));
	char* password = calloc(100,sizeof(char));
	char* error = calloc(100,sizeof(char));
	char* url = getenv("QUERY_STRING");
	sscanf(url,"%*[^=]=%[^&]&%*[^=]=%s",login,password);
	
	if(analyse_login(login,error)){
		FILE* file = fopen("log.txt","a");
		fprintf(file,"%s %s\n",login,password);
		fclose(file);
		printf("Location: http://www.session.mg/cgi-bin/sign_up_success?%s\n\n",login);
	}
	
	free(login);
	free(password);
	printf("Location: http://www.session.mg/cgi-bin/sign_up?error_sign_up=%s\n\n",error);
	
	return 0;
}

bool analyse_login(char* log, char* error){
	FILE* file = fopen("log.txt","r");
	char* l = calloc(100,sizeof(char));
	char* line = calloc(100,sizeof(char));
	
	while(fscanf(file,"%[^\n]\n",line) == 1){
		sscanf(line,"%s %*[^\n]",l);
		if(strcmp(log,l) == 0){
			sprintf(error,"Login_existant&last_login=%s",log);
			return 0;
		}
	}
	
	if(isdigit(log[0]) || ispunct(log[0])){
		sprintf(error,"Login_invalide");
		return 0;
	}
	
	free(l);
	free(line);
	fclose(file);
	return 1;
}
