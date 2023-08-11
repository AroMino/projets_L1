#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "var.h"
#include "fonctions.h"
#include "tri.h"
#include "fichiers.h"


int select_option(){
	int option = 0;
	printf(" (1) : Créer une liste\n");
	printf(" (2) : Modifier une liste\n\n");
	printf(" ====>   ");
	scanf("%d",&option);
	
	return option;
}

int select_option_modif(){
	int option = 0;
	printf("\n");
	printf(" (1) : Ajouter\n");
	printf(" (2) : Supprimer\n");
	printf(" (3) : Modifier \n\n");
	printf(" ====>   ");
	scanf("%d",&option);
	return option;
}

int get_info(Etudiant* etudiant, int num, char* text){
	
	initialisation_etudiant(etudiant);
	
	char c = 0;
	while((c = getchar()) != EOF && c != '\n');
	
	printf("\nEtudiant n°%d :\n",num);
	
	printf("Noms : ");
	scanf("%[^\n]",etudiant->noms);
	if(*(etudiant->noms) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	
	printf("Prenoms : ");
	scanf("%[^\n]",etudiant->prenoms);
	if(*(etudiant->prenoms) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
		
	printf("Contact : ");
	scanf("%[^\n]",etudiant->contact);
	if(*(etudiant->contact) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Mail : ");
	scanf("%[^\n]",etudiant->mail);
	if(*(etudiant->mail) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Adresse : ");
	scanf("%[^\n]",etudiant->adresse);
	if(*(etudiant->adresse) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Date_de_naissance : ");
	scanf("%[^\n]",etudiant->date_de_naissance);
	if(*(etudiant->date_de_naissance) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Lieu_de_naissance : ");
	scanf("%[^\n]",etudiant->lieu_de_naissance);
	if(*(etudiant->lieu_de_naissance) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Annee_bacc : ");
	scanf("%[^\n]",etudiant->annee_bacc);
	if(*(etudiant->annee_bacc) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Genre : ");
	scanf("%[^\n]",etudiant->genre);
	if(*(etudiant->genre) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Numéro CIN : ");
	scanf("%[^\n]",etudiant->cin);
	if(*(etudiant->cin) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
	
	printf("Compte GIT : ");
	scanf("%[^\n]",etudiant->git);
	if(*(etudiant->git) == '*') return 0;
	
	while((c = getchar()) != EOF && c != '\n');
		
	sprintf(text,"%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n",etudiant->noms,etudiant->prenoms,etudiant->contact,etudiant->mail,etudiant->adresse,etudiant->date_de_naissance,etudiant->lieu_de_naissance,etudiant->annee_bacc,etudiant->genre,etudiant->cin,etudiant->git);
	return 1;
}

void modifier_etudiant(int line, int num, char** text){
	printf("\nétudiant n°%d : %s",num,text[num]);
	Etudiant etudiant;
	get_info(&etudiant,num,text[num]);
	char c = 0;
	while((c = getchar()) != EOF && c != '\n');
}

void ajouter_etudiant(FILE* file, int num){
	Etudiant etudiant;
	int run = 1;
	char* text = malloc(130*sizeof(char));
	char s = 0;
	char c = 0;
	while(run){
		system("clear");
		printf("AJOUT D'ETUDIANTS\n\n");
		
		rewind(file);
		char** tab = get_text(file);
		
		tri_text(tab,num,TRI);
		
		afficher_text(tab,num);
		
		if((run = get_info(&etudiant,num,text)) == 0){
			break;
		}
		
		set_line(file,text);
		num++;
		
		while((c = getchar()) != EOF && c != '\n');
		s = getchar();
		if(s == '0'){
			run = 0;
		}
		else run = 1;
		
		free(tab);
	}
	free(text);
}

void modifier_liste(){
	ici:
	char* path = get_path();
	
	FILE* file = fopen(path,"r");
	if(file == NULL){
		printf("\nListe introuvable\n");
		char c = 100;
		while((c = getchar()) != EOF && c != '\n');
		getchar();
		goto ici;
	}
	fclose(file);
		
	int option = select_option_modif();
	
	if(option == 1){
		tri_file(path, TRI);
		file = fopen(path,"a+");
		int num = get_line_number(file);
		ajouter_etudiant(file, num);
		fclose(file);
		tri_file(path, TRI);
	}
	else if(option == 2){
		tri_file(path, TRI);
		int r = 1;
		while(r > 0){
			system("clear");
			FILE* file = fopen(path,"r+");
			if(file == NULL){
				printf("Liste introuvable\n");
				goto ici;
			}
			int line = get_line_number(file);
			rewind(file);
			char** text = get_text(file);
			tri_text(text,line,TRI);
			afficher_text(text,line);
			fclose(file);
			
			if(line>1){
				printf("\nEntrez le numéro de l'étudiant à supprimer : ");
				scanf("%d",&r);
			
				if(r>0){
					file = fopen(path,"w");
					strcpy(text[r],"");
					for(int i=r ; i<line-1 ; i++){
						strcpy(text[i],text[i+1]);
					}
					set_line(file,"Noms;Prénoms;Contacts;Mails;Adresses;Dates_de_naissance;Lieux_de_naissance;Année_bacc;Genres;CIN;Git\n");
					for(int i=1 ; i<line-1 ; i++){
						set_line(file,text[i]);
					}
					fclose(file);
				}
				free(text);
			}
			else{
				system("clear");
				printf("\nLa liste %s est vide\n",path);
				char c = getchar();
				r = 0;
			}
		}
		tri_file(path, TRI);
	}
	else if(option == 3){
		tri_file(path, TRI);
		int r = 1;
		while(r > 0){
			system("clear");
			FILE* file = fopen(path,"r+");
			if(file == NULL){
				printf("Liste introuvable\n");
				goto ici;
			}
			int line = get_line_number(file);
			rewind(file);
			char** text = get_text(file);
			tri_text(text,line,TRI);
			afficher_text(text,line);
			fclose(file);
			
			if(line>1){
				printf("\nEntrez le numéro de l'etudiant à modifier : ");
				scanf("%d",&r);
			
			
				if(r>0){
					modifier_etudiant(line,r,text);
					
					file = fopen(path,"w");
					set_line(file,"Noms;Prénoms;Contacts;Mails;Adresses;Dates_de_naissance;Lieux_de_naissance;Année_bacc;Genres;CIN;Git\n");
					for(int i=1 ; i<line ; i++){
						set_line(file,text[i]);
					}
					fclose(file);
				}
				free(text);
			}
			else{
				system("clear");
				printf("\nLa liste %s est vide\n",path);
				char c = getchar();
				r = 0;
			}
			tri_file(path, TRI);
		}
		
	}
}

void creer_liste(){
	char* path = get_path();
	FILE* file = fopen(path,"w+");
	fprintf(file,"Noms;Prénoms;Contacts;Mails;Adresses;Dates_de_naissance;Lieux_de_naissance;Année_bacc;Genres;CIN;Git\n");
	ajouter_etudiant(file, 1);
	fclose(file);
	tri_file(path,TRI);
}
