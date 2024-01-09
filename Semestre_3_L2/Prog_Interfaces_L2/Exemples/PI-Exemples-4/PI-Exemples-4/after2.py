from tkinter import *
from tkinter import ttk
import time
from turtle import bgcolor


class Horloge(Tk):
    def __init__(self):
        super().__init__()
        self.title('Horloge digitale')
        self.resizable(0, 0)
        self.geometry('250x80')

        self.style = ttk.Style(self)
        self.style.configure(
            'TLabel',
            background='ivory',
            foreground='black')

        self.label = ttk.Label(
            self,
            background= "ivory",
            text=self.time_string(),
            font=('Digital-7', 40))

        self.label.pack(expand=True)

        self.label.after(1000, self.update)

    def time_string(self):
        return time.strftime('%H:%M:%S')

    def update(self):
       self.label.configure(text=self.time_string())
       self.label.after(1000, self.update)


h = Horloge()
h.mainloop()
