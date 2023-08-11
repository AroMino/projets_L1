#!/bin/bash

gcc -c options.c
gcc -c fonctions.c
gcc -c fichiers.c
gcc -c tri.c

ar rcs bib.a options.o fonctions.o fichiers.o tri.o

gcc -o etudiant etudiant.c bib.a

#Effacer les fichiers génerés par la compilation
rm -r *.o *.a
