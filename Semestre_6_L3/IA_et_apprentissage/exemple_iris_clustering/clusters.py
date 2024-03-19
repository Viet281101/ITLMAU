import numpy as np
import matplotlib
import matplotlib.pyplot as plt
#matplotlib.use('TkAgg') 
import csv
from random import randint
import math
import pandas as pd
import time

#Extraction des données des fichiers 
def convert_donne_vers_liste():
    nb_ligne_donnee = 0
    data_liste = []
    with open("iris_data.csv", "r") as ficher_data ,open("iris_label.csv", "r") as ficher_label  :
        
        donnees_data = csv.reader(ficher_data) 
        #donnees_data= ficher_data.read()
        print(donnees_data)
        for ligne_data in donnees_data:         
            data =  [float(v) for v in ligne_data[0].strip().split(";")if v.rstrip()]
            data_liste.append(data)
            #print(ligne_data)
        #print(data_liste)
        nb_ligne_donnee = len(data_liste)

        donnee_label = csv.reader(ficher_label)
        for ligne_label in donnee_label:
            #print(ligne_label)
            pass
    
    return data_liste, nb_ligne_donnee


#Creation de centroid Aleatoire qui ne font PAS partie de la liste 
def creation_centroid_alea(nb_centroid):
    nombre_cluster = nb_centroid
    liste_centre_cluster = []

    for i in range(nombre_cluster) :
        x1_cluster = randint(0, 10)
        x2_cluster = randint(0, 10)
        x3_cluster = randint(0, 10)
        x4_cluster = randint(0, 10)
        liste_centre_cluster.append([x1_cluster,x2_cluster, x3_cluster,x4_cluster] )

    return liste_centre_cluster


#Creation de centroid A PARTIR Des fleur de la liste 
def creation_centroid_in_list(nb_centroid, nb_ligne_donnee , data_liste):
    nombre_cluster = nb_centroid
    liste_centre_cluster = []
    no_repetition=[]
    for i in range(nombre_cluster) :
        ligne_centre = randint(0, nb_ligne_donnee-1)
        no_repetition.append(ligne_centre)
        while ( len(no_repetition) != len(set(no_repetition))) :
            del no_repetition[-1]
            ligne_centre = randint(0, nb_ligne_donnee-1)
            no_repetition.append(ligne_centre)

        liste_centre_cluster.append(data_liste[ligne_centre] )

    return liste_centre_cluster


#Calcul de distance (ici euclidienne)
def calcul_distance(nb_ligne_donnee ,nombre_dinfoParElement, liste_centre_cluster, data_liste ):
    liste_distance_temp = []
    distance_temp = 0

    for i in range(nb_ligne_donnee):
        sous_liste_dis_temp= []
        for j in range(len(liste_centre_cluster)):
            genkidaddition = 0
            for k in range(nombre_dinfoParElement): 
                genkidaddition += (float(liste_centre_cluster[j][k]) - float(data_liste[i][k]) ) ** 2  
            
            distance_temp = math.sqrt(genkidaddition)
            sous_liste_dis_temp.append(distance_temp)
        
        #print(sous_liste_dis_temp)
        indice_min_distance = sous_liste_dis_temp.index(min(sous_liste_dis_temp))
        liste_dis_min = [1 if valeur == indice_min_distance else 0 for valeur in range(len(liste_centre_cluster))]
                    
        liste_distance_temp.append(liste_dis_min)
    
    for point in liste_distance_temp:
        #print(point)
        pass
    
    return liste_distance_temp


