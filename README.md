# projet metro parisien simon


Simon Colin RT 1A


description fonctionnement :
	la commande "make" lance la compilation
	la commande "./bin/main -h" permet de voire les options
	un exemple de commande : 
		"./bin/main -d RATP_GTFS_LINES -q tests/queries.txt -r tests/resultchemin.txt"

Il est déconseillé d'utiliser l'option -g car cela actualisera le jeu de donnés qui sera impacté par les grèves en cours. J'ai fourni un vieux jeu de données datant du mois d'octobre 2019.

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
	 

