from tkinter import *
from tkinter import ttk

fen = Tk()
fen.geometry('300x120')
fen.grid()

pb = ttk.Progressbar(fen,orient='horizontal',mode='determinate',length=280)
pb.grid(column=0, row=0, columnspan=2, padx=10, pady=20)

start = ttk.Button(fen,text='Start',command=pb.start)
start.grid(column=0, row=1, padx=10, pady=10, sticky=E)

stop = ttk.Button(fen,text='Stop',command=pb.stop)
stop.grid(column=1, row=1, padx=10, pady=10, sticky=W)

fen.mainloop()