#Calcul de distance (ici Manhattan)
def calcul_distance_manhattan(nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster, data_liste):
    liste_distance_temp = []

    for i in range(nb_ligne_donnee):
        sous_liste_dis_temp = []
        for j in range(len(liste_centre_cluster)):
            distance_temp = 0

            for k in range(nombre_dinfoParElement):
                distance_temp += abs(float(liste_centre_cluster[j][k]) - float(data_liste[i][k]))
            
            sous_liste_dis_temp.append(distance_temp)
        
        indice_min_distance = sous_liste_dis_temp.index(min(sous_liste_dis_temp))
        liste_dis_min = [1 if valeur == indice_min_distance else 0 for valeur in range(len(liste_centre_cluster))]
                    
        liste_distance_temp.append(liste_dis_min)
    
    for point in liste_distance_temp:
        #print(point)
        pass
    
    return liste_distance_temp



#Calcul de distance (ici Minkowski)
def calcul_distance_minkowski(nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster, data_liste, p):
    liste_distance_temp = []

    for i in range(nb_ligne_donnee):
        sous_liste_dis_temp = []
        for j in range(len(liste_centre_cluster)):
            genkidaddition = 0
            for k in range(nombre_dinfoParElement):
                genkidaddition += abs(float(liste_centre_cluster[j][k]) - float(data_liste[i][k])) ** p

            distance_temp = genkidaddition ** (1/p)
            sous_liste_dis_temp.append(distance_temp)

        indice_min_distance = sous_liste_dis_temp.index(min(sous_liste_dis_temp))
        liste_dis_min = [1 if valeur == indice_min_distance else 0 for valeur in range(len(liste_centre_cluster))]

        liste_distance_temp.append(liste_dis_min)

    return liste_distance_temp


#Calcul de 1 seul SSE 
def calcul_sse(nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster, data_liste):
    sse = 0

    for i in range(nb_ligne_donnee):
        point = data_liste[i]
        distances_point_cluster = []

        for j in range(len(liste_centre_cluster)):
            distance_cluster = 0
            for k in range(len(point)):
                distance_cluster += (float(liste_centre_cluster[j][k]) - float(point[k])) ** 2

            distances_point_cluster.append(distance_cluster)

        indice_min_distance = distances_point_cluster.index(min(distances_point_cluster))
        sse += distances_point_cluster[indice_min_distance]  

    return sse




#Fonction pour reccuperer centre 
def recalculer_centres(affectation, data_liste, nombre_cluster):
    #print("Affectations actuelle :", affectation)
    nouveau_centres = []

    for cluster in range(nombre_cluster):
        indices_points_du_cluster = [i for i in range(len(data_liste)) if affectation[i] == cluster]
        
        if indices_points_du_cluster:
            nouveau_centre = [sum(data_liste[i][j] for i in indices_points_du_cluster) / len(indices_points_du_cluster) for j in range(len(data_liste[0]))]
        else:
            nouveau_centre = data_liste[randint(0, len(data_liste)-1)]

        print(f"Nouveau centre pour le cluster {cluster} : {nouveau_centre}")
        nouveau_centres.append(nouveau_centre)

    return nouveau_centres


#Fonction qui extrait le type des fleurs et les met dans une liste
def convert_label(chemin_fichier):
    labels_liste = []
    with open(chemin_fichier, 'r') as fichier_label:
        lecteur = csv.reader(fichier_label)
        for ligne in lecteur:
            data =  [float(v) for v in ligne[0].strip().split(";")if v.rstrip()]
            labels_liste.append(data)
    return labels_liste


#Calcul de la purete d'un cluster
def purete_cluster(affectation, labels, nombre_cluster):
    puretes = []

    numero_cluster=1
    for cluster in range(nombre_cluster):
        compteur_types = [0, 0, 0]

        for i, cluster_affectation in enumerate(affectation):
            if cluster_affectation == cluster:
                type_iris = int(labels[i][0])
                compteur_types[type_iris] += 1

        print(f"Nombre de type de fleur [setosa, versicolor, virginica] dans le cluster {numero_cluster} :" ,compteur_types)
        total_points = sum(compteur_types)
        print(f"Nombre de fleur total dans le cluster {numero_cluster}: ", total_points)
        if total_points > 0:
            pourcentage_types = [coompteur / total_points for coompteur in compteur_types]
            purete = max(pourcentage_types)
            puretes.append(purete)

        numero_cluster+=1
        
    return puretes


