#Importer le module tkinter
import tkinter as tk

#Creer l'application en tant que classe
class Application(tk.Tk): 
    def __init__(self):
        tk.Tk.__init__(self) 

app = Application()
app.title("Cours de Prog d'interfaces") 
app.mainloop()

