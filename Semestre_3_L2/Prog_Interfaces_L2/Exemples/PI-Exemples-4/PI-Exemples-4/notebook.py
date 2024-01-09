from tkinter import *
from tkinter import ttk

fen = Tk()
fen.geometry('400x300')

notebook = ttk.Notebook(fen)
notebook.pack(pady=10, expand=True)

frame1 = ttk.Frame(notebook, width=400, height=280)
frame2 = ttk.Frame(notebook, width=400, height=280)
frame3 = ttk.Frame(notebook, width=400, height=280)
frame4 = ttk.Frame(notebook, width=400, height=280)

frame1.pack(fill='both', expand=True)
frame2.pack(fill='both', expand=True)
frame3.pack(fill='both', expand=True)
frame4.pack(fill='both', expand=True)

notebook.add(frame1, text='Personal info')
notebook.add(frame2, text='Data & privacy')
notebook.add(frame3, text='Security')
notebook.add(frame4, text='About')


fen.mainloop()