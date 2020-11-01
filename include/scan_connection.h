#ifndef SCAN_CONNEXION_H
#define SCAN_CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"


/*lance l'algorithme de scan de connection sur la table horaire stockée dans
tab_connection avec tps_trajet et sto_trajet deux tableaux vides de tailles
importantes*/
void scan_connection(long dep, long h_dep,
            long * tps_trajet,
            long * sto_trajet,
            Tab_connection *tab_connection);


/*affiche le contenu des tableaux stop_trajet et tps_trajet dans le fichier
"fileout" */
void print_scan_connection(long * tps_trajet,
            long * stop_trajet,
            char * fileout);


//libère la mémoire réservée aux tableaux tps_trajet et stop_trajet
void free_tab_trajet(long * tps_trajet, long * stop_trajet);


#endif
