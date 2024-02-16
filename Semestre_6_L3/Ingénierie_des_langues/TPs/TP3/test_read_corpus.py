
import glob

liste_fichiers = glob.glob("corpus_multi/*/*/*")

for chemin in liste_fichiers :
	print(chemin)
	print(chemin.split("/"))
