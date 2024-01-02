#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

Site* get_sites_available(int* number){
	FILE* file = popen("ls /etc/apache2/sites-available | wc -l","r");
	int line = 0;
	fscanf(file,"%d",&line);
	
	*number = line;
	
	char* nom = calloc(100,sizeof(char));
	
	file = popen("ls /etc/apache2/sites-available","r");
	Site* sites = calloc(line,sizeof(Site));
	
	int index = 0;
	while(fgets(nom,100,file)){
		strcpy(sites[index].nom,nom);
		index++;
	}
	pclose(file);
	
	for(int i=0 ; i<*number; i++){
		sites[i].status = 0;
	}
	
	return sites;
}

void get_sites_status(Site* sites, int number){
	char* nom = calloc(100,sizeof(char));
	
	FILE* file = popen("ls /etc/apache2/sites-enabled","r");
	
	while(fgets(nom,100,file)){
		for(int i=0 ; i<number; i++){
			if(strcmp(sites[i].nom,nom) == 0){
				sites[i].status = 1;
				break;
			}
		}
	}
	pclose(file);
}

void name_treatment(char* name){
	name[strlen(name)-1] = 0;
}

void print_sites(Site* sites, int number){
	printf("<TR>\n");
	printf("<TD>Name</TD>");
	printf("<TD>Status</TD>");
	printf("<TD>Statistics</TD>");
	printf("</TR>\n");

	for(int i=0 ; i<number ; i++){
		name_treatment(sites[i].nom);
		if(sites[i].status) printf("<TR class=\"active\">\n");
		else printf("<TR class=\"notactive\">\n");
			printf("<TD>%s</TD>",sites[i].nom);
			if(sites[i].status){
				printf("<TD><a href=\"activer_desactiver.cgi?%s=0\">Active</a></TD>",sites[i].nom);
				printf("<TD><a href=\"../statistics/statistics.cgi?site=%s\">%s.Log</a></TD>",sites[i].nom,sites[i].nom);
			}
			else{
				printf("<TD ><a href=\"activer_desactiver.cgi?%s=1\">Not Active</a></TD>",sites[i].nom);
				printf("<TD ><a href=\"../statistics/statistics.cgi?site=%s\">%s.Log</a></TD>",sites[i].nom,sites[i].nom);
			}
			
		printf("</TR>\n");
	}
}

void print_html(){
	char* text = calloc(3000,sizeof(char));
	printf("Content-Type: text/html\n\n");
	FILE* file = fopen("./list.html","r");
		while(fgets(text,3000,file)) printf("%s",text);
	fclose(file);
	free(text);
}

int main(){
	int number = 0;
	Site* sites = get_sites_available(&number);
	get_sites_status(sites,number);
	print_html();
	printf("<DIV class=\"title\">VirtualHosts</DIV>\n");
	printf("<DIV class=\"table_box\">\n");
		printf("<TABLE>\n");
		print_sites(sites,number);
		printf("</TABLE>\n");
	printf("</DIV>\n");
	printf("</BODY>\n");
	printf("</HTML>\n");
	return 0;
}
