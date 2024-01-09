from tkinter import *
from random import randrange

taille=200
app = Tk()
cnv = Canvas(app, width=taille,\
     height=taille, bg="ivory")
cnv.pack(padx=10, pady=10)
cnv.focus_set()

def dessiner(event):
    a=randrange(taille)
    b= randrange(taille)
    cnv.create_rectangle(a, b, a+20, b+20)
cnv.bind("<Key>", dessiner)

app.mainloop()