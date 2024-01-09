
from tkinter import *
from PIL import ImageTk, Image


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
        print("Virement de ", montant," euros vers le compte num  ", vers.numeroCompte)

    #La méthode afficher() sur Shell
    def afficher(self):
        print("Numero du compte: ", self.numeroCompte)
        print("Proprietaire: ", self.nom)
        print("Solde: ", self.solde)


class Application(Tk): 
    def __init__(self):
        Tk.__init__(self) 
        self.geometry("300x450")
        self['bg'] = 'white'
        self.title('Application bancaire')
        self.creerWidgets()

    def creerLabels(self):
        Label(self, text="Gérez votre compte", \
            font=("Calibri",-15), bg='white').pack(pady=10)
        Label(self, text="en toute simplicité!", \
            font=("Calibri",-15), bg='white').pack(pady=10)

    def creerImage(self):
        img=Image.open("imgBanque.png")
        img=img.resize((150,150))
        img=ImageTk.PhotoImage(img)
        label_img = Label(self, image=img, bg='white')
        label_img.image = img
        label_img.pack(pady=50)

    def creerBoutons(self):
        Button(self,text="Créer un compte",font=('Calibri',-15),\
            width=20, highlightbackground='white').pack()
        Button(self,text="Se connecter",font=('Calibri',-15),\
            width=20,highlightbackground='white').pack()

    def creerWidgets(self):
        self.creerLabels()
        self.creerImage()
        self.creerBoutons()

banque=Application()
banque.mainloop() 