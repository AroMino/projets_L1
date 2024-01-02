#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "log.c"

int main(){
	char* login = calloc(100,sizeof(char));
	char* password = calloc(100,sizeof(char));
	char* url = getenv("QUERY_STRING");
	sscanf(url,"%*[^=]=%[^&]&%*[^=]=%s",login,password);
	
	if(log_in(login,password) == CORRECT){
		FILE* file = NULL;
		file = fopen("./connected","w");
		if(file == NULL) {
			return 0;
		}
		fprintf(file,"%s",login);
		fclose(file);
		//~ printf("Location: http://www.session.mg/cgi-bin/page?&user=a0l0l\n\n");file:///home/arrow/MIT/Programmation2/CGI/session/log_in.c
		printf("Location: http://www.adminsystem.mg/accueil/accueil.cgi\n\n");
		
	}
	else {
		printf("Location: http://www.adminsystem.mg/authentification/log_in.cgi?error_log_in=Incorrect_password_or_inexistant_login&login=%s\n\n",login);
	}
	
	free(login);
	free(password);
	return 0;
}
