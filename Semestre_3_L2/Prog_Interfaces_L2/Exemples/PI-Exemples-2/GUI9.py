#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
        self.creerwidget()
    
    def creerwidget(self):
        frame = Frame(self)
        frame.pack(side = BOTTOM)

        btn1 = Button(self, text="Bouton 1")
        btn1.pack(side = LEFT, fill = BOTH)

        btn2 = Button(self, text="Bouton 2")
        btn2.pack(side = LEFT)

        btn3 = Button(self, text="Bouton 3")
        btn3.pack(side = LEFT)

        btn4 = Button(frame, text="Bouton 4")
        btn4.pack(side = BOTTOM, expand=False)

app = Application() 
app.mainloop()
