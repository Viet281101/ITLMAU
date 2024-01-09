from tkinter import *

class case:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.valeur = None #Case vide
        #Chaque case est représentée par un bouton
        self.btn = Button(plateau, text="", width=6, height=5, command=self.configurer)
        self.btn.grid(row=x, column=y)

    #Cette méthode configure une case après u ncoup joué
    def configurer(self):
        global joueur_courant
        if not self.valeur: #Si la case n'est pas occupée
            self.btn.configure(text=joueur_courant, bg='snow', fg='black')
            self.valeur = joueur_courant 
            if joueur_courant == "X": #Ajouter la case dans la liste cases_X si le joueur courant est X
                cases_X.append(self)
                joueur_courant= "O"
                status.configure(text="Joueur O")
            elif joueur_courant == "O": #Sinon l'ajouter dans les cases du joueur O
                cases_O.append(self)
                joueur_courant = "X"
                status.configure(text="Joueur X")
        verifier() #Vérifier si la config actuelle est une config gagnate
    #Remettre une case à son état initial
    def reinitialiser(self):
        self.btn.configure(text="", bg='lightgray')
        #vider les listes cases_X et cases_O
        if self.valeur == "X":
            cases_X.remove(self) 
        elif self.valeur == "O":
            cases_O.remove(self) 
        self.valeur = None

#Cette fonction permet de remettre le plateau à l'état initial
def rejouer():
    global joueur_courant
    joueur_courant = 'X' #X est le premier à jouer
    for case in cases:
        case.btn.configure(state=NORMAL)
        case.reinitialiser()
    status.configure(text="Joueur X")
    rejouer_btn.pack_forget() #rendre le boutton "jouer à nouveau" invisible

#Création de la fenêtre
ttt = Tk()
ttt.resizable(False, False)
ttt.title("Tic Tac Toe")
Label(ttt, text="Tic Tac Toe", font=('Ariel', 25)).pack()
status = Label(ttt, text="Joueur X", font=('Ariel', 15), bg='black', fg='ivory')
status.pack(fill=X)
#Bouton s'affichant à la fin de la partie et permettant de relancer la partie
rejouer_btn = Button(ttt, text='Jouer à nouveau?', font=('Ariel', 15), command=rejouer)
#Variable stockant le joueur actuel (mise à jour après chaque coup)
joueur_courant = "X"
#Création du plateau du jeu
plateau = Frame(ttt, width=300, height=300, bg='ivory')
cases = [] # la liste des cases du plateau
cases_X = [] # la liste des cases occupées par le symbole X
cases_O = [] # la liste des cases occupées par le symbole O
#Création des cases du plateau
for x in range(1, 4):
    for y in range(1, 4):
        cases.append(case(x, y))
plateau.pack(pady=5, padx=5)

#Class qui représente une combinaison gagante
class CombiGagnante:
    def __init__(self, x1, y1, x2, y2, x3, y3):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.x3 = x3
        self.y3 = y3
        #cette méthode vérifie si un symbole vérifie cette configuration
    def verif(self, symbole):
        p1_satisfied = False
        p2_satisfied = False
        p3_satisfied = False
        if symbole == 'X':
            for c in cases_X:
                if c.x == self.x1 and c.y == self.y1:
                    p1_satisfied = True
                elif c.x == self.x2 and c.y == self.y2:
                    p2_satisfied = True
                elif c.x == self.x3 and c.y == self.y3:
                    p3_satisfied = True
        elif symbole == 'O':
            for c in cases_O:
                if c.x == self.x1 and c.y == self.y1:
                    p1_satisfied = True
                elif c.x == self.x2 and c.y == self.y2:
                    p2_satisfied = True
                elif c.x == self.x3 and c.y == self.y3:
                    p3_satisfied = True
        return all([p1_satisfied, p2_satisfied, p3_satisfied])
combi_gagnantes = [
    CombiGagnante(1, 1, 1, 2, 1, 3),
    CombiGagnante(2, 1, 2, 2, 2, 3),
    CombiGagnante(3, 1, 3, 2, 3, 3),
    CombiGagnante(1, 1, 2, 1, 3, 1),
    CombiGagnante(1, 2, 2, 2, 3, 2),
    CombiGagnante(1, 3, 2, 3, 3, 3),
    CombiGagnante(1, 1, 2, 2, 3, 3),
    CombiGagnante(3, 1, 2, 2, 1, 3)
]
#Fonction qui désactive les cases à la fin du jeu et affiche le bouton "jouer à nouveau"
def fin():
    for c in cases:
        c.btn.configure(state=DISABLED)
    rejouer_btn.pack()
#vérifie si le plateau contient une config gagnante
def verifier():
    for combi in combi_gagnantes:
        if combi.verif('X'):
            status.configure(text="X a gagné!")
            fin()
            return
        elif combi.verif('O'):
            status.configure(text="O a gagné!")
            fin()
            return
    #si aucune comb gagante n'est satisfaite
    #et toutes les cases occupées = partie nulle
    if len(cases_X) + len(cases_O) == 9:
        status.configure(text="Partie nulle!")
        fin()

ttt.mainloop()