#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Directive{
	char scriptalias[100];
	char directory[100];
	bool indexes;
	char options[100];
	bool followsymlinks;
	bool execCGI;
	bool script[3];
	bool allow;
	char allowoverride[100];
}Directive;

typedef struct VirtualHost{
	char servername[100];
	char serveradmin[100];
	char serveralias[100];
	char documentroot[100];
	Directive* directives;
}VirtualHost;

void dir_treatment(char* dir){
	char* tmp = calloc(100,sizeof(char));
	strcpy(tmp,dir);
	strcpy(dir,"");
	int j = 0;
	for(int i=0; tmp[i] != ' ' && tmp[i] != 0 ; i++, j++){
		if(tmp[i] == '%'){
			i+=2;
			dir[j] = '/';
		}
		else dir[j] = tmp[i];
	}
	dir[j] = 0;	
}


int* get_directives_tab(char* tmp, int directory_number){
	char* p = tmp;
	char* t = p;
	int* directive_tab = calloc(directory_number,sizeof(int));
	for(int i=0 ; i<directory_number ; i++){
		directive_tab[i] = atoi(p);
		int j=0;
		while(t[j] != '+' && t[j] != 0) j++;
		p = t+j+1;
		t = p;
	}
	return directive_tab;
}

void get_directive(char* url, Directive* directives,int* directive_tab, int i){
	char* tmp = calloc(200,sizeof(char));
	int n = directive_tab[i];
	sprintf(tmp,"directory%d=",n);
	if(strstr(url,tmp)) sscanf(strstr(url,tmp),"%*[^=]=%[^&]",directives[i].directory);
	sprintf(tmp,"scriptalias%d=",n);
	if(strstr(url,tmp)) sscanf(strstr(url,tmp),"%*[^=]=%[^&]",directives[i].scriptalias);
	free(tmp);
	
	dir_treatment(directives[i].directory);
	dir_treatment(directives[i].scriptalias);
	
	char* t1 = calloc(200,sizeof(char));
	char* t2 = calloc(200,sizeof(char));
	char* t3 = calloc(200,sizeof(char));
	char* t4 = calloc(200,sizeof(char));
	
	sprintf(t1,"indexes%d=",n);
	sprintf(t2,"followsymlinks%d=",n);
	sprintf(t3,"execcgi%d=",n);
	sprintf(t4,"allowoverride%d=",n);
	
	if(i==0){
		if(strstr(url,t1) || strstr(url,t2) || (strstr(url,t3))) sprintf(directives[i].options,"Options");
		else strcpy(directives[i].options,"");
		if(strstr(url,t1)) strcat(directives[i].options," Indexes");
		if(strstr(url,t2)) strcat(directives[i].options," FollowSymLinks");
		if(strstr(url,t3)){
			strcat(directives[i].options," ExecCGI");
		}
	}
	else{
		if(strstr(url,t1) || strstr(url,t2) || (strstr(url,t3))) sprintf(directives[i].options,"Options");
		else strcpy(directives[i].options,"");
		
		if(strcmp(directives[0].options,"") == 0){
			if(strstr(url,t1)) strcat(directives[i].options," Indexes");
			if(strstr(url,t2)) strcat(directives[i].options," FollowSymLinks");
			if(strstr(url,t3)){
				strcat(directives[i].options," ExecCGI");
			}
		}
		else{
			if(strstr(url,t1)) strcat(directives[i].options," +Indexes");
			if(strstr(url,t2)) strcat(directives[i].options," +FollowSymLinks");
			if(strstr(url,t3)){
				strcat(directives[i].options," +ExecCGI");
			}
		}
	}
	
	if(strstr(url,t4)) sprintf(directives[i].allowoverride,"AllowOverride All");
	else sprintf(directives[i].allowoverride,"AllowOverride None");
	
	free(t1);
	free(t2);
	free(t3);
	free(t4);
	
}

