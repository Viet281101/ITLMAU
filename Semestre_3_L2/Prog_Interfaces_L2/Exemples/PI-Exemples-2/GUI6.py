#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    closed=[False,False]

    def __init__(self):
        tk.Tk.__init__(self) 
    @classmethod
    def quit_a(cls):
        a.destroy()
        if cls.closed[1]:
            app.destroy()
        else:
            cls.closed[0] = True
    @classmethod
    def quit_b(cls):
        b.destroy()
        if cls.closed[0]:
            app.destroy()
        else:
            cls.closed[1] = True

app = Application() 
a = Toplevel(app, bg="red")
b = Toplevel(app, bg="ivory")

a.protocol("WM_DELETE_WINDOW",Application.quit_a)
b.protocol("WM_DELETE_WINDOW",Application.quit_b)

app.withdraw()
app.mainloop()

