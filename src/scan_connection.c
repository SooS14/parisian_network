#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"
#include "scan_connection.h"



/*attention a bien prendre les tableau tps_trajet et stop_trajet assez grand !
Il servent à stocker les arrêts ateignables et leurs horaires. Leur taille
est donnés par la variable taille. tab_connection est la structure optenue
après le parsing de la table de transfert.*/
void scan_connection(long depart, long heure_depart, long *tps_trajet,long *stop_trajet, Tab_connection *tab_connection) {

  if ((tab_connection == NULL)||(stop_trajet == NULL)||(tps_trajet == NULL)){
    fputs("scan_connection : un/plusieurs des arguments est/sont null", stderr);
    exit(1);
  }

  /*initialisation (tout pt d'arrêt est à un temps infini de l'entrée,
   aucun arrêt n'est atteignable)*/
  for (long stop = 0; stop < 10000000; stop++) {
    tps_trajet[stop] = 9999999;
    stop_trajet[stop] = -1;
  }
  tps_trajet[depart] = heure_depart;

  int taille = tab_connection->taille;

  /* on parcours la structure tab_connection en actualisant les tableaux
  tps_trajet et stop_trajet. Si on trouve une connection qui améliore le temps
  de trajet alors on l'intègre dans le tableau stop_trajet */
  for (int i = 0; i < taille; i++) {
    if ((tps_trajet[tab_connection->tab[i]->stop_dep] <= tab_connection->tab[i]->tps_dep)
    && (tps_trajet[tab_connection->tab[i]->stop_arr] > tab_connection->tab[i]->tps_arr)) {
      stop_trajet[tab_connection->tab[i]->stop_arr] = tab_connection->tab[i]->stop_dep;
      tps_trajet[tab_connection->tab[i]->stop_arr] = tab_connection->tab[i]->tps_arr;
    }
  }
}



void print_scan_connection(long * tps_trajet, long * stop_trajet,char * fileout){

  FILE *out = fopen(fileout,"w");
  if (out == NULL) {
    fputs("scan_connection : out est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  for (int i = 0; i < 10000000; i++) {
    if (stop_trajet[i] != -1) {
      fprintf(out, "stop: %li ; horaire: %li\n",stop_trajet[i], tps_trajet[stop_trajet[i]]);
    }
  }
  fclose(out);
}



void free_tab_trajet(long * tps_trajet, long * stop_trajet) {
  free(tps_trajet);
  free(stop_trajet);
}
