#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "types.h"
#include "scan_connection.h"
#include "parsing_stops.h"
#include "parsing_connection.h"
#include "parsing_requete.h"
#include "parsing_option.h"
#include "print_chemin.h"


int main(int argc, char *argv[]) {

//script qui vérifie la présence des données de la RATP (et les
//télécharge/unzip/organise dans le cas échéant)
  system("./gestion_RATP_data.sh");


//execute le parsing des options donnés par l'utilisateur en ligne de commande
  Argument argument1;
  parsing_args(argc, argv, &argument1);


//si l'option -g est présente on lance un script qui saisi à nouveau
//les données de la ratp
  if (argument1.flag == 1) {
    system("./update_RATP_data.sh");
  }


//execute le parsing de queries.txt le chemin est donné par l'utilisateur
  Tab_requete *tab_requete1 = malloc(sizeof(*tab_requete1));
  parsing_requete(argument1.queries, tab_requete1);


//execute le parsing de all_stops et le stock dans tab_noeud1
  Tab_noeud *tab_noeud1 = malloc(sizeof(*tab_noeud1));
  parsing_stops("dataset/all_stops.txt", tab_noeud1);


//ouvre le fichier de sortie pour les résultats
  FILE *out = fopen(argument1.result,"w");
  if (out == NULL) {
    fputs("main : erreur ouverture fichier",stderr);
    exit(1);
  }

  //pour chaque requete on fait tourner l'algorithme de connexion scan
  for (int k = 0; k < tab_requete1->taille; k++) {

  //debut du traitement d'une nouvelle requete
    fprintf(out, "###########requete numero : %i\n", k);
    printf("\n");
    printf("\n");
    printf("###########requete numero : %i\n", k);

  //creation de la table de transfert en appelant le script python
    char appel_script[1000] = "python3 creation_table_transfert.py ";

    strcat(appel_script,tab_requete1->tab[k]->jour);
    strcat(appel_script," ");
    strcat(appel_script,tab_requete1->tab[k]->heure);
    strcat(appel_script," ");
    strcat(appel_script,argument1.ratp_dataset);
    system(appel_script);

  //execute le parsing de la table de transfert et le stock dans tab_connection1
    Tab_connection *tab_connection1 = malloc(sizeof(*tab_connection1));
    parse_connection("dataset/table_transfert_finale.txt",tab_connection1);


    /*tout ça parce que les arrets ont plusieurs id (dépendent de la ligne et
      du sens dans lequel elle est empruntée) */
      long *depart_ids = malloc(50*sizeof(long));
      int nb_depart = trouve_stop_id(tab_noeud1,tab_requete1->tab[k]->depart,depart_ids);
      long *arrivee_ids = malloc(50*sizeof(long));
      int nb_arrivee = trouve_stop_id(tab_noeud1,tab_requete1->tab[k]->arrivee,arrivee_ids);

      //pour chaque couple d'identifiant départ/arrivée on fait une tentative
      for (int i = 0; i < nb_depart; i++) {
        for (int j = 0; j < nb_arrivee; j++) {
          long depart_id = depart_ids[i];
          long arrivee_id = arrivee_ids[j];

          //l'heure de la requête est transformé en seconde
          long heure_depart = heure_queries(tab_requete1->tab[k]->heure);

          //création des deux tableaux utilisé dans le scan de connection
          long * tps_trajet = malloc(10000000 * sizeof(long));
          long * stop_trajet = malloc(10000000 * sizeof(long));


          /*exécution de l'algorithme, tps_trajet et stop_trajet sont
          actualisés */
          scan_connection(depart_id, heure_depart, tps_trajet,
                            stop_trajet, tab_connection1);


          fprintf(out,"#############essai numero : %i,%i\n", i, j);
          printf("\n");
          printf("##############essai numero : %i,%i\n", i, j);

          //écriture du chemin de la tentative dans le fichier des résultats
          long * path = calloc(1000, sizeof(long));
          int taille = chemin(stop_trajet, path, arrivee_id, depart_id);
          print_chemin(path,tps_trajet,taille,out,tab_noeud1);

          /*on libère les tableaux tps_trajet, stop_trajet et path entre chaque
          tentative */
          free_tab_trajet(tps_trajet, stop_trajet);
          free(path);
        }
      }

      //on libère la place prise par les connections entre chaque requête
      free_tab_connection(tab_connection1);
      free(depart_ids);
      free(arrivee_ids);
      fprintf(out, "\n");
      fprintf(out, "\n");
    }


  /*on ferme le fichier contenant les résultats et on libère l'espace occupé
  par les arrêts et les requêtes*/
  fclose(out);
  free_tab_noeud(tab_noeud1);
  free_tab_requete(tab_requete1);

  return 0;
}
