#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h>
#include <stdio.h>



/*structure qui représente une connection c'est à dire:
arrêt départ; arrêt arrivée; heure départ; heure arrivée;
grâce à cette structure on peut stocker les données présentes
dans le fichier table_transfert_finale.txt */
typedef struct Connection Connection;
struct Connection{

  // arrêt de départ symbolisé par son stop_id donné par la ratp
  long stop_dep;

  // arrêt d'arrivée symbolisé par son stop_id donné par la ratp
  long stop_arr;

  // heure de départ de sto_dep en seconde
  long tps_dep;

  // heure d'arrivée à sto_arr en seconde
  long tps_arr;
};



/*la structure Tab_connection regroupe les structures connection
obtenues par le parcours de table_transfert_finale */
typedef struct Tab_connection Tab_connection;
struct Tab_connection{

  //tableau utilisé pour regrouper les connections
  Connection *tab[10000000];

  //pour sauvegarder la taille du tableau
  int taille;
};



//stock les informations durant le parsing de all_stops.txt
//un Noeud est créé pour chaque ligne de all_stops.txt
typedef struct Noeud Noeud;
struct Noeud{

  //identifiant de l'arrêt
  long stop_id;

  //nom de l'arrêt (sans les guillemets)
  char nom[100];

  //identiifiant de la ligne
  char ligne_id[100];
};



//regroupe les Noeuds dans un tableau dont la taille est connue
typedef struct Tab_noeud Tab_noeud;
struct Tab_noeud{

  //tableau utilisé pour regrouper les noeuds
  Noeud *tab[1000];

  //sauvegarde la taille du tableau
  int taille;
};



//stock les informations durant le parsing de queries.req
//une Requete est créé pour chaque ligne de queries.req
typedef struct Requete Requete;
struct Requete{

  //nom de l'arrêt de départ
  char depart[100];

  //nom de l'arrêt d'arrivée
  char arrivee[100];

  //date donnée dans la requête sous la forme aaaammjj
  char jour[100];

  //heure donnée dans la requête sous la forme hhmm
  char heure[100];
};



//regroupe les Requete dans un tableau dont la taille est connue
typedef struct Tab_requete Tab_requete;
struct Tab_requete{

  //stock chque requête
  Requete *tab[1000];

  //sauvegarde la taille du tableau
  int taille;
};



//structure utilisée pour stocker les arguments de ligne de commande
typedef struct Argument Argument;
struct Argument{

  //dossier contenant les données de la ratp
  char * ratp_dataset;

  //fichier contenant les requêtes
  char * queries;

  //fichier contenant le résultat
  char * result;

  //permet de stocker une condition
  int flag;
};

#endif
