#include <math.h>
#include <stdio.h>
#include "descartes.h"

double descartes(double a, double b){
	double solution = b;
	while(fabs(f(solution)) > EPS){
		Point p1 = {a,f(a)};
		Point p2 = {solution,f(solution)};
		Droite d = equation_droite(p2,p1);
		solution = -d.constante/d.coeff;
	}
	return solution;
}

Droite equation_droite(Point a, Point b){
	double coeff = (a.y-b.y)/(a.x-b.x);
	double constante = a.y - coeff*a.x;
	Droite d = {coeff,constante};
	return d;
}
