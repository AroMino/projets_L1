#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fonctions.h"
#include "descartes.h"
#include "dichotomie.h"
#include "newton.h"
#include "integrale.h"

double f(double x){
	double f_x = 0.0;
	f_x = x*x - 1;
	return f_x;
}

double derive_f_x(double x){
	double f_1_x = 2*x;
	return f_1_x;
}

Droite equation_de_la_tangente(double x0){
	Droite t = {derive_f_x(x0),-derive_f_x(x0)*x0 + f(x0)};
	return t;
}

char* recherche_de_solution(double a, double b, int methode){
	char* solution = calloc(100,sizeof(char));
	double s = 0.0;
	
	sprintf(solution,"Pas de solution ou fonction non monotone entre %f et %f",a,b);
	if(methode == 1){
		/// DICHOTOMIE
		if(f(a)*f(b) > 0){
			sprintf(solution,"Pas de solution ou fonction non monotone entre %f et %f",a,b);
		}
		else sprintf(solution,"La solution est %f\n",dichotomie(a,b));
	}
	
	else if(methode == 2){
		/// NEWTON
		s = newton(a,b);
		if(s >= a && s <= b)sprintf(solution,"La solution est %f\n",s);
	}
	
	else{
		/// DESCARTES
		s = descartes(a,b);
		if(s >= a && s <= b) sprintf(solution,"La solution est %f\n",s);
	}
	return solution;
}
