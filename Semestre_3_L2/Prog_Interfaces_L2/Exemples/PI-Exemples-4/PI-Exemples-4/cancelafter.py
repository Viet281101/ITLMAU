from tkinter import Tk, Canvas, Button
from random import randrange

def anim(cpt):
    global id_anim
    cnv.delete("all")
    cnv.create_text(SIDE//2, SIDE//2, text =int(cpt), font="Arial 200 bold")
    id_anim=cnv.after(500, anim, cpt+1)

def go():
    cnv.after_cancel(id_anim)
    anim(1)

SIDE=400
root = Tk()
cnv = Canvas(root, width=SIDE, height=SIDE, bg='ivory')
cnv.pack()
btn=Button(root, text="Réintialiser", command=go)
btn.pack()

id_anim=None
anim(1)

root.mainloop()