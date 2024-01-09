
from tkinter import *


class Application(Tk): 
    def __init__(self):
        Tk.__init__(self) 
        self.geometry("250x250")
        self['bg'] = 'white'
        self.title('Gestion des résultats dexamen')
        self.creerWidgets()

    def creerLabel(self):
        Label(self, text="Gestion des résultats", font=("Calibri",-15), bg='white').pack(pady=20)
    
    def creerBoutons(self):
        Button(self,text="Ajouter un étudiant",command = self.ajouterEtudiant, font=('Calibri',-15),width=20, highlightbackground='white').pack()
        Button(self,text="Afficher les résultats",command=self.afficherResultat,font=('Calibri',-15),width=20,highlightbackground='white').pack()
        Button(self,text="Consulter les notes",command=self.consulterNotes,font=('Calibri',-15),width=20,highlightbackground='white').pack()
        Button(self,text="Quitter", command= self.quit, font=('Calibri',-15),width=20,highlightbackground='white').pack()
    def creerWidgets(self):
        self.creerLabel()
        self.creerBoutons()

    def ajouterEtudiant(self):
        win = Toplevel(self, bg='white')
        win.title("Ajout d'un étudiant")
        self.formulaire(win)
    def afficherResultat(self):
        win = Toplevel(self, bg='white')
        win.title("Les résultats d'examen")
        self.resultat(win)
    def consulterNotes(self):
        win = Toplevel(self, bg='white')
        win.title("Les notes d'examen")
        self.notes(win)

  
    @staticmethod
    def formulaire(win):
        Label(win, text="Ajout d'un étudiant", font=('Calibri',-15), bg='white').grid(columnspan=2)
        Label(win, text="Nom", font=('Calibri',-15), bg='white').grid(row=1, column=0,sticky = NW)
        Label(win, text="Note CC - 1", font=('Calibri',-15), bg='white').grid(row=2, column=0,sticky = NW)
        Label(win, text="Note CC - 2", font=('Calibri',-15), bg='white').grid(row=3, column=0,sticky = NW)
        Label(win, text="Note CC - 3", font=('Calibri',-15), bg='white').grid(row=4, column=0,sticky = NW)
        Entry(win).grid(row=1, column=1,sticky = NW)
        Entry(win).grid(row=2, column=1,sticky = NW)
        Entry(win).grid(row=3, column=1,sticky = NW)
        Entry(win).grid(row=4, column=1,sticky = NW)
        Button(win,text="Ajouter",width=15,font=('Calibri',-15), highlightbackground='white').grid(columnspan=2, sticky=NE)
        Button(win,command=win.destroy,text="Annuler",width=15,font=('Calibri',-15), highlightbackground='white').grid(columnspan=2,sticky=NE)
    @staticmethod
    def notes(win):
        Label(win, text="Les notes de l'examen", font=('Calibri',-15), bg='white').grid(columnspan=5)
        Label(win, text="Numéro-étudiant", font=('Calibri',-15), bg='white').grid(row=1, column=0,sticky = NW, padx=15)
        Label(win, text="Nom", font=('Calibri',-15), bg='white').grid(row=1, column=1,sticky = NW, padx=15)
        Label(win, text="CC-1", font=('Calibri',-15), bg='white').grid(row=1, column=2,sticky = NW, padx=15)
        Label(win, text="CC-2", font=('Calibri',-15), bg='white').grid(row=1, column=3,sticky = NW, padx=15)
        Label(win, text="CC-3", font=('Calibri',-15), bg='white').grid(row=1, column=4,sticky = NW, padx=15)

        Button(win,command=win.destroy,text="Quitter",width=15,font=('Calibri',-15), highlightbackground='white').grid(columnspan=5)
    @staticmethod
    def resultat(win):
        Label(win, text="Les résultats de l'examen", font=('Calibri',-15), bg='white').grid(columnspan=5)
        Label(win, text="Numéro-étudiant", font=('Calibri',-15), bg='white').grid(row=1, column=0,sticky = NW, padx=15)
        Label(win, text="Nom", font=('Calibri',-15), bg='white').grid(row=1, column=1,sticky = NW, padx=15)
        Label(win, text="Résultat", font=('Calibri',-15), bg='white').grid(row=1, column=2,sticky = NW, padx=15)

        Button(win,command=win.destroy,text="Quitter",width=15,font=('Calibri',-15), highlightbackground='white').grid(columnspan=5)

app=Application()
app.mainloop() 