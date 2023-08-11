#include "var.h"

#ifndef OPTIONS_H
#define OPTIONS_H 1

int select_option();
int select_option_modif();
int get_info(Etudiant* etudiant, int num, char* text);
void modifier_etudiant(int line, int num, char** text);
void ajouter_etudiant(FILE* file, int num);
void modifier_liste();
void creer_liste();

#endif
