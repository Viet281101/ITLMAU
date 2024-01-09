#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
        self.creerwidget()
    
    def creerwidget(self):
        cnv = Canvas(self, width=200, height=200, bg="ivory")
        cnv.pack()
        Button(self, text="Quitter", command=self.quit).pack()

app = Application() 

app.mainloop()

