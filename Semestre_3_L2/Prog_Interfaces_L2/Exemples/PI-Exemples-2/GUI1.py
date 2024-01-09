#Importer le module tkinter
import tkinter as tk

#Creer l'application en tant que classe
class Application(tk.Tk): 
    def __init__(self):
        tk.Tk.__init__(self) 
        self.creer_widgets()
    def creer_widgets(self):
        self.label = tk.Label(self, text="J'adore Python !")
        self.bouton = tk.Button(self, text="Quitter", command=self.quit) 
        self.label.pack()
        self.bouton.pack()

app = Application() 
app.title("Ma Première App") 
app.mainloop()

