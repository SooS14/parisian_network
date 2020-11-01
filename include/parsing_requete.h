#ifndef PARSING_REQUETE_H
#define PARSING_REQUETE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"


/*effectue le parsing du fichier "filein" contenant les requètes et les
stock dans tab_requete */
void parsing_requete(char *filein, Tab_requete *tab_requete);


//affiche dans le fichier "fileout" les éléments de tab_requete
void print_result_requete(Tab_requete *tab_requete, char * fileout);


//libère la mémoire allouée pour tab_requete
void free_tab_requete(Tab_requete *tab_requete);


/*trouve l'identifiant correspondant au nom donné. tab_noeud est une instance
de la structure Tab_noeud, les résultats sont renvoyés dans le tableau
resultats */
int trouve_stop_id(Tab_noeud *tab_noeud, char *stop_nom, long * resultats);


/*transforme l'heure donnée sous forme de chaine de caractère
en un nombre de seconde */
long heure_queries(char * heure);


#endif
