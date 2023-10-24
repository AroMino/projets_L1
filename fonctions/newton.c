#include "newton.h"

double newton(double a, double b){
	double solution = a;
	while(fabs(f(solution))>EPS){
		Droite t = equation_de_la_tangente(solution);
		solution = -t.constante/t.coeff;
	}
	return solution;
}
