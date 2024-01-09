
#Importer le module tkinter
import tkinter as tk
from tkinter import *

#Creer l'application en tant que classe
class Application(tk.Tk): 
	def __init__(self):
		tk.Tk.__init__(self)
		self['bg'] = 'green'
		self.appBtn()

	def appBtn(self):
		ajoutBtn = tk.Button(self, text="Ajouter un étudiant", height = 2, width = 30, font=("Arial", 10), command=AjouterEtudiants) 
		ajoutBtn.pack()
		afficheBtn = tk.Button(self, text="Afficher les résultats", height = 2, width = 30, font=("Arial", 10), command=AfficherResultats) 
		afficheBtn.pack()
		quitBtn = tk.Button(self, text="Quitter", height = 2, width = 30, font=("Arial", 10), command=self.quit) 
		quitBtn.pack()


class AjouterEtudiants(tk.Tk):
	def __init__(self):
		tk.Tk.__init__(self)
		self['bg'] = 'black'
		self.title("Ajouter un étudiant")
		self.inputInfo()

	def inputInfo(self):
		n = 0
		self.notes = []

		#### Label:
		nomLbl = Label(self, text = "Nom: ", font=("Arial", 12), fg = 'red', bg = 'black')
		NotesLbl = Label(self, text = "Notes d'etudiant: ", font=("Arial", 12), fg = 'white', bg = 'black')
		anglaisLbl = Label(self, text = "Anglais: ", font=("Arial", 12), fg = 'red', bg = 'black')
		mathLbl = Label(self, text = "Math: ", font=("Arial", 12), fg = 'red', bg = 'black')
		physiqueLbl = Label(self, text = "Physique: ", font=("Arial", 12), fg = 'red', bg = 'black')

		#### Input:
		self.nomInput = Entry(self)
		self.anglaisInput = Entry(self)
		self.mathInput = Entry(self)
		self.physiqueInput = Entry(self)

		#### Setup position:
		nomLbl.grid(row = n, column = 0, sticky = W, pady = 1)
		NotesLbl.grid(row = n+1, columnspan=2, sticky = W, pady = 2)
		anglaisLbl.grid(row = n+2, column = 0, sticky = W, pady = 1)
		mathLbl.grid(row = n+3, column = 0, sticky = W, pady = 1)
		physiqueLbl.grid(row = n+4, column = 0, sticky = W, pady = 1)

		self.nomInput.grid(row = n, column = 1, sticky = W, pady = 1)
		self.anglaisInput.grid(row = n+2, column = 1, sticky = W, pady = 1)
		self.mathInput.grid(row = n+3, column = 1, sticky = W, pady = 1)
		self.physiqueInput.grid(row = n+4, column = 1, sticky = W, pady = 1)

		#### Button:
		updateBtn = tk.Button(self, text="Ajouter", height = 1, width = 25, font=("Arial", 10), command=self.updateInfo) 
		updateBtn.grid(row = n+5, columnspan=2, sticky = W, pady = 1)

		quitBtn = tk.Button(self, text="Quitter", height = 1, width = 25, font=("Arial", 10), command=self.destroy) 
		quitBtn.grid(row = n+6, columnspan=2, sticky = W, pady = 1)


	def updateInfo(self):
		self.nom = self.nomInput.get()
		self.anglais = self.anglaisInput.get()
		self.notes.append(self.anglais)
		self.math = self.mathInput.get()
		self.notes.append(self.math)
		self.physique = self.physiqueInput.get()
		self.notes.append(self.physique)

		print(self.nom)
		print(self.anglais)
		print(self.math)
		print(self.physique)
		print(self.notes)


class AfficherResultats(tk.Tk):
	etudiants = []
	def __init__(self):
		tk.Tk.__init__(self)
		self['bg'] = 'blue'
		self.title("Afficher les résultats")

		self.geometry("320x80")
		self.afficher()

	def afficher(self):
		pass



def main():
	app = Application() 
	app.title("Gestion des Resultat Examens") 
	app.mainloop()


if __name__ == '__main__':
	main()

