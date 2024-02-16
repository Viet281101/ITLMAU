
import glob
import json

def dic_to_json(dic, json_file):
	with open(json_file, "w", encoding="utf−8") as w:
		w.write(json.dumps(dic, indent = 2, ensure_ascii=False))

def load_model(json_file):
	with open(json_file, "r", encoding="utf−8") as f:
		model = json.load(f)
		return(model)
			   

files_list = glob.glob("corpus_multi/*/*/*")
print("Nombre de fichiers : %i"%len(liste_fichiers))

def show_files(files_list) :
	for chemin in files_list :
		print(chemin)
		print(chemin.split("/"))
		break # stoppe la boucle, à décommenter si vous voulez
	
def read_file(chemin):
	# TO_FILL
	pass

def language_dic(files_list):
	# TO FILL
	pass

def create_lmodels_wc(dic):
	# TO FILL
	pass


''' Exercice 3
def evaluate(pred_results):
	correct = 0
	for language, predicted_language in pred_results:
		results_dic.setdefault(langue, {"VP": int(), "FP": int(), "FN": int()})
		results_dic.setdefault(langue_pred, {"VP": int(), "FP": int(), "FN": int()})
		if langue == langue_pred:
			results_dic[language]["VP"] += 1  # langue bien détectée
			NB_bonnes_reponses += 1

		# TO FILL
		
	return dic_resultats, NB_bonnes_reponses
'''


if __name__ == "__main__":
	show_files(files_list)
