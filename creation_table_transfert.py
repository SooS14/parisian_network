# -*- coding: utf-8 -*-

import sys
import time



                ###################################
                #création de la table de transfert#
                ###################################




#en entrée on a : station_dep ,station_arrivee ,jour ,heure_depart
#on ne considère que le métro
#il faut traiter les données de la RATP de la manière suivante :
#   quels services sont disponibles
#   en déduire quels trips sont disponibles
#   en déduire quels transferts entre arrêts sont disponibles
#   construire la table de transfert.


#On prcocède en 2 temps.
#   On commence par donner tous les transferts entre arrêts d'une même ligne
#   Puis on y ajoute tous les transferts liés aux correspondances entre lignes différentes
#   On trie la table de transfert par heure de départ croissante



#coin des variables globales :
#########################################################################################################
t1 = time.time()

#pour limiter le temps d'éxecution du prétraitement et la taille de la table on donne une
#durée max du trajet et le jour du trajet ainsi que l'heure du départ.
duree_trajet = "0300"

liste_id_ligne = ['1','2','3','3b','4','5','6','7','7b','8','9','10','11','12','13','14','Fun','Orv']

if len(sys.argv) > 3 :
    date = sys.argv[1]
    temps_depart = sys.argv[2]
    dossier = sys.argv[3]
else :
    print('il manque des arguments')
        
temps_depart = temps_depart + "00"

print(date)
print(temps_depart)
print(dossier)


#liste de tous les stops de metro seulement
all_stop = []

##########################################################################################################






#regroupement des donnees :
##########################################################################################################

#cette fonction regroupe tous les stops de metro d'une ligne dans un fichier all_stops.txt 
def stops_ligne(id_ligne):

    stops1 = open(dossier + "/RATP_GTFS_METRO_" + id_ligne + "/stops.txt", "r")
    data = stops1.read()
    stops1.close()
    liste_stops = data.split('\n')
    m = len(liste_stops)

    stops2 = open("dataset/all_stops.txt","a")

    res = []

    for i in range(1,m-1):
        tmp = liste_stops[i].split(',')
        res.append(tmp[0])
        stops2.write(tmp[0])
        stops2.write(",")
        stops2.write(tmp[2])
        stops2.write(",ligne "+id_ligne+",")
        stops2.write("\n")
    stops2.close()
    return res


stops = open("dataset/all_stops.txt", "w")
stops.write("liste de tous les stops de metro\n")
stops.close()

liste_stops_metro = []

for id_ligne in liste_id_ligne :
    liste_stops_metro = stops_ligne(id_ligne) + liste_stops_metro



##########################################################################################################







#fonctions auxiliaires :
##########################################################################################################

#cette fonction transforme une heure de la form hh:mm:ss en heure décimale (en seconde)
def heure_decimale1(h):
    l1 = h.split(':')
    heure = (int(l1[0]) * 3600) + (int(l1[1]) * 60) + int(l1[2])
    return(heure)

#cette fonction transforme une heure de la form hhmmss en heure décimale (en seconde)
def heure_decimale2(h):
    n = len(h)
    i = 0
    res = 0
    while i < n :
        res = (int(h[i] + h[i + 1])) * pow(60,2 - i/2) + res
        i = i + 2
    return res
#########################################################################################################









#création de la table_de_transfert :
##########################################################################################################
#cette fonction écrit dans le fichier table_transfert d'une ligne pour des
#horaires dans un intervalle de donnees par la variable : duree_trajet heures à partir de temps_depart
#temps_depart est une chaine de caracteres de la forme : hhmmss
#date est une string de la forme : anneemoisheure sans espaces ni séparateurs.
#id_ligne est une string de la forme "1" ou "7b"

def table_horaire_ligne(id_ligne,temps_depart,date):
    string1 = dossier + "/RATP_GTFS_METRO_" + id_ligne + "/calendar_dates.txt"
    calendar = open(string1, "r")
    data1 = calendar.read()
    calendar.close()

    liste_data1 = data1.split('\n')
    n = len(liste_data1)

    stock_service = []
    for i in range(1,n-1):
        a = liste_data1[i].split(',')
        if a[1] == date :
            stock_service.append(a[0])


    string2 = dossier + "/RATP_GTFS_METRO_" + id_ligne + "/trips.txt"
    trips = open(string2, "r")
    data2 = trips.read()
    trips.close()

    liste_data2 = data2.split('\n')
    m = len(liste_data2)

    stock_trips = []
    for service in stock_service :
        for i in range(1,m-1):
            a = liste_data2[i].split(',')
            if a[1] == service:
               stock_trips.append(a[2])


    string1 = dossier + "/RATP_GTFS_METRO_" + id_ligne + "/stop_times.txt"
    ligne = open(string1,"r")
    data = ligne.read()
    ligne.close()

    string2 = "dataset/table_transfert/table_transfert" + id_ligne + ".txt"
    transfers1 = open(string2, 'w')
    transfers1.write('table de transfert' + ' ' + id_ligne)
    transfers1.write('\n')
    transfers1.close()

    transfers2 = open(string2, 'a')

    liste_data = data.split('\n')
    n = len(liste_data)


    tps = heure_decimale2(temps_depart)
    duree_trajet_sec = heure_decimale2(duree_trajet)
    for i in range(1,n-1):
        a = liste_data[i].split(',')
        b = liste_data[i+1].split(',')
        a_heure = heure_decimale1(a[2])

        if (tps <= a_heure) and ( a_heure < (tps + duree_trajet_sec)) and (a[0] == b[0]) and (a[0] in stock_trips):

            transfers2.write(a[3])
            transfers2.write(',')
            transfers2.write(b[3])
            transfers2.write(',')
            transfers2.write(str(a_heure))
            transfers2.write(',')
            b_heure = heure_decimale1(b[1])
            transfers2.write(str(b_heure))
            transfers2.write('\n')

    transfers2.close()




