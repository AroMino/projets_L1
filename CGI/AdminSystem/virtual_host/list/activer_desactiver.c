#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void desactiver(char* nom){
	char* cmd = calloc(200,sizeof(char));
	sprintf(cmd,"a2dissite %s",nom);
	FILE* file = popen(cmd,"r");
	pclose(file);
	free(cmd);
}

void activer(char* nom){
	char* cmd = calloc(200,sizeof(char));
	sprintf(cmd,"a2ensite %s",nom);
	FILE* file = popen(cmd,"r");
	pclose(file);
	free(cmd);
}

int main(){
	char* url = calloc(500,sizeof(char));
	url = getenv("QUERY_STRING");
	int status = 0;
	char* nom = calloc(100,sizeof(char));
	sscanf(url,"%[^=]",nom);
	sscanf(url,"%*[^=]=%d",&status);	
	
	if(status) activer(nom);
	else desactiver(nom);
	system("sudo systemctl reload apache2");
	printf("Location: http://www.adminsystem.mg/virtual_host/list/list.cgi\n\n");
	
	return 0;
}
