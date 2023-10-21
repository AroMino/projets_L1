#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generer_mdp(int len, char* car);

int main(){
	srand(time(NULL));
	char car[61] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
	char* mdp = generer_mdp(8,car);
	printf("%s\n",mdp);
	free(mdp);
}

char* generer_mdp(int len, char* car){
	char* mdp = calloc(len,sizeof(char));
	int index = 0;
	
	for(int i=0 ; i<len ; i++){
		index = rand()%61;
		mdp[i] = car[index];
	}
	return mdp;
}
