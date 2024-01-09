
from tkinter import *
import tkinter

#Classe qui représente le jeu
class Jeu(Tk):
    def __init__(self):
        super().__init__()
        #Créer les différents widgets de la fenêtre
        #Boutons et plateau

        self.plateau = Plateau(self, 500, 750)
        self.plateau.grid(row = 0, column = 0)
        

    def validation(self):
        pass

    def indice(self):
        pass

    def resetAll(self):
        pass

#Classe qui représente l'échiquier
class Plateau(Frame):
    cases = [] #liste des cases
    #Constructeur 
    def __init__(self,fenetre : Tk, width, height):
        super().__init__(fenetre, width= width, height =height, bg='ivory')
        #Créer les cases
        

    def solution(self):
        pass
        #à complèter

    def compteDiagonale(self, k):
        nb = 0
        min = 0
        max = 0
        if k < 0:
            min = -k
            max = 8
        else:
            min = 0
            max = 8 - k

        for i in range(min ,max):
            for c in self.cases:
                if c.x == i and c.y == i+k and c.estOccupee():
                    nb +=1
        return nb
    
    def compteAntidiagonale(self, k):
        nb = 0
        min = 0
        max = 0
        if k < 0:
            min = -k
            max = 8
        else:
            min = 0
            max = 8 - k
        for i in range(min ,max):
            for c in self.cases:
                if c.x == 7-i and c.y == i+k and c.estOccupee():
                    nb +=1
        return nb
    
    def compteLigne(self, k):
        nb = 0
        for c in self.cases:
            pass
    #à complèter
    
    def compteColonne(self, k):
        pass
    #à complèter

    def verifieDiagonales(self):
        for i in range(-6, 7):
            if self.compteDiagonale(i)>1:
                return False
        return True

    def verifieAntidiagonales(self):
        for i in range(-6, 7):
            if self.compteAntidiagonale(i)>1:
                return False
        return True

    def verifieLignes(self):
        pass
    #à complèter

    def verifieColonnes(self):
        pass
    #à complèter

    def verifieConfiguration(self):
        pass
    #à complèter

    def reset(self):
        pass
            
#Classe qui représente une case de l'échiquier
class Case(Button):
    def __init__(self,plateau:Frame, x , y):
        pass
    #à complèter
        
    def estOccupee(self):
        return self.occupee
        #à complèter

    def clicGauche(self):
        pass
    #à complèter


mon_jeu = Jeu()
mon_jeu.mainloop()


