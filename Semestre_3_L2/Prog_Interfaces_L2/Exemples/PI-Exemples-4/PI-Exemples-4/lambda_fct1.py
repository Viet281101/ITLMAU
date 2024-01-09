from tkinter import *
from tkinter import ttk

fen= Tk()
fen.geometry("200x200")

def afficher_msg(text):
   Label(fen, text=text,font=('Ariel 12 bold')).pack()

btn1 = Button(fen, text="Bonjour")
btn1.pack(pady=10)
btn1.bind("<Button-1>", lambda event: afficher_msg("Bonjour"))

btn2=Button(fen, text="Hello")
btn2.pack(pady=10)

btn3=Button(fen, text="Hola")
btn3.pack(pady=10)

fen.mainloop()