VirtualHost split_url(char* url){
	VirtualHost virtual;
	
	int directory_number = 0;
	sscanf(strstr(url,"tab_len="),"tab_len=%d",&directory_number);
	
	char* tmp = calloc(200,sizeof(char));
	sscanf(strstr(url,"tab="),"tab=%[^&]",tmp);
	int* directive_tab = get_directives_tab(tmp,directory_number);
	free(tmp);
	
	virtual.directives = malloc(directory_number*sizeof(Directive));
	
	/// Initialisation
	strcpy(virtual.servername,"");
	strcpy(virtual.documentroot,"");
	strcpy(virtual.serveralias,"");
	strcpy(virtual.serveradmin,"");
	
	/// Split
	sscanf(strstr(url,"documentroot="),"%*[^=]=%[^&]",virtual.documentroot);
	sscanf(strstr(url,"servername="),"%*[^=]=%[^&]",virtual.servername);
	if(strstr(url,"serveralias=")) sscanf(strstr(url,"serveralias="),"%*[^=]=%[^&]",virtual.serveralias);
	if(strstr(url,"serveradmin=")) sscanf(strstr(url,"serveradmin="),"%*[^=]=%[^&]",virtual.serveradmin);
	if(strcmp(virtual.serveradmin,"") == 0) strcpy(virtual.serveradmin,"webmaster@localhostalhost");
	dir_treatment(virtual.documentroot);
	
	strcpy(virtual.directives[0].directory,virtual.documentroot);
	for(int i=0 ; i<directory_number ; i++){
		get_directive(url,virtual.directives,directive_tab,i);
	}
	return virtual;
}

void print_directive(Directive* directives,int i,FILE* file){
	if(strcmp(directives[i].scriptalias,"") != 0){
		fprintf(file,"	ScriptAlias %s %s\n",directives[i].scriptalias,directives[i].directory);
	}
	fprintf(file,"	<Directory %s>\n",directives[i].directory);
	fprintf(file,"		%s\n",directives[i].options);
	if(strstr(directives[i].options,"ExecCGI")) fprintf(file,"		AddHandler cgi-script .cgi\n");
	fprintf(file,"		%s\n",directives[i].allowoverride);
	fprintf(file,"		Require all granted\n");
	fprintf(file,"	</Directory>\n");
}

void print_html(){
	char* text = calloc(3000,sizeof(char));
	printf("Content-Type: text/html\n\n");
	FILE* file = fopen("./back.html","r");
		while(fgets(text,3000,file)) printf("%s",text);
	fclose(file);
	free(text);
}

int main(){
	printf("Content-type: text/html\n\n");
	char* url = calloc(1000,sizeof(char));
	url = getenv("QUERY_STRING");
	VirtualHost virtual = split_url(url);
	
	int directory_number = 0;
	sscanf(strstr(url,"tab_len="),"tab_len=%d",&directory_number);
	
	char* path = calloc(200,sizeof(char));
		
	sprintf(path,"/etc/apache2/sites-available/%s.conf",virtual.servername);
	
	FILE* file = fopen(path,"w");
	fprintf(file,"<VirtualHost *:80>\n\n");
	
	fprintf(file,"	ServerName %s\n",virtual.servername);
	fprintf(file,"	ServerAdmin %s\n",virtual.serveradmin);
	
	fprintf(file,"	DocumentRoot %s\n",virtual.documentroot);
	
	for(int i=0 ; i<directory_number ; i++){
		print_directive(virtual.directives,i,file);
		//~ if(strcmp(directives[i].scriptalias,"") != 0){
		//~ fprintf(file,"	ScriptAlias %s %s\n",directives[i].scriptalias,directives[i].directory);
		//~ }
		//~ fprintf(file,"	<Directory %s>\n",directives[i].directory);
		//~ fprintf(file,"		%s\n",directives[i].options);
		//~ if(strstr(directives[i].options,"ExecCGI")) fprintf(file,"		AddHandler cgi-script .cgi\n");
		//~ fprintf(file,"		%s\n",directives[i].allowoverride);
		//~ fprintf(file,"		Require all granted\n");
		//~ fprintf(file,"	</Directory>\n");
	}
	fprintf(file,"	ErrorLog ${APACHE_LOG_DIR}/error.log\n");
	fprintf(file,"	CustomLog /etc/apache2/access/%s.log combined\n",virtual.servername);
	
	fprintf(file,"\n</VirtualHost>");
	fclose(file);
	
	print_html();
	
	printf("<div class=\"content\">");
		printf("<div class=\"head\">%s</div>",virtual.servername);
		printf("<h2>Your configuration has been successfully saved</h2>");
		printf("<h2>Tap <span>Activate</span> to activate it</h2>");
			printf("<div class=\"buttons-box\">");
				printf("<a href=\"../list/activer_desactiver.cgi?\" class=\"activate\">Activate</a>");
				printf("<a href=\"http://www.adminsystem.mg/virtual_host/list/list.cgi\">List</a>");
		printf("</div>");
	printf("</div>");
	printf("</body>");
	printf("</html>");
	return 0;
}
