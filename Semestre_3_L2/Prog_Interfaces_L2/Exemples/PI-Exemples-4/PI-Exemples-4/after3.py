from tkinter import *

SIDE=400
PAD=SIDE//12

#déplacement de la balle
def move(dx, dy):
    ulx, uly, lrx, lry = list(map(int, cvs.coords(ball)))
    if ulx <=0 or lrx >=SIDE:
        dx=-dx
    elif uly<=0 or lry>=SIDE:
        dy=-dy
    cvs.move(ball, dx, dy)
    cvs.after(30, move, dx, dy)

#créer la fenetre
fen=Tk()
cvs=Canvas(fen, width=SIDE, height=SIDE, highlightthickness=0,
           bg="ivory")
cvs.pack(padx=PAD, pady=PAD)

#créer la balle
n=20
R=SIDE//n
x0=200
y0=40
ball=cvs.create_oval(x0, y0, 2*R+x0, 2*R+y0, outline='OrangeRed2',
                     fill='OrangeRed2')

move(4, 6)
fen.mainloop()