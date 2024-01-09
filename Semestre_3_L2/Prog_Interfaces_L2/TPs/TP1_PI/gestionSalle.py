
#Definition de la classe Salle
class Salle:
    nombreSalle = 0
    jours=["Lundi","Mardi"," Mercredi", "Jeudi" ,"Vendredi"]
    creneaux = ["9h-10h","10h-11h","11h-12h", "15h-16h" ,"16h-17h","17h-18h"]
    #Le constructeur
    def __init__(self, nom, disponibilite):
        Salle.nombreSalle += 1
        self.id = Salle.nombreSalle
        self.nom = nom
        self.disponibilite = disponibilite
    
    def reserver(self, date, creneau):
        self.disponibilite[date-1][creneau-1] = True
        print("La salle ", self.nom, " est reservée pour ", Salle.jours[date-1], " à ",Salle.creneaux[creneau-1])
    
    def annulerRes(self, date, creneau):
        self.disponibilite[date-1][creneau-1] = False
        print("Réservation annulée")

    def afficherSalle(self):
        print("La salle ", self.nom, ":")
        print("Les disponibilités :")
        for i in range(5):
            print(Salle.jours[i])
            for j in range(6):
                if self.disponibilite[i][j]:
                    disponibilite = "Reservée"
                else: 
                    disponibilite = "Disponible"
                print(Salle.creneaux[j], " : ", disponibilite)

class SalleMachine(Salle):
    def __init__(self, nom, disponibilite, nombreMachines, videoProj):
        super().__init__(nom, disponibilite)
        self.nombreMachines= nombreMachines
        self.videoProjecteur = videoProj
    def afficherSalle(self):
        super().afficherSalle()
        print("Nombre de machines: ", self.nombreMachines)
        if self.videoProjecteur:
            print("Cette salle est équipée d'un videoprojecteur.")
        else:
            print("Cette salle n'est pas équipée d'un videoprojecteur.")
    
disponibilite = [[True,False,False,False,True,False],[True,False,False,False,True,False],[True,False,False,False,True,False],[True,False,False,False,True,False],[True,False,False,False,True,False]]

#salle_1 = Salle("B103",disponibilite)
#salle_1.reserver(1,2)
#salle_1.afficherSalle()
#salle_1.annulerRes(1,2)
#salle_1.afficherSalle()

#salle_2 = SalleMachine("B162", disponibilite, 40, True)
#salle_2.afficherSalle()


