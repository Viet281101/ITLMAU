from tkinter import *

def f(event):
    t=event.keysym
    print("Touche pressée :", t)
def g(event):
    x=event.x
    y=event.y
    print("Position :", x, y)

app = Tk()
app.bind("<Key>", f)
app.bind("<Motion>",g)
app.mainloop()
