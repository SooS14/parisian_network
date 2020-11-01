#include "types.h"
#include "parsing_option.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void parsing_args(int argc, char ** argv, Argument *argument){

  if (argument == NULL) {
    fputs("parsing_option : argument est null",stderr);
    exit(1);
  }

  //initialisation de l'intance de structure Argument
  argument->ratp_dataset = NULL;
  argument->queries = NULL;
  argument->result = NULL;
  argument->flag = 0;

  int c;

  //parcours la ligne de commande à la recherche des options
  while ((c = getopt (argc, argv, "d:hq:r:g")) != -1){

    //remplissage de "argument"
    switch (c){
      case 'h':
        print_usage();
        exit(0);
      case 'd':
        argument->ratp_dataset = optarg;
        break;
      case 'q':
        argument->queries = optarg;
        break;
      case 'r':
        argument->result = optarg;
        break;
      case 'g':
        argument->flag = 1;
        break;

      //les cas qui ne sont pas en accord avec le format
      case '?':
        if (optopt == 'd'){
          fprintf (stderr, "Option -%c requiert un argument.\n", optopt);
        }else if (isprint (optopt)){
          fprintf (stderr, "option inconnue `-%c'.\n", optopt);
        }else{
          fprintf (stderr,"caractère inconnu `\\x%x'.\n",optopt);
        }

        print_usage();
        exit(1);


      /*ce que l'on renvoie par défault pour s'assurer un retour même dans des
      cas non pris en compte */
      default:
        fprintf (stderr,"caractère inconnu `%c'.\n",c);
        print_usage();
        exit(1);
      }
    }

    //certaines options sont requises

    if(!argument->ratp_dataset){
        puts("l'option -d est requise");
        print_usage();
        exit(1);
    }
    if(!argument->queries){
        puts("l'option -q est requise");
        print_usage();
        exit(1);
    }
    if(!argument->result){
        puts("l'option -r est requise");
        print_usage();
        exit(1);
    }
}


/*utilitaire qui s'affiche lors d'une erreur de l'utilisateur ou lorsque
l'option -h est utilisée */
void print_usage(void){
  puts(
  "Usage:\n"
  "-d DOSSIER    donnees de la ratp\n"
  "              contenues dans RATP_GTFS_LINES\n"
  "-q FICHIER    chemin du fichier où\n"
  "              sont donnees les requêtes\n"
  "-r            chemin du fichier où\n"
  "              sont donnes les resultats\n"
  "-g            pour mettre à jour les\n"
  "              donnes de la ratp\n"
  "-h            afficher l'aide");
}



void print_result_argument(Argument *argument, char *fileout){

  FILE *out = fopen(fileout,"w");
  if (out == NULL) {
    fputs("parsing_option : erreur ouverture fichier",stderr);
    exit(1);
  }

  fprintf(out,"dossier ratp :%s\n", argument->ratp_dataset);
  fprintf(out,"fichier queries :%s\n", argument->queries);
  fprintf(out,"fichier result :%s\n", argument->result);
  if (argument->flag == 1) {
    fprintf(out,"UPDATE_RATP_DATASET\n");
  } else {
    fprintf(out,"NO_UPDATE_REQUIRED\n");
  }
  fclose(out);
}
