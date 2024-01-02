#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "dichotomie.h"
#include "newton.h"
#include "descartes.h"
#include "css.c"

double* split_url(char*url){
	double* tab = calloc(5,sizeof(double));
	if(strstr(url,"a=")) sscanf(strstr(url,"a="),"a=%lf",&tab[0]);
	if(strstr(url,"b=")) sscanf(strstr(url,"b="),"b=%lf",&tab[1]);
	if(strstr(url,"methode=")) sscanf(strstr(url,"methode="),"methode=%lf",&tab[2]);
	
	if(fabs(tab[1]) - fabs(tab[0]) < 0.0){
		double t = tab[0];
		tab[0] = tab[1];
		tab[1] = t;
	}
	
	return tab;
}
int main(){
	
	printf("Content-type: text/html \n\n");
	char* url = calloc(100,sizeof(char));
	url = getenv("QUERY_STRING");
	double* tab = split_url(url);
	char method[3][10] = {"Dichotomy","Descartes","Newton"};
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>My Fonctions</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
		print_css("./index.css");
	printf("</STYLE>");
	printf("</HEAD>\n");
	
	
	
	printf("<BODY>\n");
	printf("<FORM action=\"main.cgi\" method=\"get\" class=\"bar\">\n");
		printf("<INPUT class=\"intervalle\" type=\"number\" value=\"%d\" name=\"a\"/>",(int)tab[0]);
		printf("<INPUT class=\"intervalle\" type=\"number\" value=\"%d\" name=\"b\"/>",(int)tab[1]);
		printf("<SELECT name=\"methode\" value=\"1\">");
			printf("<OPTION value=\"1\">Dichotomy</OPTION>");
			printf("<OPTION value=\"2\">Descartes</OPTION>");
			printf("<OPTION value=\"3\">Newton</OPTION>");
		printf("</SELECT>");
		printf("<INPUT class=\"submit\" type=\"submit\" value=\"Solve\"/>");
	printf("</FORM>\n");
	
	printf("<H1 class=\"fonction\">f(x) = x² - 1 , f'(x) = 2x</H1>\n");
	printf("<H1 class=\"fonction\">Solving : x² - 1 = 0</H1>\n");
		if((int)tab[2] == 1) dichotomie(tab[0],tab[1]);
		else if((int)tab[2] == 2) descartes(tab[0],tab[1]);
		else newton(tab[0],tab[1]);
			
	printf("</BODY>\n");
	printf("</HTML>\n");
	free(tab);
	return 0;
}
