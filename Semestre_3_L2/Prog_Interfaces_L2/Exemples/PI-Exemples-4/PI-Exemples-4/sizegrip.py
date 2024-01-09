from tkinter import *
from tkinter import ttk

fen = Tk()
fen.geometry('300x200')
fen.resizable(True, True)

fen.columnconfigure(0, weight=1)
fen.rowconfigure(0, weight=1)

sg = ttk.Sizegrip(fen)
sg.grid(row=1, sticky=SE)

fen.mainloop()