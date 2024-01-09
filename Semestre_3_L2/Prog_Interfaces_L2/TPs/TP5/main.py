
from ctypes import sizeof
from tkinter import *
from tkinter import messagebox
from tkinter import ttk
from tkinter.font import BOLD
from PIL import ImageTk, Image
import pygame

## Classe qui représente le jeu
class Jeu(Tk):
    def __init__(self):
        super().__init__()
        self.startJeu()

    #     self.list_choix = ['3x3', '4x4', '5x5', '6x6', '7x7', '8x8', '9x9', '10x10']
    #     self.box_choix = ttk.Combobox(self, width=6, values=[self.list_choix[t] for t in range(0, len(self.list_choix))])
    #     self.box_choix.grid(row = 1, column= 0)
    #     self.start_btn = Button(self, text = "Jouer", command = self.startJeu)
    #     self.start_btn.grid(row=1, column=1)

    # def tailleJeu(self) -> int:
    #     taille = 0
    #     if self.box_choix.get() == '3x3':
    #         taille = 3
    #     elif self.box_choix.get() == '4x4':
    #         taille = 4
    #     elif self.box_choix.get() == '5x5':
    #         taille = 5
    #     elif self.box_choix.get() == '6x6':
    #         taille = 6
    #     elif self.box_choix.get() == '7x7':
    #         taille = 7
    #     elif self.box_choix.get() == '8x8':
    #         taille = 8
    #     elif self.box_choix.get() == '9x9':
    #         taille = 9
    #     elif self.box_choix.get() == '10x10':
    #         taille = 10
    #     return taille

    def startJeu(self):
        playMusic()
        ### Créer les différents widgets de la fenêtre
        ## Boutons et plateau
        self.plateau = Plateau(self, 500, 650)
        self.plateau.grid(row = 0, column = 0)

        frame_btn = Frame(self,width = 200, height = 650, bg= 'ivory')
        frame_btn.grid(row = 0, column = 1)

        self.btn_verification = Button(frame_btn,text = "Vérifier", fg = 'black', command=self.validation, width= 10, highlightbackground='ivory')
        self.btn_verification.place(x = 50 , y=50)

        self.btn_indice = Button(frame_btn,text = "Indice", command=self.indice, width= 10, highlightbackground='ivory')
        self.btn_indice.place(x = 50, y=100)

        self.btn_reset = Button(frame_btn,text = "Réinitialiser", command=self.confirmBox, width= 10, highlightbackground='ivory')
        self.btn_reset.place(x = 50, y=150)

        ## Musique bouton
        self.icon_play = ImageTk.PhotoImage(file = "volume-icon-play.png")
        self.icon_pause = ImageTk.PhotoImage(file = "volume-icon-pause.png")

        self.btn_music = Button(frame_btn, image = self.icon_play, relief=FLAT, command = self.changeIcon)
        self.btn_music.image = self.icon_play
        self.btn_music.place(x = 10 , y = 10)

        ## Setting icon bouton
        self.setting_icon = Image.open("setting_icon.png")
        self.setting_icon=self.setting_icon.resize((30,30))
        self.setting_icon=ImageTk.PhotoImage(self.setting_icon) 
        self.setting_bouton = Button(frame_btn, image=self.setting_icon)
        self.setting_bouton.image = self.setting_icon
        self.setting_bouton.bind("<Button>", lambda e: KeyBind(self))
        self.setting_bouton.place(x = 160 , y = 5)

        ## Texte zone
        self.texte_action = Text(frame_btn, width = 23, height=20)
        self.texte_action.place(x = 10, y = 300)
        self.scroll = Scrollbar(frame_btn, command = self.texte_action.yview)
        self.texte_action.configure(yscrollcommand = self.scroll.set)

        self.text_reste = Text(frame_btn, width=23, height=3)
        self.text_reste.place(x = 10, y = 200)

        self.nbr_reste = "Le nombre des reines qu'il reste à placer : {}\n\n"
        self.placee_act = "Une reine est placée dans la case ({0}, {1})\n\n"
        self.retiree_act = "Une reine est retirée dans la case ({0}, {1})\n\n"
        self.indice_act = "Indice: Vous pouvez placer une reine dans la case ({0}, {1})\n\n"
        self.verifi_act_inval = "Vérification: La configuration est invalide !\n\n"
        self.verifi_act_val = "Vérification: La configuration est valide !\n\n"

    def showAct(self):
        pos = self.plateau.getCasePos()
        print(pos[1])
        print(pos[2])

    def changeIcon(self):
        if self.btn_music.image == self.icon_play:
            self.btn_music.config(image=self.icon_pause)
            self.btn_music.image = self.icon_pause
            stopMusic()
        else:
            self.btn_music.config(image=self.icon_play)
            self.btn_music.image = self.icon_play
            playMusic()

    def confirmBox(self):
        confirm = messagebox.askquestion('Confirm Box', "Etes-vous sur de \n d'initialiser l'échiquier ?", icon='warning')
        if confirm == 'yes':
            self.resetAll()

    def validation(self):
        if self.plateau.verifieConfiguration():
            self.btn_verification['fg'] = 'green'
            self.texte_action.insert("1.0", self.verifi_act_val)
            self.text_reste.insert("1.0", self.nbr_reste.format(self.plateau.nbrReste))
            self.plateau.nbrReste -= 1
        else:
            self.btn_verification['fg'] = 'red'
            self.texte_action.insert("1.0", self.verifi_act_inval)
            self.text_reste.insert("1.0", self.nbr_reste.format(self.plateau.nbrReste))
            self.plateau.nbrReste -= 1

    def indice(self):
        indice= self.plateau.solution()
        if indice[0]:
            self.btn_indice['fg'] = 'green'
            case = self.plateau.getCase(indice[1], indice[2])
            self.texte_action.insert("1.0", self.indice_act.format(indice[1], indice[2]))
            case['text'] = 'X'
            case['fg'] = 'green'
            case.after(1000,case.reset)
        else:
            self.btn_indice['fg'] = 'red'
    
    def resetAll(self):
        self.plateau.reset()


