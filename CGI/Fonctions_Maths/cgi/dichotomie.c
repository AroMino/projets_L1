#include <math.h>
#include <stdio.h>
#include "fonctions.h"

void dichotomie(double a, double b){
	if(f(a)*f(b) > 0){
		printf("<H1 class=\"solution\">Pas de solution ou fonction non monotone entre %f et %f</H1>",a,b);
	}
	else{
		printf("<TABLE>\n");
		printf("<TR><TD colspan=\"4\">DICHOTOMIE</TD></TR>");
		printf("<TR>\n");
		printf("<TD>A</TD\n>");
		printf("<TD>MILIEU</TD\n>");
		printf("<TD>f(MILIEU)</TD\n>");
		printf("<TD>B</TD\n>");
		printf("</TR>\n");
		double solution = 1;
		while(fabs(f(b)-f(a)) > EPS){
			solution = (a+b)/2;
			printf("<TR>\n");
			printf("<TD>%f</TD\n>",a);
			printf("<TD>%f</TD\n>",solution);
			printf("<TD>%f</TD\n>",f(solution));
			printf("<TD>%f</TD\n>",b);
			printf("</TR>\n");
			if(f(solution)*f(b) <= 0){
				a=solution;
			}
			else b = solution;
		}
		printf("</TABLE>\n");
		printf("<H1 class=\"solution\">La solution est : %f</H1>",solution);
	}
}
