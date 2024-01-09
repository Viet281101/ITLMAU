from tkinter import *
class Application(Tk): 
    def __init__(self):
        Tk.__init__(self) 
        self.creerBouton()
    def creerBouton(self):
        texteBouton = "Quitter"
        commandeBouton = self.quit
        bouton = Button(self, text = texteBouton,\
        command = commandeBouton)
        bouton.pack(padx = 15, pady = 15)

app = Application()
app.mainloop()