#ifndef PARSE_STOPS_H
#define PARSE_STOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"


/*effectue le parsing du fichier "filein" dans lequel sont donnés les
noms des arrêts de métro et les stocks dans tab_noeud */
void parsing_stops(char *filein, Tab_noeud *tab_noeud);


//affiche ce que contient tab_noeud dans le fichier "fileout"
void print_result_stops(Tab_noeud *tab_noeud, char * fileout);


//libère la mémoire allouée pour le tab_noeud
void free_tab_noeud(Tab_noeud *tab_noeud);


#endif
