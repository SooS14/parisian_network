#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "scan_connection.h"
#include "print_chemin.h"
#include "parsing_stops.h"
#include "parsing_requete.h"
#include "parsing_connection.h"
#include "tps_unit_test.h"

int __remaining_alloc;


//teste la lecture des requêtes
void test_requete(void){
    Tab_requete tab_requete;// = malloc(sizeof(Tab_requete));
    parsing_requete("tests_queries.txt", &tab_requete);
    print_result_requete(&tab_requete,"results_requetes.txt");
    tps_assert(strcmp(tab_requete.tab[0]->depart, "Bobigny-Pablo-Picasso") == 0);
    tps_assert(strcmp(tab_requete.tab[0]->arrivee, "Mairie d'Issy") == 0);
    tps_assert(strcmp(tab_requete.tab[0]->jour, "20191214") == 0);
    tps_assert(strcmp(tab_requete.tab[0]->heure, "0100") == 0);
    //free_tab_requete(&tab_requete);
    for (int i = 0; i < tab_requete.taille; i++) {
      Requete * point = tab_requete.tab[i];
      if (point == NULL) {
        fputs("parsing_requete : point est null, erreur allocation",stderr);
        exit(1);
      }
      free(point);
    }
}



//teste la lecture des noeuds
void test_noeud(void){
    Tab_noeud tab_noeud; // = malloc(sizeof(*tab_noeud));
    parsing_stops("tests_all_stops.txt", &tab_noeud);
    print_result_stops(&tab_noeud,"results_stops.txt");
    tps_assert(tab_noeud.tab[0]->stop_id == 2371);
    tps_assert(strcmp(tab_noeud.tab[0]->nom, "\"Nation\"") == 0);
    tps_assert(strcmp(tab_noeud.tab[0]->ligne_id, "ligne 1") == 0);
    //free_tab_noeud(&tab_noeud);
    for (int i = 0; i < tab_noeud.taille; i++) {
      Noeud * point = tab_noeud.tab[i];
      if (point == NULL) {
        fputs("parsing_requete : point est null, erreur allocation",stderr);
        exit(1);
      }
      free(point);
    }
}





int main(void)
{
  TEST(test_requete);

  TEST(test_noeud);
}
