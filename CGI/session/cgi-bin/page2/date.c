#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Date{
	int annee;
	int mois;
	int jour;
}Date;

int diff(Date d1, Date d2){
	int diff = -d1.jour + 1;
	d1.jour = 1;
	while(d1.annee != d2.annee){
		switch(d1.mois){
			case 1: 
				diff += 31;
			case 2:
				if((d1.annee%4 == 0 && d1.annee%100 != 0) || d1.annee%400 == 0) diff+=29;
				else diff+=28;
			case 3:
				diff += 31;
			case 4:
				diff += 30;
			case 5:
				diff += 31;
			case 6:
				diff += 30;
			case 7:
				diff += 31;
			case 8:
				diff += 31;
			case 9:
				diff += 30;
			case 10:
				diff += 31;
			case 11:
				diff += 30;
			case 12:
				diff += 31;
				
		}
		d1.mois = 1;
		d1.annee++;
	}
		switch(d2.mois-1){
			case 12:
				diff += 31;
			case 11:
				diff += 30;
			case 10:
				diff += 31;
			case 9:
				diff += 30;
			case 8:
				diff += 31;
			case 7:
				diff += 31;
			case 6:
				diff += 30;
			case 5:
				diff += 31;
			case 4:
				diff += 30;
			case 3:
				diff += 31;
			case 2:
				if((d1.annee%4 == 0 && d1.annee%100 != 0) || d1.annee%400 == 0) diff+=29;
				else diff+=28;
			case 1: 
				diff += 31;
		}
	diff += d2.jour - d1.jour;
	return diff;
}

bool is_recent_than(Date d1, Date d2){
	if(d1.annee > d2.annee) return 1;
	else if(d1.annee == d2.annee && d1.mois > d2.mois) return 1;
	else if((d1.annee == d2.annee && d1.mois == d2.mois) && d1.jour > d2.jour) return 1;
	return 0;
}

char* jour_de_la_semaine(Date d){
	char* retour = calloc(20,sizeof(char));
	Date ref = {2023,01,01};
	char* list[] = {"Alahady","Alatsinainy","Talata","Alarobia","Alakamisy","Zoma","Sabotsy"};
	
	int df = 0;
	if(is_recent_than(ref,d)){
		df = diff(d,ref)%7;
		strcpy(retour,list[7-df]);
	}
	else{
		df = diff(ref,d)%7;
		strcpy(retour,list[df]);
	}
	return retour;
}

char* get_mois(Date d){
	char* mois = calloc(20,sizeof(char));
	char* list[] = {"Janoary","Febroary","Martsa","Aprily","Mey","Jona","Jolay","Aogositra","Septambra","Oktobra","Novambra","Desambra"};
	strcpy(mois,list[d.mois-1]);
	return mois;
}
