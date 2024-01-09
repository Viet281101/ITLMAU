#Définition de la classe Voiture
class Voiture:
    #création du constructeur
    def __init__(self, marque, couleur):
        self.marque = marque
        self.couleur = couleur

#Création de deux instances de la classe Voiture
voiture_1 = Voiture("Lamborghini" , "Noir")
voiture_2 = Voiture("BMW", "Rouge")

#Afficher la marque des deux voitures crées
print(voiture_1.marque)
print(voiture_1.couleur)
print(voiture_2.marque)
print(voiture_2.couleur)