### Keybind window
class KeyBind(Toplevel):
    def __init__(self, master = None):
        super().__init__(master=master)
        self.title("Keybind Setting")
        self.labelKey()
    
    def labelKey(self):
        nbr_ligne = 0
        self.lbl_key_enter = Label(self, text ="'ENTER' ou 'V': ", font=(BOLD, 12))
        self.lbl_key_enter.grid(row = nbr_ligne, column = 0, sticky = W, pady = 1)
        self.lbl_ent_comment = Label(self, text=" pour vérifier les actions")
        self.lbl_ent_comment.grid(row = nbr_ligne, column = 1, sticky = W, pady = 1)

        self.lbl_key_space = Label(self, text ="'SPACE' ou 'I': ", font=(BOLD, 12))
        self.lbl_key_space.grid(row = nbr_ligne + 1, column = 0, sticky = W, pady = 1)
        self.lbl_spc_comment = Label(self, text=" pour indice de placer une reine dans la case")
        self.lbl_spc_comment.grid(row = nbr_ligne + 1, column = 1, sticky = W, pady = 1)

        self.lbl_key_tab = Label(self, text ="'TAB' ou 'N': ", font=(BOLD, 12))
        self.lbl_key_tab.grid(row = nbr_ligne + 2, column = 0, sticky = W, pady = 1)
        self.lbl_tab_comment = Label(self, text=" pour réinitialiser le jeu")
        self.lbl_tab_comment.grid(row = nbr_ligne + 2, column = 1, sticky = W, pady = 1)

        self.lbl_key_music = Label(self, text ="'S' ou 'M': ", font=(BOLD, 12))
        self.lbl_key_music.grid(row = nbr_ligne + 3, column = 0, sticky = W, pady = 1)
        self.lbl_music_comment = Label(self, text=" pour ouvrir et fermer la musique")
        self.lbl_music_comment.grid(row = nbr_ligne + 3, column = 1, sticky = W, pady = 1)

        self.lbl_key_esc = Label(self, text ="'ESCAPE' ou 'Q': ", font=(BOLD, 12))
        self.lbl_key_esc.grid(row = nbr_ligne + 4, column = 0, sticky = W, pady = 1)
        self.lbl_esc_comment = Label(self, text=" pour quitter le jeu")
        self.lbl_esc_comment.grid(row = nbr_ligne + 4, column = 1, sticky = W, pady = 1)

        self.quitBtn = Button(self, text="Quitter", height = 1, width = 10, fg = 'red', font=("Arial", 13, BOLD), command=self.destroy) 
        self.quitBtn.grid(row = nbr_ligne + 5, columnspan = 2, pady = 4)


