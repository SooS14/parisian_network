#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "types.h"


//réalise le parsing de la table horaire et le stock dans tab_connection
void parse_connection(char *filein, Tab_connection *tab_connection);


//affiche dans un fichier de destination "fileout" ce qui est stocké dans
//tab_connection
void print_result_connection(Tab_connection *tab_connection, char * fileout);


//libère la zone mémoire de tab_connection
void free_tab_connection(Tab_connection *tab_connection);


#endif
