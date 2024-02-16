
import glob
import json

def dic_to_json(dic, json_file):
	"""Writes a dictionary to a json file."""
	with open(json_file, "w", encoding="utf−8") as w:
		w.write(json.dumps(dic, indent = 2, ensure_ascii=False))

def load_model(json_file):
	"""Loads a json file and returns its content."""
	with open(json_file, "r", encoding="utf−8") as f:
		model = json.load(f)
		return(model)
			   

files_list = glob.glob("corpus_multi/*/*/*")
print("Nombre de fichiers : %i"%len(files_list))


#####//////  Exercice 1: créer un modèle de langue ///////#####

train_files_list = [f for f in files_list if "/appr/" in f]
test_files_list = [f for f in files_list if "/test/" in f]

print("Nombre de fichiers d'entraînement : %i"%len(train_files_list))
print("Nombre de fichiers de test : %i"%len(test_files_list))


def show_files(files_list) :
	"""Prints the list of files."""
	for chemin in files_list :
		print(chemin)
		print(chemin.split("/"))
		break
	

def read_file(chemin):
	"""Reads a file and returns its content."""
	with open(chemin, "r", encoding="utf-8") as file:
		content = file.read()
	return content


def language_dic(files_list):
	"""Creates a dictionary of languages and their words."""
	language_word_count = {}
	for chemin in files_list:
		parts = chemin.split('/')
		language = parts[-3]

		content = read_file(chemin)

		words = content.split()
		for word in words:
			if language not in language_word_count:
				language_word_count[language] = {}
			if word not in language_word_count[language]:
				language_word_count[language][word] = 1
			else:
				language_word_count[language][word] += 1

	return language_word_count


def create_lmodels_wc(dic):
	lmodels_wc = {}
	for language, words_count in dic.items():
		most_common_words = sorted(words_count.items(), key=lambda item: item[1], reverse=True)[:10]

		lmodels_wc[language] = [word for word, count in most_common_words]
	return lmodels_wc



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

	#####//////  Exercice 1: créer un modèle de langue ///////#####
	language_word_count = language_dic(train_files_list)

	lmodels_wc = create_lmodels_wc(language_word_count)

	dic_to_json(lmodels_wc, "language_models.json")
	print("lmodels_wc.json créé")

