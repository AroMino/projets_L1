#ifndef FONCTIONS_H
#define FONCTIONS_H 1

#define EPS 0.000001

typedef struct Point{
	double x;
	double y;
}Point;

typedef struct Droite{
	double coeff;
	double constante;
}Droite;

double f(double x);
double derive_f_x(double x);
Droite equation_de_la_tangente(double x0);
char* recherche_de_solution(double a, double b, int methode);

#endif
