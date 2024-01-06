from tkinter import *

#Classe qui représente le jeu
class Jeu(Tk):
    def __init__(self):
        super().__init__()
        #Créer les différents widgets de la fenêtre
        #Boutons et plateau
        self.plateau = Plateau(self, 500, 750)
        self.plateau.grid(row = 0, column = 0)
        frame_btn = Frame(self,width = 200, height = 750, bg= 'ivory')
        frame_btn.grid(row = 0, column = 1)
        self.btn_verification = Button(frame_btn,text = "Vérifier", fg = 'black', command=self.validation, width= 10, highlightbackground='ivory')
        self.btn_verification.place(x = 50 , y=100)
        self.btn_indice = Button(frame_btn,text = "Indice", command=self.indice, width= 10, highlightbackground='ivory')
        self.btn_indice.place(x = 50, y=150)
        self.btn_reset = Button(frame_btn,text = "Réinitialiser", command=self.resetAll, width= 10, highlightbackground='ivory')
        self.btn_reset.place(x = 50, y=200)

    def validation(self):
        if self.plateau.verifieConfiguration():
            self.btn_verification['fg'] = 'green'
        else:
            self.btn_verification['fg'] = 'red'

    def indice(self):
        indice= self.plateau.solution()
        if indice[0]:
            self.btn_indice['fg'] = 'green'
            case = self.plateau.getCase(indice[1], indice[2])
            case['text'] = 'X'
            case['fg'] = 'green'
            case.after(1000,case.reset)
        else:
            self.btn_indice['fg'] = 'red'
    
    def resetAll(self):
        self.plateau.reset()


#Classe qui représente l'échiquier
class Plateau(Frame):
    cases = []
    #Constructeur 
    def __init__(self,fenetre : Tk, width, height):
        super().__init__(fenetre, width= width, height =height, bg='ivory')
        #Créer les cases
        for x in range(0, 8):
            for y in range(0, 8):
                self.cases.append(Case(self, x, y))
    
    def getCase(self, x, y):
        for c in self.cases:
            if c.x == x and c.y == y:
                return c

    def solution(self):
        if self.verifieConfiguration():
            for i in range(0,8):
                if self.compteLigne(i) == 0:
                    for j in range(0, 8):
                        c= self.getCase(i,j)
                        c['text'] = 'X'
                        c.occupee = True
                        if self.verifieConfiguration():
                            c.reset()
                            return (True, i, j)
                        else:
                            c.reset() 
        return (False, -1, -1)

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
            if c.x == k and c.estOccupee():
                nb +=1
        return nb
    def compteColonne(self, k):
        nb = 0
        for c in self.cases:
            if c.y == k and c.estOccupee():
                nb +=1
        return nb
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
        for i in range(0,8):
            if self.compteLigne(i)>1:
                return False
        return True
    def verifieColonnes(self):
        for i in range(0,8):
            if self.compteColonne(i)>1:
                return False
        return True
    def verifieConfiguration(self):
        return self.verifieDiagonales() and self.verifieAntidiagonales()\
            and self.verifieLignes() and self.verifieColonnes()

    def reset(self):
        for c in self.cases:
            c.reset()
            
#Classe qui représente une case de l'échiquier
class Case(Button):
    def __init__(self,plateau:Frame, x , y):
        super().__init__(plateau, text="", width=6, height=5, command=self.clicGauche, highlightbackground='ivory')
        self.x = x
        self.y = y
        self.occupee = False
        self.grid(row=x, column=y)
        
    def estOccupee(self):
        return self.occupee

    def clicGauche(self):
        if self.estOccupee():
            self.configure(text="")
            self.occupee = False
        else:
            self.configure(text="X" , fg='black')
            self.occupee = True

    def reset(self):
        self['text'] = ""
        self['fg'] = "black"
        self.occupee = False

mon_jeu = Jeu()
mon_jeu.mainloop()