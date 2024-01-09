from tkinter import *
from PIL import Image, ImageTk

fenetre = Tk()
fenetre.geometry("200x200")

icone = Image.open("up8.png")
icone = ImageTk.PhotoImage(icone)
fenetre.tk.call('wm', 'iconphoto', fenetre._w, icone)

fenetre.mainloop()