#ifndef STATISTIQUES_H

#define STATISTIQUES_H

#define NUMBER 1200
#define SHOWN 10
#define PAGINATION 10

typedef struct Access{
	char ip[20];
	char type[300];
	char time[100];
}Access;

typedef struct Info{
	int p;
	int n;
	char* site;
	char* pseudo;
}Info;

#endif
