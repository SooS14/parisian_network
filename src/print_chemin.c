#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include "types.h"
#include "print_chemin.h"



void base_heure(int n, FILE * out){
  int r = n;
  fprintf(out,"heure : ");
  /*à chaque boucle on écrit dans le fichier "out" le reste de la division
  par 60 */
  for (int i = 2; i >= 0; i--) {
    int p = pow(60,i);
    r = n / p;
    n = n % p;
    fprintf(out, "%i", r);
    if (i != 0) {
      fprintf(out,":");
    }
  }
  fprintf(out,"\n");
}



int chemin(long *stop_trajet, long *path, long arrivee, long debut){
  long actuel = arrivee;
  int i = 1;
  path[0] = actuel;
  /*la boucle parcours le tableau stop_trajet (qui contient le prédécesseur de 
  chaque arrêt) en sens inverse */
  while (actuel != debut) {
    if (actuel != -1) {
      printf("%li\n", actuel);
      actuel = stop_trajet[actuel];
      path[i] = actuel;
      i = i + 1;
    } else {
      printf("pas de chemin\n");
      return i;
    }
  }
  printf("%li\n", debut);
  return i;
}



void print_chemin(long * path, long *tps_trajet ,
   int taille, FILE *out, Tab_noeud *tab_noeud){

     for (int i = taille; i >= 0; i--) {
       for (int j = 0; j < tab_noeud->taille; j++) {
         if (tab_noeud->tab[j]->stop_id == path[i]) {
           fprintf(out, "%s ; stop: %s ; ", tab_noeud->tab[j]->ligne_id, tab_noeud->tab[j]->nom);
           base_heure(tps_trajet[path[i]],out);
         }
       }
     }
     fprintf(out, "\n");
     fprintf(out, "\n");

   }
