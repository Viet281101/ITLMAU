from tkinter import *
from tkinter import ttk

class App(Tk):
    def __init__(self):
        super().__init__()
        self.geometry('300x100')

        self.style = ttk.Style(self)

        self.button = ttk.Button(self, text='3 secondes')
        self.button['command'] = self.start
        self.button.pack(expand=True, ipadx=10, ipady=5)

    def start(self):
        self.change_button_color('red')
        self.after(3000,lambda: self.change_button_color('black'))

    def change_button_color(self, color):
        self.style.configure('TButton', foreground=color)

app = App()
app.mainloop()