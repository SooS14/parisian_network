#ifndef PRINT_CHEMIN_H
#define PRINT_CHEMIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"


/*affiche dans le fichier "fileout" l'heure en base 60 selon un temps donné en
seconde */
void base_heure(int n, FILE * out);


/*trouve le chemin de deb à arr en utilisant sto_trajet et le stock dans path
la fonction retourne la taille de path */
int chemin(long *sto_trajet, long *path, long arr, long deb);


/*affiche le chemin dans la sortie standard et dans le fichier "out" à partir
du tableau path en y intégrant les horaires et les numéros de ligne */
void print_chemin(long * path, long *tps_trajet, int taille,
        FILE *out, Tab_noeud *tab_noeud);


#endif
