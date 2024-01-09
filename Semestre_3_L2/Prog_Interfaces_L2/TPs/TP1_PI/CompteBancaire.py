

#Definition de la classe CompteBancaire
class CompteBancaire:
    #Le constructeur
    def __init__(self, numeroCompte:int, nom:str, solde:float):
        self.numeroCompte = numeroCompte
        self.nom = nom
        self.solde = solde
    #La méthode crediter()
    def crediter(self, montant:float):
        self.solde += montant

    #La méthode debiter()
    def debiter(self, montant:float):
        if self.solde >= montant:
            self.solde -= montant
    #La méthode virementVers()
    def virementVers(self, vers, montant:float):
        if self.solde >= montant:
            vers.crediter(montant)
            self.debiter(montant)
        print("Virement de ",montant," euros vers le compte num  ", vers.numeroCompte)
    #La méthode afficher()
    def afficher(self):
        print("Numero du compte: ", self.numeroCompte)
        print("Proprietaire: ", self.nom)
        print("Solde: ", self.solde)
    
#Création d'un compte bancaire
#compte_1 = CompteBancaire(345667154, "Audrey Haines", 2450.54)
#Affichage les infos du compte
#compte_1.afficher()
#Versement d'un montant avec la méthode crediter()
#compte_1.crediter(200)
#Retrait d'un montant avec la méthode debiter()
#compte_1.debiter(550)
#compte_1.afficher()
#Création d'un deuxième compte
#compte_2 = CompteBancaire(5645662454, "Marcus Brown", 1240.67)
#Affichage les infos du compte
#compte_2.afficher()
#Virement d'un montant du compte_1 vers le compte_2
#compte_1.virementVers(compte_2, 400)
#Affichage les infos du compte
#compte_2.afficher()




