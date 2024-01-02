#include <math.h>
#include <stdio.h>
#include "newton.h"

double newton(double a, double b){
	printf("<TABLE>\n");
	printf("<TR><TD colspan=\"2\">METHODE DE NEWTON</TD></TR>");
	printf("<TR>\n");
	printf("<TD>X0</TD\n>");
	printf("<TD>f(X0)</TD\n>");
	printf("</TR>\n");
	double solution = a;
	while(fabs(f(solution))>EPS){
		Droite t = equation_de_la_tangente(solution);
		solution = -t.constante/t.coeff;
		printf("<TR>\n");
		printf("<TD>%f</TD\n>",solution);
		printf("<TD>%f</TD\n>",f(solution));
		printf("</TR>\n");
	}
	printf("</TABLE>\n");
	printf("<H1 class=\"solution\">La solution est : %f</H1>",solution);
	return solution;
}
