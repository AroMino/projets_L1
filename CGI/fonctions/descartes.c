#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "descartes.h"

double descartes(double a, double b){
	double solution = b;
	while(fabs(f(solution)) > EPS){
		
		Point p1 = {a,f(a)};
		Point p2 = {b,f(b)};
		Droite d = equation_droite(p2,p1);
		printf("%f:%f et %f:%f\n",a,f(a),b,f(b));
		printf("%fx + %f\n",d.coeff,d.constante);
		solution = -d.constante/d.coeff;
		printf("solution = %lf\n",solution);
		
		if(f(solution)*f(b) <= 0) a = solution;
		else{
			if(fabs(f(a) - f(solution)) > fabs(f(b) - f(solution))) b = solution;
			else a = solution;
		}
		
		
	}
	return solution;
}

Droite equation_droite(Point a, Point b){
	double coeff = (a.y-b.y)/(a.x-b.x);
	double constante = a.y - coeff*a.x;
	Droite d = {coeff,constante};
	return d;
}
