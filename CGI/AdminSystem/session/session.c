#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "session.h"
#include "date.c"
#include "css.c"

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

void print_line(Session session,int num,Info* info){
	printf("<TR class=\"%s\">\n",session.type);
	printf("<TD>%d</TD>\n",num);
	printf("<TD>%s</TD>\n",session.time);
	printf("<TD>%s</TD>\n",session.type);
	printf("<TD><a href=\"session.cgi?user=%s\">%s</a></TD>\n",session.user,session.user);
	printf("</TR>\n");
	(num)++;
}

Session* get_session(char* path, int* index){
	Session* sessions = calloc(NUMBER,sizeof(Session));
	FILE* file = NULL;
	file = fopen(path,"r");
	if(file == NULL){
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

Session* get_searched_user(Session* all, int all_number,char* user_to_search,int* index){
	*index = 0;
	for(int i=0 ; i<all_number ; i++){
		if(strcmp(user_to_search,all[i].user) == 0 || strcmp(user_to_search,"a0l0l") == 0){
			(*index)++;
		}
	}
	int c = 0;
	Session* searched_user = malloc((*index)*sizeof(Session));
	for(int i=0 ; i<all_number && c <= *index ; i++){
		if(strcmp(user_to_search,all[i].user) == 0 || strcmp(user_to_search,"a0l0l") == 0){
			searched_user[c] = all[i];
			c++;
		}
	}
	return searched_user;
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

void print_nav_bar(int total_number,Info* info){

	int page_n = 0;
	page_n = total_number/SHOWN;
	if(total_number%SHOWN != 0 && total_number/SHOWN != 0) page_n++;
	
	while(info->n > page_n/PAGINATION || (info->n == page_n/PAGINATION && page_n%10 == 0 && page_n != 0)) info->n--;
	
	printf("<div class=\"box_nav\">");
	
	if(strcmp(info->user,"a0l0l") != 0) printf("<a href=\"session.cgi?user=a0l0l\"><button class=\"all\">Show All</button></a>\n");

	
	if(info->n>0 && info->n<page_n/PAGINATION+1) printf("<a href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"back\">Previous</button></a><br>\n",info->user,info->p,info->n-1);
	else printf("<a href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"back\" disabled>Previous</button></a><br>\n",info->user,info->p,info->n-1);
	
	printf("<div class=\"box_num\">");
	for(int i=info->n*PAGINATION ; i<info->n*PAGINATION+PAGINATION && i<page_n ; i++){
		if(info->p == i) printf("<a  href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"actual_num\">%d</button></a>",info->user,i,i/PAGINATION,i+1);
		else printf("<a  href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"num\">%d</button></a>",info->user,i,i/PAGINATION,i+1);
	}
	printf("</div>");
	
	if(info->n < page_n/PAGINATION && (page_n % 10 != 0 || info->n != page_n/PAGINATION - 1)) printf("<a href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"next\">Next</button></a><br>\n",info->user,info->p,info->n+1);
	else printf("<a href=\"session.cgi?user=%s&p=%d&n=%d\"><button class=\"next\" disabled>Next</button></a><br>\n",info->user,info->p,info->n+1);

	printf("</div>");
}

void traitement_date(Session* sessions,int number){
	char* heure = calloc(30,sizeof(char));
	for(int i=0 ; i<number ; i++){
		int a=0, m=0, j=0;
		sscanf(sessions[i].time,"%d-%d-%d %s",&a,&m,&j,heure);
		Date d = {a,m,j};
		sprintf(sessions[i].time,"%s %02d %s %d\n%s",jour_de_la_semaine(d),j,get_mois(d),a,heure);
	}
	free(heure);
}

void to_lower_case(char* str){
	for(int i=0 ; str[i] != 0 ; i++){
		if(str[i]>='A' && str[i]<='Z') str[i]+=32;
	}
}

void print_html(){
	char* text = calloc(3000,sizeof(char));
	printf("Content-Type: text/html\n\n");
	FILE* file = fopen("./session.html","r");
		while(fgets(text,3000,file)) printf("%s",text);
	fclose(file);
	free(text);
}

int main(){
	char* url = calloc(50,sizeof(char));
	
	url = getenv("QUERY_STRING");
	
	Info* info = split_url(url);
	
	//~ if(!is_loged(info->pseudo)) printf("Location: http://www.session.mg/authentification/log_in.cgi\n\n");
	to_lower_case(info->user);
	
	char path[] = "/var/log/auth.log";
	int index = 0;
	
	Session* sessions = get_session(path,&index);
	traitement_date(sessions,index);

	printf("Content-Type: text/html\n\n");
	print_html();
	int index_final = 0;
	Session* user_sessions = get_searched_user(sessions,index,info->user,&index_final); 	// index_final -> number	
	
	while(info->p*SHOWN > index_final) info->p--;
	
	printf("<DIV class=\"title\">Auth.Log</DIV>\n");
	printf("<DIV class=\"principal_box\">\n");
	
	printf("<form method=\"get\" class=\"box\" action=\"session.cgi\">");
	printf("<div class=\"search_box\">\n");
		printf("<div class=\"input-group\">");
			printf("<input type=\"search\" class=\"form-control form-control-lg\" name=\"user\" required placeholder=\"Type your user here\">");
			printf("<div class=\"input-group-append\">");
				printf("<button type=\"submit\" class=\"btn btn-lg btn-default\">");
					printf("<i class=\"fa fa-search\"></i>");
				printf("</button>");
			printf("</div>");
		printf("</div>");
		//~ printf("<input type=\"text\" value=\"\" name=\"user\" class=\"in\" required placeholder=\"Search\">\n");
		//~ printf("<input type=\"submit\" value=\"Search\" class=\"sub\">\n");
	printf("</div>\n");
	printf("</form>\n");
	if(strcmp(info->user,"a0l0l") != 0) printf("<h1 class=\"user_searched\">%s</h1>\n",info->user);
	print_nav_bar(index_final,info);
	
	printf("<TABLE>\n");
	printf("<TR>\n");
	printf("<TD></TD>\n");
	printf("<TD>DATE</TD>\n");
	printf("<TD>SESSION</TD>\n");
	printf("<TD>USER</TD>\n");
	printf("</TR>\n");
	
	for(int i=info->p*SHOWN ; i<info->p*SHOWN+SHOWN && i<index_final ; i++) print_line(user_sessions[i],i+1,info);
	
	printf("</TABLE>\n");
	printf("</DIV>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	free(user_sessions);
	free(sessions);
	free(info);
	return 0;
}
