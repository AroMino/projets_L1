#include <stdio.h>
#include <stdlib.h>

void print_html(){
	char* text = calloc(3000,sizeof(char));
	printf("Content-Type: text/html\n\n");
	FILE* file = fopen("./accueil.html","r");
		while(fgets(text,3000,file)) printf("%s",text);
	fclose(file);
	free(text);
}

int main(){
	print_html();
	return 0;
}
