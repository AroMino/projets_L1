#ifndef DATE_H
#define DATE_H

typedef struct Date{
	int annee;
	int mois;
	int jour;
}Date;

char* get_mois(Date d);
char* jour_de_la_semaine(Date d);
bool is_recent_than(Date d1, Date d2);
int diff(Date d1, Date d2);

#endif