#Fonction pour placer les données sur le graph 2D
def placement_point(axes,liste_distance_temp, liste_centre_cluster , liste_axe_pour_print ,data_liste ): 
    #liste de combinaison d'axes 
    combinaison_axes = [
                            [["LongueurSepale", 0], ["LargeurSepale",1]], 
                            [["LongueurSepale",0], ["LongueurPetale",2]], 
                            [["LongueurSepale",0], ["LargeurPetale",3]], 
                            [["LargeurSepale",1], ["LongueurPetale",2]], 
                            [["LargeurSepale",1], ["LargeurPetale",3]], 
                            [["LongueurPetale",2], ["LargeurPetale",3]]
                        ]


    #Affichage des clusters pour chaque point
    for i, axe_plan in enumerate(axes.flatten()):
        #Selectionn des axes a afficher en fonction de la combinaison actuelle
        axe_x, axe_y = combinaison_axes[i]
        axe_plan.clear()
        for i, point in enumerate(liste_distance_temp):
            appartenance_cluster = point.index(1) 
            couleur_cluster = couleurs_clusters[appartenance_cluster]
            
            #Selection des axes a afficher en fonction de combinaison_axes
            x = data_liste[i][axe_x[1]]
            y=  data_liste[i][axe_y[1]]

            axe_plan.scatter(x,y, color=couleur_cluster)
        plt.subplots_adjust(hspace=0.5) 
        axe_plan.set_xlabel(f'{axe_x[0]}', fontsize=15)
        axe_plan.set_ylabel(f'{axe_y[0]}', fontsize=15)

        #Afficher les centres des clusters
        for i, centre in enumerate(liste_centre_cluster):
            couleur_cluster = couleurs_clusters[i]
            
            #Selection des axes a afficher en fonction de liste_centre_cluster
            x = centre[axe_x[1]]
            y = centre[axe_y[1]]
            #print("centre ", centre)
            #print("centre x : ",x)
            #print("centre y : ", y)

            axe_plan.scatter(x, y, color=couleur_cluster, marker='x', s=100)
    
    #plt.draw()
    
    #plt.pause(0.1)



#Fonction qui prépare a l'utilisation du SSE , elle permet de choisir aussi le calcul de distance 
def analyse_sse(data_liste):
    valeurs_sse = []
    ensmble_range_k=range(1, 11)
    print("--------------------------")
    print("\n ON VA CALCULER LES SSE AVEC DE NOUVEAU CENTRE donc RECHOISSISEZ une methode de calcul ")
    choix_calcul_distance = -1
    while choix_calcul_distance <= 0 or choix_calcul_distance > 3  :
        choix_calcul_distance =int(input(" Quel calcul de distance voulez vous ?  : \n[1] Euclidienne  [2] Manhattan [3] Minkowski :"))

    choix_de_p = -1
    for k in ensmble_range_k:
        liste_centre_cluster = creation_centroid_alea(k)


        if choix_calcul_distance == 1:
            liste_distance_temp = calcul_distance(nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, data_liste)
        elif choix_calcul_distance == 2:
            liste_distance_temp = calcul_distance_manhattan(nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, data_liste)
        elif choix_calcul_distance == 3:

            if choix_de_p == -1 :
                while choix_de_p <= 0:
                    choix_de_p = int(input("Choississez un nombre de P pour Minkowski ? : "))
            liste_distance_temp = calcul_distance_minkowski(nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, data_liste, choix_de_p)
        
        sse = calcul_sse(nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, data_liste)
        valeurs_sse.append(sse)

    plt.figure()
    plt.plot(ensmble_range_k, valeurs_sse)
    plt.title('Analyse des SSE')
    plt.xlabel('Nombre de clusters')
    plt.ylabel('SSE')
    plt.show()





