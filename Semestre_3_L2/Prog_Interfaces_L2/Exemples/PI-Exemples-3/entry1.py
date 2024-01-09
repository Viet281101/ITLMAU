from tkinter import *

app = Tk()
Label(app,text="Nom").grid(row=0)
Label(app,text="Prénom").grid(row=1)
e1 = Entry(app)
e2 = Entry(app)
e1.grid(row=0, column=1)
e2. grid(row=1, column=1)

app.mainloop()