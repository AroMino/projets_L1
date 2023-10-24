#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fonctions.h"
#include "descartes.c"
#include "dichotomie.c"
#include "newton.c"

double f(double x){
	double f_x = 0.0;
	f_x = x*x - 4*x + 3;
	return f_x;
}

double derive_f_x(double x){
	double f_1_x = 2*x - 4;
	return f_1_x;
}

Droite equation_de_la_tangente(double x0){
	Droite t = {derive_f_x(x0),-derive_f_x(x0)*x0 + f(x0)};
	return t;
}

char* recherche_de_solution(double a, double b){
	char* solution = calloc(100,sizeof(char));
	
	//~ /// DICHOTOMIE
	//~ if(f(a)*f(b) > 0){
		//~ sprintf(solution,"Pas de solution ou fonction non monotone entre %f et %f",a,b);
	//~ }
	//~ else 
	//~ sprintf(solution,"La solution est %f\n",dichotomie(a,b));
	
	/// NEWTON
	sprintf(solution,"La solution est %f\n",newton(a,b));
	
	//~ /// DESCARTES
	//~ sprintf(solution,"La solution est %f\n",descartes(a,b));
	return solution;
}
