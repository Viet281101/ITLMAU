
class Salles:
	def __init__(self, id, nom:str):
		self.id = id
		self.nom = nom
		self.disponible

	@staticmethod
	def disponibilite_salle(jour:str, creneaux:int):
		switch1 = {
			'Lundi': True,
			'Mardi': True,
			'Mercredi' : True,
			'Jeudi' : True,
			'Vendredi' : True,
			'Samedi' : False,
			'Dimache' : False,
		}
		return switch1.get(jour, "Veuillez entrez un jour que vous voulez reserver: ")

		switch2 = {
			
		}
		
