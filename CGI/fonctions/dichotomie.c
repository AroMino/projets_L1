#include <math.h>
#include "fonctions.h"

double dichotomie(double a, double b){
	double solution = 1;
	while(fabs(f(b)-f(a)) > EPS){
		solution = (a+b)/2;
		if(f(solution)*f(b) <= 0){
			a=solution;
		}
		else b = solution;
		
	}
	return solution;
}
