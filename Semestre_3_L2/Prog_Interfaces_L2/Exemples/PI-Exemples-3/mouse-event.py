from tkinter import *

LARGEUR = 480
HAUTEUR = 320

def clic(event):
    X = event.x
    Y = event.y
    r = 20
    cnv.create_rectangle(X-r, Y-r, X+r, Y+r,\
         outline = 'black',fill = 'green')

def effacer():
    cnv.delete(ALL)

app= Tk()

cnv = Canvas(app, width = LARGEUR, \
    height = HAUTEUR, bg = 'white')
cnv.pack(padx = 5, pady = 5)

cnv.bind('<Button-1>', clic)
cnv.pack(padx =5, pady =5)

Button(app, text = 'Effacer', \
    command = effacer).\
        pack(side = LEFT,padx = 5,pady = 5)
Button(app, text = 'Quitter', \
    command = app.destroy).pack()

app.mainloop()

