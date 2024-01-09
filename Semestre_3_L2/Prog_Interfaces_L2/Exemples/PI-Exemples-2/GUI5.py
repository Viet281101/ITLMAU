#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 
    def __init__(self):
        tk.Tk.__init__(self) 
    

def quit_a():
    a.destroy()
    if closed[1]:
        app.destroy()
    else:
        closed[0] = True

def quit_b():
    b.destroy()
    if closed[0]:
        app.destroy()
    else:
        closed[1] = True

app = Application() 
a = Toplevel(app, bg="red")
b = Toplevel(app, bg="ivory")

a.protocol("WM_DELETE_WINDOW",quit_a)
b.protocol("WM_DELETE_WINDOW",quit_b)

closed=[False,False]

app.withdraw()

app.mainloop()