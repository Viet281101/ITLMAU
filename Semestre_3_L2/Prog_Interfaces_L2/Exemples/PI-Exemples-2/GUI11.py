#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 

    def __init__(self):
        tk.Tk.__init__(self) 
        self.creerwidget()
    
    def creerwidget(self):
        frame = Frame(self, width=200, height=200, bg="ivory")
        frame.place(anchor = NW)
        
        l1 = Label(frame, text = "Bonjour", bg="ivory")
        l2 = Label(frame, text = "Bonjour", bg="ivory")
        l3 = Label(frame, text = "Bonjour", bg="ivory")

        l1.place(x = 10, y = 10)
        l2.place(x = 50, y = 50)
        l3.place(x = 90, y = 90)


app = Application()
app.mainloop()
