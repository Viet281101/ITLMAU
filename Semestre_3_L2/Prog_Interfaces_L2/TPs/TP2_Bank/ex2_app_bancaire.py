
#Importer le module tkinter
import tkinter as tk
from PIL import ImageTk, Image


#Definition de la classe CompteBancaire
class CompteBancaire:
	#Le constructeur
	def __init__(self, numeroCompte:int, nom:str, solde:float):
		self.numeroCompte = numeroCompte
		self.nom = nom
		self.solde = solde

	#La méthode crediter()
	def crediter(self, montant:float):
		self.solde += montant

	#La méthode debiter()
	def debiter(self, montant:float):
		if self.solde >= montant:
			self.solde -= montant

	#La méthode virementVers()
	def virementVers(self, vers, montant:float):
		if self.solde >= montant:
			vers.crediter(montant)
			self.debiter(montant)
		print("Virement de ",montant," euros vers le compte num  ", vers.numeroCompte)

	#La méthode afficher()
	def afficher(self):
		print("Numero du compte: ", self.numeroCompte)
		print("Proprietaire: ", self.nom)
		print("Solde: ", self.solde)


#Creer l'application en tant que classe
class Application(tk.Tk): 
	def __init__(self):
		tk.Tk.__init__(self)
		self.creer_widgets()

	def creer_widgets(self):
		self.label1 = tk.Label(self, text = "Gérez votre compte", font=('Calibri', 15))
		self.label2 = tk.Label(self, text = "en toute simplicité !", font=('Calibri', 15))
		self.label1.pack()
		self.label2.pack()

		img = Image.open("imgBanque.png")
		img = img.resize((150, 150))
		img = ImageTk.PhotoImage(img)
		self.label = tk.Label(self, image = img)
		self.label.pack()



app = Application() 
app.title("Application Bancaire") 
app.mainloop()
