from tkinter import *

app = Tk()
app.geometry("100x100")
var1 = IntVar()
Checkbutton(app,text="Oui",variable=var1)\
    .grid(row=0,sticky=W)
var2 = IntVar()
Checkbutton(app,text="Non",variable=var2)\
    .grid(row=1,sticky=W)

app.mainloop()
