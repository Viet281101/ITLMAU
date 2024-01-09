from tkinter import *

app = Tk()
entree = Entry(app)
entree.pack()
def afficher():
    print(entree.get())

bouton=Button(app, text="Afficher", \
    command=afficher)
bouton.pack(padx=50, pady=10)

app.mainloop()

