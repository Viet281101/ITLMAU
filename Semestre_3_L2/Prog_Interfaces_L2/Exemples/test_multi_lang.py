
import tkinter as Tk


def change_language_eng():
    root.title('Program')
    menuButton.config(text='Menu')


def change_language_spa():
    root.title('Programa')
    menuButton.config(text='Menú')

    
root = Tk.Tk()
root.title('Program')
menuButton = Tk.Button(root, text='Menu')
engButton = Tk.Button(root, text='English', command=change_language_eng)
spaButton = Tk.Button(root, text='Spanish', command=change_language_spa)
menuButton.grid(row=0, column=0)
engButton.grid(row=1, column=0)
spaButton.grid(row=2, column=0)
root.mainloop()

