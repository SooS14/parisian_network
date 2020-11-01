#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parsing_requete.h"



void parsing_requete(char *filein, Tab_requete *tab_requete){

  if (tab_requete == NULL) {
    fputs("parsing_queries : tab_requete est null",stderr);
    exit(1);
  }
  
  tab_requete->taille = 0;

  FILE *in = fopen(filein,"r");
  if (in == NULL) {
    fputs("parsing_queries : in est null, erreur ouverture fichier",stderr);
    exit(1);
  }


  char buffer[1000];
  int count = 0;

  //on saute le titre
  fseek(in,51,SEEK_SET);

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

    //la requete suivante est créée
    Requete *requete = malloc(sizeof(*requete));
    if (requete == NULL) {
      fputs("parsing_requete : requete est null, erreur allocation",stderr);
      exit(1);
    }


    //utilisation de strtok :
    char * token = strtok(buffer,",");
    strcpy(requete->depart, token);
    token = strtok(NULL,",");
    strcpy(requete->arrivee,token);
    token = strtok(NULL,",");
    strcpy(requete->jour,token);
    token = strtok(NULL,",");
    strcpy(requete->heure,token);

    //on stock chaque requete dans tab_requete
    tab_requete->tab[count] = requete;
    count = count + 1;
  }
  tab_requete->taille = count;
  fclose(in);
}



void print_result_requete(Tab_requete *tab_requete, char * fileout){
  if (tab_requete == NULL) {
    fputs("parsing_queries : tab_requete est null",stderr);
    exit(1);
  }
  FILE *out = fopen(fileout,"w");
  if (out == NULL) {
    fputs("parsing_queries : out est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  for (int i = 0; i < tab_requete->taille; i++) {
    fprintf(out, "%s,", tab_requete->tab[i]->depart);
    fprintf(out, "%s,", tab_requete->tab[i]->arrivee);
    fprintf(out, "%s,", tab_requete->tab[i]->jour);
    fprintf(out, "%s\n", tab_requete->tab[i]->heure);
  }
  fclose(out);
}



int trouve_stop_id(Tab_noeud *tab_noeud, char *stop_nom, long *resultats) {

  //ce bloc permet de rajouter des guillemets autour du nom fourni
  char *tmp = malloc(100 * sizeof(char));
  tmp[0] = '"';
  int count = 0;
  while (stop_nom[count] != '\0') {
    tmp[count + 1] = stop_nom[count];
    count = count + 1;
  }
  tmp[count+1] = '"';
  tmp[count + 2] = '\0';

  int j = 0;

  /*si une occurrence du nom donné est trouvé dans les données du tab_noeud
  et stock l'identifiant */
  for (int i = 0; i < tab_noeud->taille; i++) {
    if (strcmp(tab_noeud->tab[i]->nom,tmp) == 0) {
      resultats[j] = tab_noeud->tab[i]->stop_id;
      j = j + 1;
    }
  }
  free(tmp);
  if (j == 0) {
    fputs("erreur pas d'identifiant correspondant\n",stderr);
  }
  return j;
}


long heure_queries(char * heure){

  //on utilise le code ascii pour faire correspondre 1 en int à 1 en char
  int h1 = heure[0] - 48;
  int h2 = heure[1] - 48;
  int m1 = heure[2] - 48;
  int m2 = heure[3] - 48;

  return (h1*10 + h2)*60*60 + (m1*10 + m2)*60;
}



void free_tab_requete(Tab_requete *tab_requete) {
  if (tab_requete == NULL) {
    fputs("parsing_requete : tab_requete est null",stderr);
    exit(1);
  }

  //on libère la mémoire occupée par chaque requête
  for (int i = 0; i < tab_requete->taille; i++) {
    Requete * point = tab_requete->tab[i];
    if (point == NULL) {
      fputs("parsing_requete : point est null, erreur allocation",stderr);
      exit(1);
    }
    free(point);
  }
  free(tab_requete);
}
