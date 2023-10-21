#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 1200
#define SHOWN 10
#define PAGINATION 10

#include "date.c"

typedef struct Info{
	int p;
	int n;
	char* user;
	int status;
	char* pseudo;
}Info;

typedef struct Session{
	char user[20];
	char type[7];
	char time[100];
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

void print_line(Session session,int num,Info* info){
	printf("<TR>\n");
	printf("<TD class=\"%s\">%d</TD>\n",session.type,num);
	printf("<TD class=\"%s\">%s</TD>\n",session.type,session.time);
	printf("<TD class=\"%s\">%s</TD>\n",session.type,session.type);
	printf("<TD class=\"%s\"><a class=\"%s\" href=\"page?user=%s&status=1&pseudo=%s\">%s</a></TD>\n",session.type,session.type,session.user,info->pseudo,session.user);
	printf("</TR>\n");
	(num)++;
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
	info->status = 0;
	
	if(*url == 0){
		info->user = url;
	}
	
	else{
		if(strstr(url,"user")){
			sscanf(strstr(url,"user"),"%*[^=]=%[^&]",info->user);
		}
		if(strstr(url,"pseudo")){
			sscanf(strstr(url,"pseudo"),"%*[^=]=%[^&]",info->pseudo);
		}
		if(strstr(url,"p=")){
			sscanf(strstr(url,"p="),"%*[^=]=%d",&info->p);
		}
		if(strstr(url,"n=")){
			sscanf(strstr(url,"n="),"%*[^=]=%d",&info->n);
		}
		if(strstr(url,"status")){
			sscanf(strstr(url,"status"),"%*[^=]=%d",&info->status);
		}
	}
	
	return info;
}

void print_link_nav(int total_number,Info* info){
	
	int page_n = 0;
	page_n = total_number/SHOWN;
	if(total_number%SHOWN != 0 && total_number/SHOWN != 0) page_n++;
	
	printf("<div class=\"box_nav\">");
	if(info->n>0 && info->n<page_n/PAGINATION+1) printf("<a href=\"/cgi-bin/page?user=%s&status=1&p=%d&n=%d&pseudo=%s\"><button class=\"back\">Back</button></a><br>\n",info->user,info->p,info->n-1,info->pseudo);
	
	printf("<div class=\"box_num\">");
	for(int i=info->n*PAGINATION ; i<info->n*PAGINATION+PAGINATION && i<page_n ; i++){
		if(info->p == i) printf("<a  href=\"/cgi-bin/page?user=%s&p=%d&status=1&n=%d&pseudo=%s\"><button class=\"actual_numero\">%d</button></a>",info->user,i,i/PAGINATION,info->pseudo,i+1);
		else printf("<a  href=\"/cgi-bin/page?user=%s&p=%d&status=1&n=%d&pseudo=%s\"><button class=\"numero\">%d</button></a>",info->user,i,i/PAGINATION,info->pseudo,i+1);
	}
	printf("</div>");
	
	if(info->n < page_n/PAGINATION && (page_n % 10 != 0 || info->n != page_n/PAGINATION - 1)) printf("<a href=\"/cgi-bin/page?user=%s&status=1&p=%d&n=%d&pseudo=%s\"><button class=\"next\">Next</button></a><br>\n",info->user,info->p,info->n+1,info->pseudo);

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

void print_side_bar(char* path,Info* info){
	printf("<nav class=\"bar\">");
	if( strcmp(info->user,"a0l0l") != 0 ) printf("<H1 class=\"file\"> %s : <span>%s</span></H1>",path,info->user);
	else printf("<H1 class=\"file\"> %s </H1>",path);
	printf("<h1 class=\"pseudo\">Greetings %s</h1>",info->pseudo);
	printf("<a href=\"http://www.session.mg\" class=\"log_out\">Log out</a>");
	printf("</nav>");
}

int main(){
	char* url = calloc(50,sizeof(char));
	url = getenv("QUERY_STRING");
	
	Info* info = split_url(url);
	if(info->status == 0) printf("Location: http://www.session.mg\n\n");
	
	to_lower_case(info->user);
	char path[] = "/var/log/auth.log";
	int index = 0;
	Session* sessions = get_session(path,&index);
	traitement_date(sessions,index);

	printf("Content-Type: text/html\n\n");
	
	int index_final = 0;
	Session* user_sessions = get_searched_user(sessions,index,info->user,&index_final); 	// index_final -> number
	
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>Sessions</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
		print_css("./index.css");
	printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY>\n");
	
	print_side_bar(path,info);
	
	
	printf("<form method=\"get\" class=\"box\" action=\"/cgi-bin/page\">");
		printf("<input type=\"text\" value=\"\" name=\"user\" class=\"in\"/>\n");
		printf("<input type=\"submit\" value=\"Search\" class=\"sub\">\n");
		printf("<input type=\"hidden\" name=\"status\" value=\"%d\">\n",info->status);
		printf("<input type=\"hidden\" name=\"pseudo\" value=\"%s\">\n",info->pseudo);
	printf("</form>\n");
	
	if(strcmp(info->user,"a0l0l") != 0) printf("<a href=\"/cgi-bin/page?user=a0l0l&status=1&pseudo=%s\"><button class=\"all\">Show All</button></a><br>\n",info->pseudo);
	
	print_link_nav(index_final,info);

	printf("<TABLE>\n");
	printf("<TR>\n");
	printf("<TD> </TD>\n");
	printf("<TD>DATE</TD>\n");
	printf("<TD>SESSION</TD>\n");
	printf("<TD>USER</TD>\n");
	printf("</TR>\n");
	
	while(info->p*SHOWN > index_final) info->p--;
	
	//~ //for(int i=0 ; i<index ; i++) print_line(sessions[i],info->user,&num);
	for(int i=info->p*SHOWN ; i<info->p*SHOWN+SHOWN && i<index_final ; i++) print_line(user_sessions[i],i+1,info);
	
	printf("</TABLE>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	free(user_sessions);
	free(sessions);
	return 0;
}
