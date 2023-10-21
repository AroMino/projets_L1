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
		printf("Location: http://www.session.mg/cgi-bin/page?&user=a0l0l\n\n");
		fclose(file);
	}
	else {
		printf("Location: http://www.session.mg/cgi-bin/log_in?error_log_in=Incorrect_password_or_inexistant_login&login=%s\n\n",login);
	}
	
	free(login);
	free(password);
	return 0;
}