#Fonction faisant tous les type de Liason en fonction de l'argument "methode_linkage"
def multi_linkage(num_cluster1, num_cluster2, data_liste, nb_clusters, nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster , liste_distance_temp, methode_linkage):
    points_cluster1 = []
    points_cluster2 = []

    # Boucle pour mettres dans une liste les points du cluster 1
    for i in range(nb_ligne_donnee):
        if liste_distance_temp[i][num_cluster1] == 1:
            points_cluster1.append(data_liste[i])

    # Boucle pour mettres dans une liste les points du cluster 2
    for i in range(nb_ligne_donnee):
        if liste_distance_temp[i][num_cluster2] == 1:
            points_cluster2.append(data_liste[i])

    distance_link = 10000000000.0

    somme_distance = 0
    compteur =  0

    #Boucle pour faire le calcul de liaison
    for point1 in points_cluster1:
        for point2 in points_cluster2:
            distance = 0
            for k in range(nombre_dinfoParElement):
                distance += (float(point1[k]) - float(point2[k])) ** 2
            distance = math.sqrt(distance)

            #si methode_linkage ==1  on fait le simple linkage
            if methode_linkage == 1 :
                if distance < distance_link:
                    distance_link = distance
            
            #si methode_linkage ==2  on fait le complete linkage
            elif methode_linkage == 2 :
                if distance > distance_link:
                    distance_link = distance
            
            #si methode_linkage ==3  on fait le Group Average linkage
            elif methode_linkage == 3 :
                somme_distance += distance
                compteur += 1
            
            #si methode_linkage ==4  on fait le Ward linkage
            elif methode_linkage == 4:
                somme_distance += distance
    
    distance_moyenne = 0
    if methode_linkage == 3 :
        if compteur != 0:
            distance_moyenne = somme_distance / compteur
        return distance_moyenne
    
    # Si la méthode de linkage est Ward
    elif methode_linkage == 4:
        somme_carre_distances = somme_distance ** 2
        somme_carre_distances_cluster1 = 0
        for x in points_cluster1:
            for y in liste_centre_cluster[num_cluster1]:
                for k in range(nombre_dinfoParElement):
                    somme_carre_distances_cluster1 += (float(x[k]) - float(y)) ** 2
                    
           
        somme_carre_distances_cluster2 = 0
        for x in points_cluster2:
            for y in liste_centre_cluster[num_cluster2]:
                for k in range(nombre_dinfoParElement):
                    somme_carre_distances_cluster2 += (float(x[k]) - float(y)) ** 2
                    
        ward_distance = somme_carre_distances - somme_carre_distances_cluster1 - somme_carre_distances_cluster2
        return ward_distance
    
    #donc on return distance link si la methode est 1 ou 2
    else:
        return distance_link




#Cet fonction permet de lancer en boucle les methode de liason en boucle afin que cela se fasse sur les bon cluster
def fusion_clusters(data_liste, nb_clusters, nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster, liste_distance_temp, methode_linkage):
    distances_minimales = []  

    #On Parcours chaque paire de clusters
    for i in range(nb_clusters):
        for j in range(i + 1, nb_clusters): 
            #On Calcule la distance minimale entre les clusters i et j 
            distance_min = multi_linkage(i, j, data_liste, nb_clusters, nb_ligne_donnee, nombre_dinfoParElement, liste_centre_cluster,liste_distance_temp, methode_linkage)
            
            distances_minimales.append((i, j, distance_min)) 
    
    #On Trie la liste des distances minimales 
    distances_minimales.sort(key=lambda x: x[2])
    
    #et on separe les données
    clusterAccueillant, clusterAbandonne, distance_min = distances_minimales[0]

    print(f"Fusion des cluster d'indice {clusterAccueillant} et {clusterAbandonne}")


    # Boucle pour fusionner les clusters
    for ligne, element in enumerate(liste_distance_temp):
        # Si l'élément appartient au clusterAbandonne, le changer pour qu'il appartienne au cluster accueillant
        #et on supprime la colonne dappartenance de lancien cluster
        if element[clusterAbandonne] == 1:
            liste_distance_temp[ligne][clusterAccueillant] = 1
        liste_distance_temp[ligne].pop(clusterAbandonne)

    nb_clusters -=1
    liste_centre_cluster.pop(clusterAbandonne)

    return liste_distance_temp , nb_clusters, liste_centre_cluster









