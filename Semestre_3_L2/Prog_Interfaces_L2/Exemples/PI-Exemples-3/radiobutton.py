from tkinter import *

def sel():
  selected = "Vous avez sélectionné : " \
    + v.get()
  label.config(text = selected)

app = Tk()
v = StringVar()
v.set("Python")

r1 = Radiobutton(app, text="Python", \
  variable=v, value="Python", command=sel)
r1.pack(anchor = W)
r2 = Radiobutton(app, text="Java", \
  variable=v, value="Java", command=sel)
r2.pack(anchor = W)
r3 = Radiobutton(app, text="PHP", \
  variable=v, value="PHP", command=sel)
r3.pack(anchor = W)

label = Label(app)
label.pack()
app.mainloop()