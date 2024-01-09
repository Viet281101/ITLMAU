#Importer le module tkinter
import tkinter as tk
#Importer la classe Canvas
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 
    def __init__(self):
        tk.Tk.__init__(self) 

app = Application() 
cnv = Canvas(app, width = 300, height = 300)
cnv.pack()

app.resizable(False, False)


app.mainloop()
