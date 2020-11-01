#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include "parsing_stops.h"




void parsing_stops(char *filein, Tab_noeud *tab_noeud){

  if (tab_noeud == NULL) {
    fputs("parsing_stops : tab_noeud est null",stderr);
    exit(1);
  }

  FILE *in = fopen(filein,"r");
  if (in == NULL) {
    fputs("parsing_stops : in est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  char buffer[1000];
  int count = 0;

  //on saute le titre
  fseek(in,33,SEEK_SET);

  //tant que fgets le permet on parcours le fichier
  while (fgets(buffer,1000,in)) {

    /*gros problème de cette methode si le curseur de queries.txt est sur
    une nouvelle ligne la chaine "buffer" est VIDE !! */
    if (strcmp(buffer,"\n") == 0) {
      break;
    }

    //on supprime le \n de buffer
    int fin = 0;
    while (buffer[fin] != '\n') {
      fin = fin + 1;
    }
    buffer[fin] = '\0';

    Noeud *noeud = malloc(sizeof(*noeud));
    if (noeud == NULL) {
      fputs("parsing_stops : noeud est null, erreur allocation",stderr);
      exit(1);
    }

    //utilisation de strtok :
    //le premier appel permet de récupérer l'identifiant de l'arrêt
    char * token = strtok(buffer,",");
    sscanf(buffer,"%li,",&(noeud->stop_id));

    //le second appel permet de récupérer le nom de l'arrêt
    token = strtok(NULL,",");
    strcpy(noeud->nom,token);

    //on récupère la ligne avec un troisième appel
    token = strtok(NULL,",");
    strcpy(noeud->ligne_id,token);

    //on stock chaque arret dans tab_arret1
    tab_noeud->tab[count] = noeud;
    count = count + 1;
  }
  tab_noeud->taille = count;
  fclose(in);
}




void print_result_stops(Tab_noeud *tab_noeud, char * fileout){
  if (tab_noeud == NULL) {
    fputs("parsing_stops : tab_noeud est null",stderr);
    exit(1);
  }
  FILE *out = fopen(fileout,"w");
  if (out == NULL) {
    fputs("parsing_stops : out est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  for (int i = 0; i < tab_noeud->taille; i++) {
    fprintf(out, "%li,", tab_noeud->tab[i]->stop_id);
    fprintf(out, "%s\n", tab_noeud->tab[i]->nom);
  }
  fclose(out);
}




void free_tab_noeud(Tab_noeud *tab_noeud) {
  if (tab_noeud == NULL) {
    fputs("parsing_stops : tab_noeud est null",stderr);
    exit(1);
  }
  //on libère la mémoire de occupée par chaque noeud
  for (int i = 0; i < tab_noeud->taille; i++) {
    Noeud * point = tab_noeud->tab[i];
    if (point == NULL) {
      fputs("parsing_stops : point est null, erreur allocation",stderr);
      exit(1);
    }
    free(point);
  }
  free(tab_noeud);
}
