
#Definition de la classe Etudiant
class Etudiant:
    etudiants = []
    #Le constructeur
    def __init__(self, nom, notes):
        self.nom = nom
        self.notes = notes
        moy = Etudiant.moyenne(self.notes)
        if(moy < 10):
            self.admissibilite = False
        else:
            self.admissibilite = True
        Etudiant.ajouterEtudiant(self)
    
    def afficher(self):
        if self.admissibilite:
            resultat = "Admis"
        else: resultat = "Non admis"
        print(self.nom, " - ", resultat)

    @classmethod
    def ajouterEtudiant(cls, etudiant):
        cls.etudiants.append(etudiant)

    @classmethod
    def afficherResultat(cls):
        print("Resultats de l'examen: ")
        for e in cls.etudiants:
            e.afficher()
        
    @staticmethod
    def moyenne(notes):
        somme = 0
        for m in notes:
            somme += m
        return somme/3 
        

def main():
    #Lire au clavier le nom et notes de 3 etudiants
    for i in range(3):
        notes = []
        nom = input("Entrer le nom de l'étudiant: ")
        for j in range(3):
            note = input("Entrer une note ")
            n = float(note)
            notes.append(n)
        etudiant = Etudiant(nom, notes)

    Etudiant.afficherResultat()


if __name__ == '__main__':
    main()

