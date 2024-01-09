from tkinter import *

taille = 400
app = Tk()

frame = Frame(app, background="black")
frame.pack()

cnv = Canvas(frame, width=taille, \
    height=taille, bg="ivory")
cnv.pack(padx=20, pady=20)

btn = Button(frame, text="Coucou!")
btn.pack(pady=20)

app.mainloop()
