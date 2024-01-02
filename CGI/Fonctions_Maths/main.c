#include <stdio.h>

#include "fonctions.h"

int main(){
	printf("Dichotomie : %s\n",recherche_de_solution(-20,20,1));
	printf("Newton : %s\n",recherche_de_solution(-20,20,2));
	//~ printf("Dscartes : %s\n",recherche_de_solution(-4,5,3));
	
	return 0;
}
