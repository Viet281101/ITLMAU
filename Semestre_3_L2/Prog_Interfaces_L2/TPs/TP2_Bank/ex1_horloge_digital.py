
#Importer le module tkinter
import tkinter as tk
import time

#Creer l'application en tant que classe
class Application(tk.Tk): 
	def __init__(self):
		tk.Tk.__init__(self)
		self.root = tk.Tk()
		self.label = tk.Label(text="", font=('Times New Roman', 40))
		self.label.pack()
		self.updateHorloge()
		self.Boutons()

	def updateHorloge(self):
		now = time.strftime("%H:%M:%S")
		self.label.configure(text = now)
		self.root.after(1000, self.updateHorloge)

	def Boutons(self):
		self.bouton1 = tk.Button(self, text="Mettre a jour") 
		self.bouton2 = tk.Button(self, text="Quitter", command=self.quit) 
		self.bouton1.pack()
		self.bouton2.pack()


app = Application() 
app.title("Horloge Digital")
app.mainloop()
