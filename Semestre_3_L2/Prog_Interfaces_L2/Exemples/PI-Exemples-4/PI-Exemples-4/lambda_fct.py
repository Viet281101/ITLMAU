from tkinter import *
from tkinter import ttk

fen= Tk()
fen.geometry("200x200")

def afficher_msg(text):
   Label(fen, text=text,font=('Ariel 12 bold')).pack()

Button(fen, text="Bonjour" ,command= lambda:
afficher_msg("Bonjour")).pack(pady=10)

Button(fen, text="Hello" ,command= lambda:
afficher_msg("Hello")).pack(pady=10)

Button(fen, text="Hola" ,command= lambda:
afficher_msg("Hola")).pack(pady=10)

fen.mainloop()