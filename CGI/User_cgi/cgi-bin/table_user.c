#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
	char path[] = "/etc/passwd";
	int nombre = 0;
	char** human_user = get_user(path,&nombre);
	
	printf("Content-Type: text/html\n\n");
	
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>User Info</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
	printf("table{margin:0 0 0 50px;width:80vw;}\n");
	printf("td{border-style:solid;text-align:center;padding:5px 10px 5px 10px;}\n");
	printf("h1{margin:0 0 0 10px;}\n");
	printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY>\n");
	printf("<H1> Liste des utilisateurs du système </H1><BR>");
	printf("<TABLE>\n");
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
	return 0;
}



