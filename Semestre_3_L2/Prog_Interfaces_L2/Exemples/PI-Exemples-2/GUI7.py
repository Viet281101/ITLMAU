#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
    
    def normalscreen(self):
        self.attributes("-fullscreen", False)

app = Application() 
app.attributes("-fullscreen", True)

app.bind("<Escape>", Application.normalscreen)
app.mainloop()

