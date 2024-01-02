#include "fonctions.h"
#include "integrale.h"

double integrale(double a, double b){
	double pr = 0;
	double intervalle = 0.0001;
	for(double i=a ; i<b ; i+=intervalle){
		pr+= f(i)*(intervalle); // rectangle
		//~ pr+= f(i)*(intervalle) + (f(i+intervalle)-f(i))*(intervalle)/2; // trapèze
	}
	return pr;
}
