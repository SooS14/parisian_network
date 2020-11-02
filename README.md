# projet metro parisien


description fonctionnement :
	la commande "make" lance la compilation
	la commande "./bin/main -h" permet de voire les options
	un exemple de commande : 
		"./bin/main -d RATP_GTFS_LINES -q tests/queries.txt -r tests/resultchemin.txt"

Il est déconseillé d'utiliser l'option -g car cela actualisera le jeu de donnés qui sera impacté par de potentielles grèves en cours. J'ai fourni un vieux jeu de données datant du mois d'octobre 2019.

les résultats sont écrits dans le fichier donné avec l'option -r

le programme fait plusieurs tentatives en fonction des identifiants des arrêts. Les tenatives ratées portent l'inscription "pas de chemin"

description des dossiers :
bin : contient l'éxécutable
dataset : contient le jeu de donné modifié par le pré-traitement
include : contient les .h du projet 
	types.h contient les structures utilisées dans le codes
src : contient les .c du projet
	parsing_*.c contiennent les fonctions de parsing du jeu de donnée
	print_chemin contient les fonctions pour l'affichage du résultat
	scan_connection.c contient l'algorithme permettant de trouver le plus court chemin
	main.c éxécute les fonctions

tests : contient les résultats de mes tests
RATP_GTFS_LINES : contient les données de la RATP
(peuvent être modifiées avec les options)
	 



# Parisian metro project


operating description :
	"make" command launches the compilation
	command "./bin/main -h" allows to see the options
	example : 
		"./bin/main -d RATP_GTFS_LINES -q tests/queries.txt -r tests/resultchemin.txt".

It is not recommended to use the -g option because it will update the dataset which will be impacted by the possible strikes. I provided an old dataset from October 2019.

The results are written in the file given with the -r option.

the program makes several attempts based on the stop identifiers. Failed attempts are marked "no way" ("pas de chemin").

file description :
bin : contains the executable
dataset : contains data modified by the preprocess
include : contains header files
	types.h contains the structures used in the code
src : 	contains source files
	parsing_*.c contains parsing functions of the dataset
	print_path contains functions for displaying the result
	scan_connection.c contains the algorithm which computes the shortest path of a connection.
	main.c executes all functions

tests: contains results of my tests
RATP_GTFS_LINES: contains RATP (Régie autonome des transports parisiens) data
(can be modified using options)


