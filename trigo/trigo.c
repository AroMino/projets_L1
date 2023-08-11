#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define START 0
#define END 360
#define pi 3.141592653565897932

void ecriture_table_trigo(FILE* file);
double deg_to_rad(int i);

int main(){
	char path[] = "/home/arrow/MIT/Programmation2/trigo/trigo.csv";
	
	FILE* file = NULL;
	file = fopen(path,"w");
	if(file == NULL){
		printf("Erreur d'ouverture !\n");
		fclose(file);
		exit(0);
	}
	ecriture_table_trigo(file);
	fclose(file);
	
	printf("Terminé avec succès\n");
	return 0;
}

void ecriture_table_trigo(FILE* file){
	double cosx = 0;
	double sinx = 0;
	double tanx = 0;
	double cotanx = 0;
	double i = 0;
	
	fprintf(file,"x cos sin tan cotan\n");
	
	for(int j=START ; j<=END ; j++){
		i = deg_to_rad(j);
		cosx = cos(i);
		sinx = sin(i);
		tanx = tan(i);
		cotanx = 1/tanx;
		fprintf(file,"%d %f %f %f %f\n",j,cosx,sinx,tanx,cotanx);
	}
	
}

double deg_to_rad(int i){
	double x = i * pi / 180;
	return x;
}
