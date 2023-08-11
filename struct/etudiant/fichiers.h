#ifndef FICHIERS_H
#define FICHIERS_H 1

int get_line_number(FILE* file);
void set_line(FILE* file, char* text);
char** get_text(FILE* file);
void tri_file(char* path, int option);

#endif
