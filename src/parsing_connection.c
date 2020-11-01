#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"
#include "parsing_connection.h"




void parse_connection(char *filein, Tab_connection *tab_connection) {

  if (tab_connection == NULL) {
    fputs("parsing_connection : tab_connection est null",stderr);
    exit(1);
  }


  FILE * table_trans = fopen(filein,"r");
  if (table_trans == NULL) {
    fputs("parsing_connection : in est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  char buffer[100];
  int count = 0;

  //la premiere ligne n'est que le titre de la table de transfert, on la saute
  fseek(table_trans,26,SEEK_SET);

  //tant que fgets ne renvoie pas le signal erreur ou fin de fichier :
  while (fgets(buffer,100,table_trans)) {

    /*gros problème de cette methode si le curseur de queries.txt est sur
    une nouvelle ligne la chaine "buffer" est VIDE !! */
    if (strcmp(buffer,"\n") == 0) {
      break;
    }

    int fin = 0;
    //pour supprimer le \n dans buffer
    while (buffer[fin] != '\n') {
      fin = fin + 1;
    }
    buffer[fin] = '\0';

    //la connection suivante est créée
    Connection *connection = malloc(sizeof(*connection));
    if (connection == NULL) {
      fputs("parsing_connection : connection est null, erreur allocation",stderr);
      exit(1);
    }

    //le format de la table de transfert est adapté pour sscanf
    sscanf(buffer,"%li,%li,%li,%li",
    &(connection->stop_dep),
    &(connection->stop_arr),
    &(connection->tps_dep),
    &(connection->tps_arr));

    //on stock chaque connection
    tab_connection->tab[count] = connection;
    count = count + 1;
  }
  tab_connection->taille = count;
  fclose(table_trans);

}



void print_result_connection(Tab_connection *tab_connection, char * fileout){

  if (tab_connection == NULL) {
    fputs("parsing_connection : tab_connection est null",stderr);
    exit(1);
  }

  FILE *out = fopen(fileout,"w");
  if (out == NULL) {
    fputs("parsing_connection : out est null, erreur ouverture fichier",stderr);
    exit(1);
  }

  for (int i = 0; i < tab_connection->taille; i++) {
    fprintf(out, "%li,", tab_connection->tab[i]->stop_dep);
    fprintf(out, "%li", tab_connection->tab[i]->stop_arr);
    fprintf(out, "%li,", tab_connection->tab[i]->tps_dep);
    fprintf(out, "%li\n", tab_connection->tab[i]->tps_arr);
  }

  fclose(out);
}




void free_tab_connection(Tab_connection *tab_connection) {

  if (tab_connection == NULL) {
    fputs("parsing_connection : tab_connection est null",stderr);
    exit(1);
  }

  //pour chaque éléments du tableaux on libère l'espace mémoire occupé
  for (int i = 0; i < tab_connection->taille; i++) {
    Connection * point = tab_connection->tab[i];
    if (point == NULL) {
      fputs("parsing_connection : point est null, erreur allocation",stderr);
      exit(1);
    }
    free(point);
  }
  free(tab_connection);
}
