#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "css.c"

void split_url(char* url, char* error_sign_up){
	if(strstr(url,"error_sign_up")){
			sscanf(strstr(url,"error_sign_up"),"%*[^=]=%[^&]",error_sign_up);
	}
}

int main(){
	
	char* url = calloc(50,sizeof(char));
	char* last_login = calloc(50,sizeof(char));
	char* error_sign_up = calloc(50,sizeof(char));
	url = getenv("QUERY_STRING");
	
	split_url(url,error_sign_up);
	if(strstr(url,"last_login=")){
		sscanf(strstr(url,"last_login="),"%*[^=]=%[^&]",last_login);
	}
	
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
	printf("<div class=\"box\">\n");
	printf("<div class=\"box_log\">\n");
			printf("<h1>Welcome !</h1>");
			printf("<h2>Already have an account ?</h2>");
			printf("<a href=\"http://www.session.mg/cgi-bin/log_in\">Log in</a>");
	printf("</div>\n");
		printf("<form action=\"/cgi-bin/create\" method=\"get\" class=\"box_sign_up\">\n");
			printf("<h1>Sign up</h1>");
			printf("<input type=\"text\" value=\"%s\" name=\"login\" placeholder=\"Login\" required>\n",last_login);
			printf("<input type=\"password\" name=\"pass\" placeholder=\"Password\" required>\n");
			printf("<span>%s</span>",error_sign_up);
			printf("<button type=\"submit\">Create</button>\n");
		printf("</form>\n");
		
	printf("</div>\n");
	printf("</BODY>\n");
	
	printf("</HTML>\n");
	return 0;
}
