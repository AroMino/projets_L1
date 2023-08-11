#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "var.h"

int main(){
	int option = select_option();
	switch(option){
		case 0:
		return 0;
		
		case 1:
			creer_liste();
		break;
		
		case 2:
			modifier_liste();
		break;
		
		default:
		return 0;
		
	}

	return 0;
}


