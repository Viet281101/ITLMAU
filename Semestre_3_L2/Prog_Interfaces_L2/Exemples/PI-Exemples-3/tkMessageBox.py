from tkinter import *
from tkinter import messagebox

app = Tk()
def msg():
   messagebox.showinfo("Info", "Bonjour!")

btn = Button(app, text = "Cliquez ici!", \
   command = msg)
btn.pack()

app.mainloop()