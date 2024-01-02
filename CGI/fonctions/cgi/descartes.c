#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "descartes.h"

double descartes(double a, double b){
	printf("<TABLE>\n");
	printf("<TR><TD colspan=\"4\">METHODE DE DESCARTES</TD></TR>");
	printf("<TR>\n");
	printf("<TD>A</TD\n>");
	printf("<TD>X0</TD\n>");
	printf("<TD>f(X0)</TD\n>");
	printf("<TD>B</TD\n>");
	printf("</TR>\n");
	double solution = b;
	while(fabs(f(solution)) > EPS){
		
		Point p1 = {a,f(a)};
		Point p2 = {b,f(b)};
		Droite d = equation_droite(p2,p1);
		solution = -d.constante/d.coeff;
		
		printf("<TR>\n");
		printf("<TD>%f</TD\n>",a);
		printf("<TD>%f</TD\n>",solution);
		printf("<TD>%f</TD\n>",f(solution));
		printf("<TD>%f</TD\n>",b);
		printf("</TR>\n");
		
		if(f(solution)*f(b) <= 0) a = solution;
		else{
			if(fabs(f(a) - f(solution)) > fabs(f(b) - f(solution))) b = solution;
			else a = solution;
		}
	}
	printf("</TABLE>\n");
	printf("<H1 class=\"solution\">La solution est : %f</H1>",solution);
	return solution;
}

Droite equation_droite(Point a, Point b){
	double coeff = (a.y-b.y)/(a.x-b.x);
	double constante = a.y - coeff*a.x;
	Droite d = {coeff,constante};
	return d;
}
