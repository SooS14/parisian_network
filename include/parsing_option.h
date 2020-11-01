#ifndef OPTION_H
#define OPTION_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"


//parcours et stock dans args les arguments de ligne de commande avec argv et
//argc les arguments de la fonction main
void parsing_args(int argc,  char ** argv, Argument *args);


//affiche les options acceptées en ligne de commande
void print_usage(void);


//libère l'espace occupé par une structure d'argument
void free_argument(Argument *argument);


//renvoie le contenu de la structure argument dans le fichier "fileout"
void print_result_argument(Argument *argument, char *fileout);


#endif
