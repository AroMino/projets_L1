#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "statistics.h"

Access get_info_access(char* text){
	Access access;
	
	// IP
	sscanf(text,"%s",access.ip);
	
	// TYPE
	//~ sscanf(text,"%*[^]]] %[^\n]",access.type);	
	sscanf(text,"%[^\n]",access.type);
	
	// TIME
	sscanf(text,"%*[^[][%[^]]",access.time);
	
	return access;
}

Access* get_access(char* path, int* index_final){
	char* cmd = calloc(300,sizeof(char));
	sprintf(cmd,"wc -l %s",path);
	
	int number = 0;
	FILE* file = popen(cmd,"r");
		fscanf(file,"%d",&number);
	pclose(file);
	*index_final = number;
	
	char* text = calloc(1000,sizeof(char));
	file = fopen(path,"r");
	if(file == NULL){
		return NULL;
	}
	int i = 0;
	
	Access* access = calloc(number,sizeof(Access));
		while(fgets(text,1000,file)){
			if(strcmp(text,"") != 0){
				*(access+i) = get_info_access(text);
				i++;
			}
		}
		
	fclose(file);
	free(cmd);
	return access;
}

Info* split_url(char* url){
	Info* info = malloc(sizeof(Info));
	info->site = calloc(100,sizeof(char));
	info->pseudo = calloc(100,sizeof(char));
	info->p = 0;
	info->n = 0;
	
	if(*url == 0){
		info->site = url;
	}
	
	else{
		if(strstr(url,"site=")){
			sscanf(strstr(url,"site="),"%*[^=]=%[^&]",info->site);
		}
		if(strstr(url,"p=")){
			sscanf(strstr(url,"p="),"%*[^=]=%d",&info->p);
		}
		if(strstr(url,"n=")){
			sscanf(strstr(url,"n="),"%*[^=]=%d",&info->n);
		}
	}
	
	return info;
}

void print_nav_bar(int total_number,Info* info){
	int page_n = 0;
	page_n = total_number/SHOWN;
	if(total_number%SHOWN != 0 && total_number/SHOWN != 0) page_n++;
	
	while(info->n > page_n/PAGINATION || (info->n == page_n/PAGINATION && page_n%10 == 0 && page_n != 0)) info->n--;
	
	printf("<div class=\"box_nav\">");
	if(info->n>0 && info->n<page_n/PAGINATION+1) printf("<a href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"back\">Previous</button></a><br>\n",info->site,info->p,info->n-1);
	else printf("<a href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"back\" disabled>Previous</button></a><br>\n",info->site,info->p,info->n-1);
	
	printf("<div class=\"box_num\">");
	for(int i=info->n*PAGINATION ; i<info->n*PAGINATION+PAGINATION && i<page_n ; i++){
		if(info->p == i) printf("<a  href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"actual_num\">%d</button></a>",info->site,i,i/PAGINATION,i+1);
		else printf("<a  href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"num\">%d</button></a>",info->site,i,i/PAGINATION,i+1);
	}
	printf("</div>");
	
	if(info->n < page_n/PAGINATION && (page_n % 10 != 0 || info->n != page_n/PAGINATION - 1)) printf("<a href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"next\">Next</button></a><br>\n",info->site,info->p,info->n+1);
	else printf("<a href=\"statistics.cgi?site=%s&p=%d&n=%d\"><button class=\"next\" disabled>Next</button></a><br>\n",info->site,info->p,info->n+1);
	
	printf("</div>");
}

void print_line(Access access, int num, Info* info){
	printf("<TR>\n");
	printf("<TD class=\"\">%d</TD>\n",num);
	printf("<TD class=\"\">%s</TD>\n",access.ip);
	printf("<TD class=\"\">%s</TD>\n",access.time);
	printf("<TD class=\"\">%s</TD>\n",access.type);
	printf("</TR>\n");
}

void print_html(){
	char* text = calloc(3000,sizeof(char));
	FILE* file = fopen("./statistics.html","r");
		while(fgets(text,3000,file)) printf("%s",text);
	fclose(file);
	free(text);
}

void name_treatment(char* name){
	name[strlen(name)-1] = 0;
}

void print_list(char* actual_site){
	FILE* file = popen("ls /etc/apache2/sites-available","r");
	char* text = calloc(100,sizeof(char));
	bool is_site = 0;
	printf("<DIV class=\"box_list\">\n");
		while(fgets(text,100,file)){
			name_treatment(text);
			if(strcmp(actual_site,text) == 0){
				printf("<a class=\"lien\" href=\"statistics.cgi?site=%s\"><div class=\"actual_site\">%s.Log</div></a>",text,text);
				is_site = 1;
			}
			else printf("<a class=\"lien\" href=\"statistics.cgi?site=%s\"><div class=\"site\">%s.Log</div></a>",text,text);
		}
	printf("</DIV>\n");
	
	if(is_site) printf("<H1 class=\"site_title\">%s</H1>",actual_site);

	pclose(file);
	free(text);
}

int main(){
	printf("Content-Type: text/html\n\n");
	char* url = calloc(50,sizeof(char));
	
	url = getenv("QUERY_STRING");
	
	Info* info = split_url(url);
	//~ strcpy(info->site,"cv.conf");
	char* path = calloc(200,sizeof(char));
	sprintf(path,"/etc/apache2/access/%s.log",info->site);
	
	int index_final = 0;

	Access* access = get_access(path,&index_final);
	
	
	print_html();
	
	printf("<DIV class=\"title\">VirtualHosts</DIV>");
	printf("<DIV class=\"principal_box\">\n");
	
	
	
	print_list(info->site);
	
	if(index_final != 0){
	
		print_nav_bar(index_final,info);
		while(info->p*SHOWN > index_final) info->p--;	
		
		
		printf("<TABLE>\n");
		
			printf("<TR>\n");
			printf("<TD></TD>\n");
			printf("<TD>Adresse IP</TD>\n");
			printf("<TD>Time</TD>\n");
			printf("<TD>Details</TD>\n");
			printf("</TR>\n");
			
			for(int i=info->p*SHOWN ; i<info->p*SHOWN+SHOWN && i<index_final ; i++) print_line(access[i],i+1,info);
			
		printf("</TABLE>\n");
	}
	
	printf("</DIV>\n");
	
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	free(path);
	return 0;
}
