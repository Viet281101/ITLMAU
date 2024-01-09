from tkinter import *
from PIL import Image, ImageTk

fenetre = Tk()
fenetre.geometry("200x200")

icone = Image.open("up8.png")
icone = ImageTk.PhotoImage(icone)
fenetre.iconphoto(False, icone)

fenetre.mainloop()