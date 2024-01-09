#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
        self.creerwidget()
    
    def creerwidget(self):
        l1 = Label(self, text = "Nom: ")
        l2 = Label(self, text = "Prénom: ")
        e1 = Entry(self)
        e2 = Entry(self)

        l1.grid(row = 0, column = 0, sticky = W, pady=2)
        l2.grid(row = 1, column = 0, sticky = W, pady=2)

        e1.grid(row = 0, column = 1, sticky = W, pady=2)
        e2.grid(row = 1, column = 1, sticky = W, pady=2)


app = Application() 
app.mainloop()
