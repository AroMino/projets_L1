#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "css.c"

bool is_loged(char* pseudo){
	FILE* file = fopen("connected","r");
	fscanf(file,"%s",pseudo);
	if(strcmp(pseudo,"") != 0) return 1;
	fclose(file);
	return 0;
}

void print_head_bar(char* pseudo){
	printf("<nav class=\"bar\">");
	printf("<h1 class=\"pseudo\">Greetings %s</h1>",pseudo);
	printf("<a href=\"http://www.session.mg/cgi-bin/log_out\" class=\"log_out\">Log out</a>");
	printf("</nav>");
}

int main(){
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
	
	printf("<BODY class=\"accueil_body\">\n");
	print_head_bar(pseudo);
		printf("<a href=\"http://www.session.mg/cgi-bin/page?user=a0l0l\" ><div id=\"p1\">My Auth.log</div></a>");
		printf("<a href=\"http://www.session.mg/cgi-bin/table_user?\" ><div id=\"p2\">My Users</div></a>");
	printf("</BODY>\n");
	printf("</HTML>\n");
	return 0;
}
