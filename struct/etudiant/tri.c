#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fonctions.h"


void find_separator(char* tab, char sep, int* first, int* last){
	*first = 0;
	while(tab[*first] != sep){
		(*first)++;
	}
	
	*last = ++(*first);
	
	while(tab[*last] != sep && *last != strlen(tab)){
		(*last)++;
	}
	
}

int* split_number(char** tab, int line){
	int* num = calloc(line,sizeof(int));
	char* tmp = calloc(260,sizeof(char));
	int first = 0, next = 0;
	
	for(int i=1 ; i<line ; i++){
		first = 0; next = 0;
		find_separator(tab[i],';',&first,&next);
		strncat(tmp,tab[i]+first,next - first);
		num[i] = atoi(tmp);
		strcpy(tmp,"");
	}
	free(tmp);
	return num;
}

void tri_text(char** tab, int nombre, int option){
	char* tmp = calloc(250,sizeof(char));
	switch(option){
		case 1:
		int k = 0;
			for(int i=1 ; i<nombre ; i++){
				for(int j=i+1 ; j<nombre ; j++){
					k=0;
					while(tab[j][k]==tab[i][k]){
						k++;
					}
					if(tab[j][k]<tab[i][k]){
						strcpy(tmp,tab[j]);
						strcpy(tab[j],tab[i]);
						strcpy(tab[i],tmp);
						continue;
					}
				}
			}
		break;
		
		case 2:
		int* num = split_number(tab,nombre);
		int t = 0;
			for(int i=1 ; i<nombre ; i++){
				for(int j=i+1 ; j<nombre ; j++){
					if(num[j]<num[i]){
						t = num[i];
						num[i] = num[j];
						num[j] = t;
						strcpy(tmp,tab[j]);
						strcpy(tab[j],tab[i]);
						strcpy(tab[i],tmp);
						continue;
					}
				}
			}
		free(num);
	}
	free(tmp);
}

