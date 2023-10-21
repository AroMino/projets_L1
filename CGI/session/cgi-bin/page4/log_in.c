#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_out(){
	FILE* file = fopen("connected","w");
	fprintf(file,"\n");
	fclose(file);
}

void print_css(char* path){
	FILE* file = fopen(path,"r");
	char* text = calloc(257,sizeof(char));
	while(fgets(text,256,file) != NULL){
		printf("%s",text);
	}
	fclose(file);
}

void split_url(char* url, char* error_log_in){
	if(strstr(url,"error_log_in")){
		sscanf(strstr(url,"error_log_in"),"%*[^=]=%[^&]",error_log_in);
	}
}

int main(){
	log_out();
	
	char* url = calloc(50,sizeof(char));
	char* last_login = calloc(50,sizeof(char));
	char* error_log_in = calloc(50,sizeof(char));
	url = getenv("QUERY_STRING");
	
	split_url(url,error_log_in);
	if(strstr(url,"login=")){
		sscanf(strstr(url,"login="),"%*[^=]=%[^&]",last_login);
	}
	
	printf("Content-Type: text/html\n\n");
	printf("<HTML>\n");
	printf("<HEAD>\n");
		printf("<TITLE>Log and Sign</TITLE>\n");
		printf("<META charset=UTF-8>\n");
		printf("<STYLE>");
			print_css("./login.css");
		printf("</STYLE>");
	printf("</HEAD>\n");
	
	printf("<BODY>\n");
	printf("<div class=\"box\">\n");
		printf("<form action=\"/cgi-bin/log\" method=\"get\" class=\"box_log_in\">\n");
		printf("<h1>Login</h1>");
			printf("<input type=\"text\" value=\"%s\" name=\"login\" placeholder=\"Login\" required>\n",last_login);
			printf("<input type=\"password\" name=\"pass\" placeholder=\"Password\" required>\n");
			printf("<span>%s</span>",error_log_in);
			printf("<button type=\"submit\">Connect</button>\n");
		printf("</form>\n");
		printf("<div class=\"box_sign\">\n");
			printf("<h1>Welcome !</h1>");
			printf("<h2>Don't have an account ?</h2>");
			printf("<a href=\"http://www.session.mg/cgi-bin/sign_up\">Sign up</a>");
		printf("</div>\n");
	printf("</div>\n");
	
	printf("</BODY>\n");
	
	printf("</HTML>\n");
	return 0;
}
