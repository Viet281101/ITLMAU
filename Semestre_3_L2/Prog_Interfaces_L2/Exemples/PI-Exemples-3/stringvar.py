from tkinter import *

app=Tk()
msg=StringVar()
entree=Entry(app, textvariable=msg)
entree.pack( padx=20, pady=10)

lbl=Label(app, textvariable=msg)
lbl.pack(padx=20, pady=10)

app.mainloop()