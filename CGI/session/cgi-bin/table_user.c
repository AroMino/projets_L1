#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "page.h"
#include "css.c"

#define ID_MIN 1000
#define ID_MAX 6000

char** allouer(int ligne,int colonne){
	char **tab=NULL;
	tab=(char**)calloc(ligne,sizeof(char*));
	for(int i=0;i<ligne;i++){
		*(tab+i)=(void*)calloc(colonne,sizeof(char));
	}
	return tab;
}

char* get_champ(char* text, int number, char separateur){
	int index = 0;
	int i = 0;
	while(index<strlen(text) && i<number){
		if (text[index] == separateur) i++;
		index++;
	}
	
	int j = index;
	while(j<strlen(text) && text[j] != separateur) j++;
	
	int lenght_champ = j-index;
	
	
	char* tab = calloc(lenght_champ,sizeof(char));
	strncat(tab,text+index,lenght_champ);
	if(tab[strlen(tab)-1] == 10) tab[strlen(tab)-1] = 0;
	return tab;
}

int get_id(char* user){
	int id = atoi(get_champ(user,2,':'));
	return id;
}

char** analyse_user(char** text, int* nombre){
	
	int id = 0;
	int j = 0;
	for(int i=0 ; i<*nombre ; i++){
		id = get_id(text[i]);
		if(id >= ID_MIN && id < ID_MAX){
			j++;
		}
	}
	char** user = allouer(j,256);
	
	j=0;
	for(int i=0 ; i<*nombre ; i++){
		id = get_id(text[i]);
		if(id >= ID_MIN && id < ID_MAX){
			strcpy(user[j],text[i]);
			j++;
		}
	}
	*nombre = j;
	free(text);
	return user;
}

char* gen_mail(char* login){
	char* mail = calloc(strlen(login)+7,sizeof(char));
	sprintf(mail,"%s@mit.mg",login);
	return mail;
}

char** get_user(char* path, int* nombre){
	char** text = allouer(100,257);
	
	FILE* file = NULL;
	file = fopen(path,"r");
	if(file == NULL){
		printf("Erreur d'ouverture !\n");
		fclose(file);
		exit(0);
	}
	int ligne = 0;
	while(fgets(text[ligne],256,file) != NULL){
		ligne++;
	}
	fclose(file);
	
	char** human_user = analyse_user(text,&ligne);
	*nombre = ligne;
	
	return human_user;
}

char* gen_mdp(int len, char* car){
	char* mdp = calloc(len,sizeof(char));
	int index = 0;
	
	for(int i=0 ; i<len ; i++){
		index = rand()%61;
		mdp[i] = car[index];
	}
	return mdp;
}

void print_line(char* login,char* dir,char* shell,char* mail){
	printf("<TR>\n");
	printf("<TD>%s</TD>\n",login);
	printf("<TD>%s</TD>\n",dir);
	printf("<TD>%s</TD>\n",mail);
	printf("<TD>%s</TD>\n",shell);
	printf("</TR>\n");
}

void print_head_bar(char* path,char* pseudo){
	printf("<nav class=\"bar\">");
	printf("<H1 class=\"file\"> %s </H1>",path);
	printf("<h1 class=\"pseudo\">Greetings %s</h1>",pseudo);
	printf("<a href=\"http://www.session.mg/cgi-bin/log_out\" class=\"log_out\">Log out</a>");
	printf("</nav>");
}

Info* split_url(char* url){
	Info* info = malloc(sizeof(Info));
	info->user = calloc(100,sizeof(char));
	info->pseudo = calloc(100,sizeof(char));
	info->p = 0;
	info->n = 0;
	
	if(*url == 0){
		info->user = url;
	}
	
	else{
		if(strstr(url,"user")){
			sscanf(strstr(url,"user"),"%*[^=]=%[^&]",info->user);
		}
		if(strstr(url,"p=")){
			sscanf(strstr(url,"p="),"%*[^=]=%d",&info->p);
		}
		if(strstr(url,"n=")){
			sscanf(strstr(url,"n="),"%*[^=]=%d",&info->n);
		}
	}
	
	return info;
}

bool is_loged(char* pseudo){
	FILE* file = fopen("connected","r");
	fscanf(file,"%s",pseudo);
	if(strcmp(pseudo,"") != 0) return 1;
	fclose(file);
	return 0;
}

int main(){
	char path[] = "/etc/passwd";
	int nombre = 0;
	char** human_user = get_user(path,&nombre);
	char* pseudo = calloc(100,sizeof(char));
	
	if(!is_loged(pseudo)) printf("Location: http://www.session.mg/cgi-bin/log_in\n\n");
	
	printf("Content-Type: text/html\n\n");
	
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>User Info</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
		print_css("./index.css");
	printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY class=\"user_body\">\n");
	
		printf("<svg class=\"waves\" width=\"100%%\" height=\"150%%\" viewBox=\"0 0 1000 1000\" xmlns=\"http://www.w3.org/2000/svg\" preserveAspectRatio=\"none\" overflow=\"auto\" shape-rendering=\"auto\" fill=\"#fdf6e3\">"
        "<defs>"
         "<path id=\"wavepath\" d=\"M 0 2000 0 500 Q 114 394 228 500 t 228 0 228 0 228 0 228 0 228 0 228 0  v1000 z\" />"
         "<path id=\"motionpath\" d=\"M -456 0 0 0\" />" 
        "</defs>"
        "<g>"
         "<use xlink:href=\"#wavepath\" y=\"-411\" fill=\"#D46F4D\">"
         "<animateMotion"
          "dur=\"5s\""
          "repeatCount=\"indefinite\">"
          "<mpath xlink:href=\"#motionpath\"/>"
         "</animateMotion>"
         "</use>"
        "</g>"
      "</svg>");
	
		print_head_bar(path,pseudo);
	
	printf("<H1> Liste des utilisateurs du système </H1><BR>");
	printf("<TABLE class=\"user_table\">\n");
	printf("<TR>\n");
	printf("<TD>USERS</TD>\n");
	printf("<TD>DIRECTORIES</TD>\n");
	printf("<TD>EMAILS</TD>\n");
	printf("<TD>SHELLS</TD>\n");
	printf("</TR>\n");
	
	for(int i=0 ; i<nombre ; i++){
		char* login = NULL;
		char* dir = NULL;
		char* shell = NULL;
		char* mail = NULL;
		
		login = get_champ(human_user[i],0,':');
		dir = get_champ(human_user[i],5,':');
		shell = get_champ(human_user[i],6,':');
		mail = gen_mail(login);
		print_line(login,dir,shell,mail);
		
		free(login);
		free(dir);
		free(shell);
		free(mail);
	}
	printf("</TABLE>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	free(human_user);
	free(pseudo);
	return 0;
}



