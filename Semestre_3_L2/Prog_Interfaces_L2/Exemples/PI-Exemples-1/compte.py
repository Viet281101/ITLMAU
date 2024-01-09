
#Definition de la classe Compte

class Compte:
    def __init__(self, id, mdp, nom_prenom):
        self.id = id
        self.mdp = mdp
        self.nom_prenom = nom_prenom

    def modifier_mdp(self, NouvMdp):
        self.mdp = NouvMdp

    def afficher_info(self):
        print("Identifiant: ", self.id)
        print("Nom et prenom: ", self.nom_prenom)


#Definition de la classe Etudiant   
class Etudiant(Compte):
    def __init__(self, id, mdp, nom_prenom, num_etudiant, notes):
        super().__init__(id, mdp, nom_prenom)
        self.num_etudiant = num_etudiant
        self.notes = notes

    def consulter_notes(self):
        print(self.notes)

    def afficher_info(self):
        super().afficher_info()
        print("Numero-etudiant: ", self.num_etudiant)


#Definition de la classe Enseignant
class Enseignant(Compte):
    def __init__(self, id, mdp, nom_prenom, cours, notes_PI):
        super().__init__(id, mdp, nom_prenom)
        self.cours = cours
        self.notes_PI = []
    
    def ajouter_note(self, note):
        self.notes.append(note)

    def modifier_note(self, NouvNote, etudiant):
        self.notes_PI[etudiant] = NouvNote

    def consulter_notes(self):
        print(self.notes_PI)

    def afficher_info(self):
        super().afficher_info()
        print("Cours enseigné: ", self.cours)


etudiant1 = Etudiant("armin_123", "123abc", "Armin",2,  [18, 16.5, 20, 17])
etudiant1.consulter_notes()

    
