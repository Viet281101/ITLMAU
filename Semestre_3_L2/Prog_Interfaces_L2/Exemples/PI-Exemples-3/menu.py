
from tkinter import *

app = Tk()
def bonjour():
    print("Bonjour tout le monde!")
menubar = Menu(app)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Nouveau", command=bonjour)
filemenu.add_command(label="Ouvrir", command=bonjour)
filemenu.add_command(label="Enregistrer", command=bonjour)

menubar.add_cascade(label="Fichier", menu=filemenu)

app.config(menu=menubar)
app.mainloop()

