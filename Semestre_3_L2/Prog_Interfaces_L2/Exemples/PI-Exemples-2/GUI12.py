#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
        self.creerwidget()

    def creerwidget(self): 
        Label(self, text="ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      font="Arial 12").pack(side=TOP, anchor="w")
        Label(self, text="ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      font=("Times New roman", 12, "bold")).pack(side=TOP, anchor="w")
        Label(self, text="ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      font=("{Times New roman} 12 italic")).pack(side=TOP, anchor="w")
        Label(self, text="ABCDEFGHIJKLMNOPQRSTUVWXYZ",
      font=("Courier")).pack(side=TOP, anchor="w")



app = Application()
app.mainloop()