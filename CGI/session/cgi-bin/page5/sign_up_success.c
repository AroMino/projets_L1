#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "css.c"

int main(){
	char* login = calloc(100,sizeof(char));
	login = getenv("QUERY_STRING");
	
	printf("Content-Type: text/html\n\n");
	printf("<HTML>\n");
	printf("<HEAD>\n");
		printf("<TITLE>Log and Sign</TITLE>\n");
		printf("<META charset=UTF-8>\n");
		printf("<STYLE>");
			print_css("./signup.css");
		printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY>\n");
	
	printf("<div class=\"success\">\n");
	printf("<H1>Account \" <span>%s</span> \" created successfully</H1>\n",login);
	printf("<div class=\"box_button\">\n");
		printf("<a href=\"http://www.session.mg/cgi-bin/log_in\">Log in</a>\n");
		printf("<a href=\"http://www.session.mg/cgi-bin/sign_up\">Back</a>\n");
	printf("</div>\n");
	printf("</div>\n");
	
	printf("</BODY>\n");
	
	printf("</HTML>\n");
	return 0;
}
