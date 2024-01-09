#Importer le module tkinter
from time import strftime
from tkinter import *

#Creer l'application en tant que classe
class Application(Tk): 
    heure : Label
    def __init__(self):
        Tk.__init__(self) 
        self.title("Horloge digitale")
        self.creerWidgets()

    def creerWidgets(self):
        self.creerLabel()
        self.creerBoutons()
    def creerLabel(self):
        texte = strftime("%H:%M:%S")
        self.heure = Label(self, text=texte)
        self.heure.pack(padx = 15, pady = 15)
    def creerBoutons(self):
        #Creer le bouton "Mettre a jour"
        commandeBouton1 = self.updateLabel
        texte1 = "Mettre à jour"
        bouton1 = Button(self, text=texte1, command=commandeBouton1)
        bouton1.pack(padx = 15, pady = 15, fill=X)
        #Creer le bouton "Quitter"
        commandeBouton2 = self.quit
        texte2 = "Quitter"
        bouton2 = Button(self, text=texte2, command=commandeBouton2)
        bouton2.pack(padx = 15, pady = 15, fill=X)

    def updateLabel(self):
        self.heure['text'] = strftime("%H:%M:%S")



app = Application()
app.mainloop()