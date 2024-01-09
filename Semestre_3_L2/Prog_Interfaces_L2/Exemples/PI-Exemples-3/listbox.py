from tkinter import *

app = Tk()

liste = Listbox(app)
liste.insert(1, "Bleu")
liste.insert(2, "Rouge")
liste.insert(3, "Vert")
liste.insert(4, "Jaune")
liste.insert(5, "Orange")
liste.insert(6, "Noir")

liste.pack()
app.mainloop()

