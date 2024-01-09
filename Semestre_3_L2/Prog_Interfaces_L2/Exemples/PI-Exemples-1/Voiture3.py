#Définition de la classe Voiture

class Voiture:
    
    #création du constructeur
    def __init__(self, marque, couleur):
        self.marque = marque
        self.couleur = couleur

    #Définition des méthodes 

    def peindre(self, NouvCouleur):
        self.couleur = NouvCouleur

#Création de deux instances de la classe Voiture
voiture_1 = Voiture("Lamborghini" , "Noir")

#Afficher la marque des deux voitures crées
print(voiture_1.couleur)
voiture_1.peindre("Rouge")
print(voiture_1.couleur)