## Classe qui représente l'échiquier
class Plateau(Frame):
    cases = []
    ## Constructeur 
    def __init__(self,fenetre : Tk, width, height):
        super().__init__(fenetre, width= width, height =height, bg='ivory')
        ## Créer les cases
        for x in range(0, N):
            for y in range(0, N):
                self.cases.append(Case(self, x, y))
        self.nbrCase = len(self.cases)
        self.nbrReine = 0
        self.nbrReste = self.nbrCase - self.nbrReine
    
    def getCase(self, x:int, y:int) -> int:
        for c in self.cases:
            if c.x == x and c.y == y:
                return c
    
    def getCasePos(self):
        for case in self.cases:
            if case.estOccupee():
                for i in range(0,N):
                    for j in range(0, N):
                        return (True, i, j)


    def solution(self):
        if self.verifieConfiguration():
            for i in range(0,N):
                if self.compteLigne(i) == 0:
                    for j in range(0, N):
                        c= self.getCase(i,j)
                        c['text'] = 'X'
                        c.occupee = True
                        if self.verifieConfiguration():
                            c.reset()
                            return (True, i, j)
                        else:
                            c.reset() 
        return (False, -1, -1)

    def compteDiagonale(self, k:int) -> int:
        nb = 0
        min = 0
        max = 0
        if k < 0:
            min = -k
            max = N
        else:
            min = 0
            max = N - k

        for i in range(min ,max):
            for c in self.cases:
                if c.x == i and c.y == i+k and c.estOccupee():
                    nb +=1
        return nb

    def compteAntidiagonale(self, k:int) -> int:
        nb = 0
        min = 0
        max = 0
        if k < 0:
            min = -k
            max = N
        else:
            min = 0
            max = N - k
        for i in range(min ,max):
            for c in self.cases:
                if c.x == 7-i and c.y == i+k and c.estOccupee():
                    nb +=1
        return nb

    def compteLigne(self, k:int) -> int:
        nb = 0
        for c in self.cases:
            if c.x == k and c.estOccupee():
                nb +=1
        return nb

    def compteColonne(self, k:int) -> int:
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

    def verifieAntidiagonales(self) -> bool:
        for i in range(-6, 7):
            if self.compteAntidiagonale(i)>1:
                return False
        return True

    def verifieLignes(self) -> bool:
        for i in range(0,N):
            if self.compteLigne(i)>1:
                return False
        return True

    def verifieColonnes(self) -> bool:
        for i in range(0,N):
            if self.compteColonne(i)>1:
                return False
        return True

    def verifieConfiguration(self) -> bool:
        return self.verifieDiagonales() and self.verifieAntidiagonales()\
            and self.verifieLignes() and self.verifieColonnes()

    def reset(self):
        for c in self.cases:
            c.reset()
            
## Classe qui représente une case de l'échiquier
class Case(Button):
    def __init__(self,plateau:Frame, x:int , y:int):
        super().__init__(plateau, text="", width=6, height=4, command=self.clicGauche, highlightbackground='ivory')
        self.plateau = plateau
        self.x = x
        self.y = y
        self.occupee = False
        self.grid(row=x, column=y)
        
    def estOccupee(self) -> bool:
        return self.occupee

    def clicGauche(self):
        if self.estOccupee():
            self.configure(text="")
            self.reineAct()
            self.occupee = False
        else:
            self.configure(text="X", fg='black')
            self.reineAct()
            self.occupee = True

    def reineAct(self):
        clickSound()

    def reset(self):
        self['text'] = ""
        self['fg'] = "black"
        self.occupee = False


## Sound et musique
def playMusic():
    mon_audio.play(-1)
def stopMusic():
    mon_audio.stop()
def clickSound():
    click_sound.play(1)



def main():
    mon_jeu = Jeu()
    mon_jeu.title("N reines")
    mon_jeu.iconphoto(False,PhotoImage(file='Icon.png'))
    
    ## Keybind event
    mon_jeu.bind('<Return>',lambda event:mon_jeu.validation())
    mon_jeu.bind('<v>',lambda event:mon_jeu.validation())

    mon_jeu.bind('<space>',lambda event:mon_jeu.indice())
    mon_jeu.bind('<i>',lambda event:mon_jeu.indice())

    mon_jeu.bind('<Tab>',lambda event:mon_jeu.confirmBox())
    mon_jeu.bind('<n>',lambda event:mon_jeu.confirmBox())

    mon_jeu.bind('<s>', lambda event: mon_jeu.changeIcon())
    mon_jeu.bind('<m>', lambda event: mon_jeu.changeIcon())

    mon_jeu.bind('<Escape>', lambda event: mon_jeu.quit())
    mon_jeu.bind('<q>', lambda event: mon_jeu.quit())

    mon_jeu.mainloop()


if __name__ == '__main__':
    N = 8
    pygame.mixer.init()
    mon_audio = pygame.mixer.Sound("retro.wav")
    mon_audio.set_volume(0.5)
    click_sound = pygame.mixer.Sound("click_01.wav")
    click_sound.set_volume(0.2)
    main()


