#ifndef PAGE_H
#define PAGE_H 1

#define NUMBER 1200
#define SHOWN 10
#define PAGINATION 10

typedef struct Info{
	int p;
	int n;
	char* user;
	char* pseudo;
}Info;

typedef struct Session{
	char user[20];
	char type[7];
	char time[100];
}Session;

#endif