#-----------------------------------------------
#---- APPEL DE FONCTIONS ET DE VARIABLE---------
#-----------------------------------------------

#---------------------
#--- PARTIE 1 ET 2 
#----------------------
print("---------------------------------------")
print("ATTENTION TOUT LES GRAPHIQUE SERONT AFFICHE A LA FIN CEPENDANT DES INDICATIONS SERONT AFFICHE SUR LE TERMINAL !!")
print("Veuillez tout lire !!!")
print("\n[PARTIE 1 et 2] Données, Calcul de K-Moyens , Creation et Choix de Centroid, Pureté , Calcul de Distance")

fig_avant, axes_avant = plt.subplots(2, 3, figsize=(15, 10))
fig_avant.suptitle("Avant modification")
fig_apres, axes_apres = plt.subplots(2, 3, figsize=(15, 10))
fig_apres.suptitle("Après modification")

couleurs_clusters = ['red', 'green', 'blue', 'orange', 'purple', 'pink', 'black', 'gray']

data_liste = []
liste_centre_cluster = []
nb_ligne_donnee=0 
data_liste, nb_ligne_donnee =convert_donne_vers_liste()
#print(data_liste)
#print(nb_ligne_donnee)

# nb_info_par_feuille=int(input("Combien d'information il y a par feuille (normalement dans ce tp il y en a 4 donc on va autoriser de 1 à 4) ? : "))
# while choix_calcul_distance <= 0 or choix_calcul_distance > 4  :
#     choix_calcul_distance =int(input(" On limite la les info a 4 "))
nb_info_par_feuille = 4


nombre_cluster = 0
while nombre_cluster <= 0 or nombre_cluster >8  :
    nombre_cluster =int(input("Combien de Cluster voulez vous (il y a 8 couleurs max): "))
yes_no_alea= int(input("[1] Pour des points aleatoires , [0] pour utiliser des centroid baser sur des fleurs existante : "))

if yes_no_alea :
    liste_centre_cluster = creation_centroid_alea(nombre_cluster)
else :
    liste_centre_cluster = creation_centroid_in_list(nombre_cluster, nb_ligne_donnee, data_liste)

print("Voici la liste des centres : \n", liste_centre_cluster)


choix_calcul_distance = -1
while choix_calcul_distance <= 0 or choix_calcul_distance > 3  :
    choix_calcul_distance =int(input("\nQuel calcul de distance voulez vous ?  : \n[1] Euclidienne  [2] Manhattan [3] Minkowski :"))




nb_iteration_max= 30
ancienne_affectation = []
liste_distance_temp = []
if choix_calcul_distance ==1  :
    liste_distance_temp = calcul_distance(nb_ligne_donnee , nb_info_par_feuille, liste_centre_cluster, data_liste )
elif choix_calcul_distance ==2  :
    liste_distance_temp = calcul_distance_manhattan(nb_ligne_donnee , nb_info_par_feuille, liste_centre_cluster, data_liste )
elif choix_calcul_distance == 3: 
    choix_de_p = -1
    while choix_de_p <= 0   :
        choix_de_p =int(input("Choississez un nombre de P pour Minkowski ? : "))
    
    liste_distance_temp = calcul_distance_minkowski(nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, data_liste,choix_de_p )


print(liste_centre_cluster)

