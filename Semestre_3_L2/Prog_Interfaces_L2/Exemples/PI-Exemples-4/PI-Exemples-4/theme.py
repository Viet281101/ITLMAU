from tkinter import *
from tkinter import ttk


class App(Tk):
    def __init__(self):
        super().__init__()
        self.geometry('480x250')
        self.style = ttk.Style(self)

        label = ttk.Label(self, text='Nom:')
        label.grid(column=0, row=0, padx=10, pady=10,  sticky='w')
        textbox = ttk.Entry(self)
        textbox.grid(column=1, row=0, padx=10, pady=10,  sticky='w')
        btn = ttk.Button(self, text='Afficher')
        btn.grid(column=2, row=0, padx=10, pady=10,  sticky='w')

        self.selected_theme = StringVar()
        theme_frame = ttk.LabelFrame(self, text='Thèmes')
        theme_frame.grid(padx=10, pady=10, ipadx=20, ipady=20, sticky='w')

        for theme_name in self.style.theme_names():
            rb = ttk.Radiobutton(
                theme_frame,
                text=theme_name,
                value=theme_name,
                variable=self.selected_theme,
                command=self.change_theme)
            rb.pack(expand=True, fill='both')

    def change_theme(self):
        self.style.theme_use(self.selected_theme.get())


app = App()
app.mainloop()
