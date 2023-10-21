#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 1000

typedef struct Info{
	int p;
	char* user;
}Info;

typedef struct Session{
	char user[20];
	char type[7];
	char time[35];
}Session;

Session get_info_session(char* text){
	Session session;		
	// USER
	char* s = NULL;
	s = strstr(text,"session opened for user ");			// strlen session opened for user 24
	if(s == NULL) s = strstr(text,"session closed for user ");
	
	s += 24;
	int index = 0;
	while(s[index] != '(' && s[index] != ' '){
		session.user[index] = s[index];
		index++;
	}
	session.user[index] = 0;
	
	int i = 0;
	while(i<strlen(session.user)){
		if(session.user[i] == 10 || session.user[i] == 1) session.user[i] = 0;
		i++;
	}
	
	// TYPE
	if(strstr(text,"session opened for user ")) strcpy(session.type,"opened");
	else strcpy(session.type,"closed");
	
	
	// TIME
	snprintf(session.time,33,"%s",text);
	for(int i=0 ; i<33 ; i++){
		if(session.time[i] == 'T') session.time[i] = ' ';
	}
	
	return session;
}

void print_line(Session session,int* num){
	printf("<TR>\n");
	printf("<TD>%d</TD>\n",*num);
	printf("<TD>%s</TD>\n",session.time);
	printf("<TD class=\"%s\">%s</TD>\n",session.type,session.type);
	if(strcmp(session.user,"root") == 0) printf("<TD><a class=\"root\" href=\"page?user=%s\">%s</a></TD>\n",session.user,session.user);
	else printf("<TD><a href=\"page?user=%s\">%s</a></TD>\n",session.user,session.user);
	printf("</TR>\n");
	(*num)++;

}

Session* get_session(char* path, int* index){
	Session* sessions = calloc(NUMBER,sizeof(Session));
	FILE* file = NULL;
	file = fopen(path,"r+");
	if(file == NULL){
		printf("Erreur d'ouverture !\n");
		fclose(file);
		exit(0);
	}
	int line = 0;
	char* text = calloc(256,sizeof(char));
	
	while(fscanf(file,"%[^\n]\n",text) == 1) line++;
	
	int line_start = 0;

	line_start = (line - NUMBER > 0) 
		? line - NUMBER 
		: 0;
		
	rewind(file);
	line = 0;
	while(fscanf(file,"%[^\n]\n",text) == 1){
		if(line >= line_start){
			if((strstr(text,"session opened for user")) != NULL || 
			(strstr(text,"session closed for user")) != NULL){
				sessions[*index] = get_info_session(text);
				(*index)++;
			}
		}
		line++;
	}
	free(text);
	return sessions;
}

void print_css(char* path){
	FILE* file = fopen(path,"r");
	char* text = calloc(257,sizeof(char));
	while(fgets(text,256,file) != NULL){
		printf("%s",text);
	}
	fclose(file);
}

Session* get_searched_user(Session* all, int all_number,char* user_to_search,int* index){
	*index = 0;
	for(int i=0 ; i<all_number ; i++){
		if(strcmp(user_to_search,all[i].user) == 0 || *user_to_search == 0){
			(*index)++;
		}
	}
	int c = 0;
	Session* searched_user = malloc((*index)*sizeof(Session));
	for(int i=0 ; i<all_number && c <= *index ; i++){
		if(strcmp(user_to_search,all[i].user) == 0 || *user_to_search == 0){
			searched_user[c] = all[i];
			c++;
		}
	}
	return searched_user;
}

Info* split_url(char* url){
	Info* info = malloc(sizeof(Info));
	
	if(*url == 0){
		info->user = url;
	}
	else info->user = url+5;
	
	return info;
}



int main(){
	char* url = calloc(50,sizeof(char));
	url = getenv("QUERY_STRING");
	
	Info* info = split_url(url);
	
	char path[] = "/var/log/auth.log";
	int index = 0;
	Session* sessions = get_session(path,&index);

	printf("Content-Type: text/html\n\n");
	
	
	
	int index_final = 0;
	Session* user_sessions = get_searched_user(sessions,index,info->user,&index_final);
	
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>Sessions</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
		print_css("./index.css");
	printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY>\n");
	printf("<H1> /var/log/auth.log </H1><BR>");
	
	printf("<form method=\"get\" class=\"box\" action=\"/cgi-bin/page\">");
		printf("<input type=\"text\" value=\"\" name=\"user\" class=\"in\"/>\n");
		printf("<input type=\"submit\" value=\"Search\" class=\"sub\">\n");
	printf("</form>\n");
	
	if((*info->user) != 0) printf("<h2 class=\"Corr\">Correspondence to \"<span>%s</span>\"</h2>",info->user);
	printf("<TABLE>\n");
	printf("<TR>\n");
	printf("<TD> </TD>\n");
	printf("<TD>DATE</TD>\n");
	printf("<TD>TYPE</TD>\n");
	printf("<TD>USERS</TD>\n");
	printf("</TR>\n");
	
	int num = 1;
	//~ for(int i=0 ; i<index ; i++) print_line(sessions[i],info->user,&num);
	for(int i=0 ; i<index_final ; i++) print_line(user_sessions[i],&num);
	
	printf("</TABLE>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	free(user_sessions);
	free(sessions);
	return 0;
}