placement_point(axes_avant,liste_distance_temp, liste_centre_cluster, [0,1], data_liste)


#----------------------------------------------
#--- PARTIE 2 : RECALCUL DES CENTRES ET SSE ---
#----------------------------------------------

for iteration in range(nb_iteration_max):
    
    #time.sleep(1)  #Pause
    #plt.clf()  
    placement_point(axes_apres,liste_distance_temp, liste_centre_cluster, [0,1], data_liste)
    nouvelles_affectation = [point.index(1) for point in liste_distance_temp]

    if ancienne_affectation == nouvelles_affectation:
        print(f"Les affectations n'ont pas changé pour l'itération {iteration} !! FIN")
        break

    ancienne_affectation = nouvelles_affectation
    liste_centre_cluster = recalculer_centres(liste_distance_temp,data_liste, nombre_cluster)

    sse = calcul_sse(nb_ligne_donnee, nombre_cluster, liste_centre_cluster, data_liste)
    print(f"\nSSE DE l'itération {iteration + 1}: {sse}")


labels = convert_label("iris_label.csv")
puretes_clusters = purete_cluster(nouvelles_affectation, labels, nombre_cluster)

print("Pureté du cluster basé sur le type de fleur le plus proliminent :")
for i, purete in enumerate(puretes_clusters):
    print(f"Pureté du cluster {i + 1}: {purete * 100:.2f}%")




placement_point(axes_avant,liste_distance_temp, liste_centre_cluster, [0,1], data_liste)


#--------------------------------------------
#--- PARTIE 3 : LINKAGES ET DENDROGRAMME ----
#--------------------------------------------

print("------------------------------------")
print("------------------------------------")
print("\n [PARTIE 3] LINKAGE TEST \n")
print(f"Il reste {nombre_cluster} de cluster , nous allons effectuer un linkage")
print("\nPour cela choisissez le nombre de niveau de coupe cest a dire le nombre de cluster que vous voulez a la fin !")
# Appel de la fonction multi_linkage avec les paramètres appropriés
nv_coupe =0
while nv_coupe <= 0 or nv_coupe > nombre_cluster:
    nv_coupe= int(input("Choisissez un niveau de coupe correcte (minimum 1) si vous ecrivez le meme nombre que celui de cluster rien ne se passera : "))

print("\nMaintenant choisissez une méthode de Liaison")
methode_linkage=0
while methode_linkage <= 0 or methode_linkage > 4:
    methode_linkage =int(input("[1] Simple Linkage , [2] Complete Linkage , [3] Group Average Linkage , [4] Ward Linkage : "))

#pour ne pas entrer dans la boucle une premiere fois
if nv_coupe != nombre_cluster : 
    while nombre_cluster > nv_coupe :
        liste_distance_temp , nombre_cluster , liste_centre_cluster = fusion_clusters(data_liste, nombre_cluster, nb_ligne_donnee, nb_info_par_feuille, liste_centre_cluster, liste_distance_temp,methode_linkage )
        
liste_centre_cluster = recalculer_centres(liste_distance_temp,data_liste, nombre_cluster)
fig_fusion, axes_fusion = plt.subplots(2, 3, figsize=(15, 10))
fig_fusion.suptitle("[PARTIE 3] Après Fusion du nombre choisi de cluster \n (PS: vu que le nombre de cluster a changer les couleurs aussi mais pas la disposition des points)")


placement_point(axes_fusion,liste_distance_temp, liste_centre_cluster, [0,1], data_liste)



#---------------------------------------------------------------------
#--- PARTIE 2 : TEST ET ANALYSE SSE SUR DAUTRE DONNE ET AFFICHAGE ----
#---------------------------------------------------------------------
print("\n-------------------------")
print("-------------------------")
print("\n [PARTIE 2] Retour sur Analyse SSE plus poussé \n")
analyse_sse(data_liste)








plt.show()