for id_ligne in liste_id_ligne :
    table_horaire_ligne(id_ligne,temps_depart,date)

t2 = time.time()


#Cette fonction donne un nouveau fichier transfert dans lequel les correspondances
#avec les lignes de bus sont absentes.

def transfert_metro(id_ligne,liste_stops_metro):

    string3 = dossier + "/RATP_GTFS_METRO_" + id_ligne + "/transfers.txt"
    trans1 = open(string3, "r")
    data2 = trans1.read()
    trans1.close()
    liste_transfers = data2.split('\n')
    n = len(liste_transfers)

    string4 = "dataset/correspondance/correspondances" + id_ligne + ".txt"
    trans2 = open(string4, "w")
    trans2.write("correspondances de la ligne" + " " + id_ligne)
    trans2.write("\n")
    trans2.close()

    trans3 = open(string4, "a")

    for j in range(1,n-1):
        transfers = liste_transfers[j].split(',')
        depart = transfers[0]
        arrivee = transfers[1]
        if (depart in liste_stops_metro) and (arrivee in liste_stops_metro) :
            trans3.write(liste_transfers[j])
            trans3.write('\n')

    trans3.close()


for id_ligne in liste_id_ligne :
    transfert_metro(id_ligne, liste_stops_metro)


#Cette fonction écrit dans la table de transfert de chaque ligne les correspondances
#venant des autres lignes en prenant en compte le temps de transfert entre les 2 stops.
#Elle est fondé sur le fait que le fichier transfers.txt de la RATP donne
#,pour chaque ligne, uniquement les correspondances venant des autres lignes
#et non celle partant de la ligne en question.

def new_transfert(id_ligne):
    string1 = "dataset/correspondance/correspondances" + id_ligne + ".txt"
    new = open(string1, "r")
    data1 = new.read()
    new.close()

    liste_new_transfert = data1.split('\n')
    n = len(liste_new_transfert)

    string2 = "dataset/table_transfert/table_transfert" + id_ligne + ".txt"
    old1 = open(string2, "r")
    data2 = old1.read()
    old1.close

    liste_old_transfert = data2.split('\n')
    m = len(liste_old_transfert)

    old2 = open(string2, "a")

    for i in range(1, n-1):
        newtransfert = liste_new_transfert[i].split(',')
        for j in range(1, m-1):
            oldtransfert = liste_old_transfert[j].split(',')
            if newtransfert[1] == oldtransfert[0] :
                old2.write(newtransfert[0])
                old2.write(',')
                old2.write(newtransfert[1])
                old2.write(',')
                heure_depart = int(oldtransfert[2]) - int(newtransfert[3])
                old2.write(str(heure_depart))
                old2.write(',')
                heure_arrivee = oldtransfert[2]
                old2.write(heure_arrivee)
                old2.write("\n")


            elif newtransfert[0] == oldtransfert[0] :
                old2.write(newtransfert[1])
                old2.write(',')
                old2.write(newtransfert[0])
                old2.write(',')
                heure_depart = int(oldtransfert[2]) - int(newtransfert[3])
                old2.write(str(heure_depart))
                old2.write(',')
                heure_arrivee = oldtransfert[2]
                old2.write(heure_arrivee)
                old2.write("\n")
                
    old2.close()


for id_ligne in liste_id_ligne :
    new_transfert(id_ligne)


t3 = time.time()

#Il ne reste plus qu'a mettre tous les transferts dans un même fichier.txt et de le trier par heure de
#départ croissante

def table_finale(liste_id_ligne):
    string1 = "dataset/table_transfert_finale.txt"
    finale1 = open(string1,"w")
    finale1.write("table_de_transfert_finale")
    finale1.write("\n")
    finale1.close()

    res = []

    for id_ligne in liste_id_ligne:
        string2 = "dataset/table_transfert/table_transfert" + id_ligne + ".txt"
        table = open(string2, "r")
        data = table.read()
        table.close()
        lignes_fichier = data.split('\n')
        n = len(lignes_fichier)

        for i in range(1,n-1):
            tmp = lignes_fichier[i].split(',')
            quad = (tmp[0],tmp[1],int(tmp[2]),tmp[3])
            res.append(quad)

    res_trie = sorted(res, key=lambda colonnes: colonnes[2])
    m = len(res_trie)
    finale2 = open(string1, "a")

    for quadrupl in res_trie:
        dep, arr, h_dep, h_arr = quadrupl
        finale2.write(dep)
        finale2.write(',')
        finale2.write(arr)
        finale2.write(',')
        finale2.write(str(h_dep))
        finale2.write(',')
        finale2.write(h_arr)
        finale2.write('\n')

    finale2.close()


table_finale(liste_id_ligne)




t4 = time.time()

print("creation de la table :")
print(t4 - t1)

#print("connexion de stop_times :")
#print(t2-t1)

#print("connexion de transfers :")
#print(t3-t2)

#print("triage + écriture")
#print(t4-t3)
