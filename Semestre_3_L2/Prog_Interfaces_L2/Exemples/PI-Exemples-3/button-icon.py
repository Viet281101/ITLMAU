from tkinter import *
from PIL import ImageTk, Image

class Application(Tk): 
    def __init__(self):
        Tk.__init__(self) 
        self.creerBouton()
    def creerBouton(self):
        commandeBouton = self.quit
        logo = Image.open("red.png")
        logo=logo.resize((40,40))
        logo=ImageTk.PhotoImage(logo) 
        bouton = Button(self, image=logo, command=self.quit)
        bouton.image = logo
        bouton.pack(padx = 15, pady = 15)
app = Application()
app.mainloop()




