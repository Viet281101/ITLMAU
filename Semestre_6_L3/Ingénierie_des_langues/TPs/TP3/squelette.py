
import glob
import json

def dic_to_json(dic, json_file) -> None:
	"""Writes a dictionary to a json file."""
	with open(json_file, "w", encoding="utf−8") as w:
		w.write(json.dumps(dic, indent = 2, ensure_ascii=False))

def load_model(json_file) -> dict[str, list[str]]:
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


def show_files(files_list) -> None:
	"""Prints the list of files."""
	for chemin in files_list :
		print(chemin)
		print(chemin.split("/"))
		break


def read_file(chemin) -> str:
	"""Reads a file and returns its content."""
	with open(chemin, "r", encoding="utf-8") as file:
		content = file.read()
	return content


def language_dic(files_list) -> dict[str, dict[str, int]]:
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


def create_lmodels_wc(dic) -> dict[str, list[str]]:
	lmodels_wc = {}
	for language, words_count in dic.items():
		most_common_words = sorted(words_count.items(), key=lambda item: item[1], reverse=True)[:10]

		lmodels_wc[language] = [word for word, count in most_common_words]
	return lmodels_wc


def exercice1() -> None:
	language_word_count = language_dic(train_files_list)

	lmodels_wc = create_lmodels_wc(language_word_count)

	dic_to_json(lmodels_wc, "language_models.json")
	print("lmodels_wc.json créé")



#####//////  Exercice 2: utiliser le modèle de langue ///////#####

def get_most_frequent_words(text, n=10) -> list[str]:
	words = text.split()
	word_counts = {}
	for word in words:
		if word in word_counts:
			word_counts[word] += 1
		else:
			word_counts[word] = 1
	most_frequent_words = sorted(word_counts.items(), key=lambda item: item[1], reverse=True)[:n]
	return [word for word, count in most_frequent_words]



def lpredict(test_file, lmodels_wc) -> str:

	test_content = read_file(test_file)

	most_frequent_test = get_most_frequent_words(test_content)

	lprediction = []
	for lg, model in lmodels_wc.items():
		common_words = set(model).intersection(most_frequent_test)
		common_wc = len(common_words)
		lprediction.append([common_wc, lg])

	predicted_language = sorted(lprediction, key=lambda x: x[0], reverse=True)[0][1]
	return predicted_language



def exercice2() -> None:
	lmodels_wc = load_model("language_models.json")

	test_file = test_files_list[0]
	predicted_language = lpredict(test_file, lmodels_wc)
	print(f"File: {test_file}, Predicted Language: {predicted_language}")

	with open("test_results.txt", "w", encoding="utf-8") as results_file:
		correct_predictions = 0

		for test_file in test_files_list:
			actual_language = test_file.split('/')[-3]

			predicted_language = lpredict(test_file, lmodels_wc)

			if actual_language == predicted_language:
				correct_predictions += 1

			results_file.write(f"File: {test_file}, Actual Language: {actual_language}, Predicted Language: {predicted_language}\n")

		total_tests = len(test_files_list)
		accuracy = (correct_predictions / total_tests) * 100
		results_file.write(f"Accuracy: {accuracy:.2f}%\n")




#####//////  Exercice 3: évaluation ///////#####

def evaluate_wc_model(pred_results) -> tuple[dict[str, dict[str, int]], int]:
	results_dic = {}
	correct = 0

	for actual_language, predicted_language in pred_results:
		if actual_language not in results_dic:
			results_dic[actual_language] = {"TP": 0, "FP": 0, "FN": 0}
		for language in results_dic:
			if language == predicted_language:
				if language == actual_language:
					results_dic[language]["TP"] += 1
					correct += 1
				else:
					results_dic[language]["FP"] += 1
			elif language == actual_language:
				results_dic[language]["FN"] += 1

	return results_dic, correct


def exercice3() -> None:
	lmodels_wc = load_model("language_models.json")
	# pred_results = []
	# for test_file in test_files_list:
	# 	actual_language = test_file.split('/')[-3]
	# 	predicted_language = lpredict(test_file, lmodels_wc)
	# 	pred_results.append((actual_language, predicted_language))

	# results_dic, correct = evaluate_wc_model(pred_results)
	# print(results_dic)
	# print(correct)

	pred_results = [(test_file.split('/')[-3], lpredict(test_file, lmodels_wc)) for test_file in test_files_list]

	results_dic, correct_predictions = evaluate_wc_model(pred_results)

	total_tests = len(pred_results)
	overall_accuracy = (correct_predictions / total_tests) * 100
	print(f"Précision Globale: {overall_accuracy:.2f}%")
	print("Résultats par Langue:", results_dic)




#####//////  Exercice 4: en caractères ///////#####

def generate_ngrams(text, n=2):
	ngrams = [text[i:i+n] for i in range(len(text)-n+1)]
	return ngrams


def language_dic_ngrams(files_list, n=2):
	language_ngram_count = {}
	for chemin in files_list:
		parts = chemin.split('/')
		language = parts[-3]
		content = read_file(chemin)
		ngrams = generate_ngrams(content, n)

		for ngram in ngrams:
			if language not in language_ngram_count:
				language_ngram_count[language] = {}
			if ngram not in language_ngram_count[language]:
				language_ngram_count[language][ngram] = 1
			else:
				language_ngram_count[language][ngram] += 1

	return language_ngram_count


def get_most_frequent_ngrams(ngrams, n=10) -> list[str]:
	ngram_counts = {}
	for ngram in ngrams:
		if ngram in ngram_counts:
			ngram_counts[ngram] += 1
		else:
			ngram_counts[ngram] = 1
	most_frequent_ngrams = sorted(ngram_counts.items(), key=lambda item: item[1], reverse=True)[:n]
	return [ngram for ngram, count in most_frequent_ngrams]


def lpredict_ngrams(test_file, model_file, n=2) -> str:
	lmodels_wc_ngrams = load_model(model_file)
	test_content = read_file(test_file)
	test_ngrams = generate_ngrams(test_content, n)
	most_frequent_test_ngrams = get_most_frequent_ngrams(test_ngrams, n=10)

	lprediction = []
	for lg, model in lmodels_wc_ngrams.items():
		common_ngrams = set(model).intersection(most_frequent_test_ngrams)
		common_wc = len(common_ngrams)
		lprediction.append([common_wc, lg])

	predicted_language = sorted(lprediction, key=lambda x: x[0], reverse=True)[0][1]
	return predicted_language


def test_and_evaluate(n):
	model_file = f"language_models_n{n}.json"
	pred_results = [(test_file.split('/')[-3], lpredict_ngrams(test_file, model_file, n)) for test_file in test_files_list]
	results_dic, correct_predictions = evaluate_wc_model(pred_results)
	total_tests = len(pred_results)
	overall_accuracy = (correct_predictions / total_tests) * 100
	print(f"For n={n}, Overall Accuracy: {overall_accuracy:.2f}%")
	print("Results by Language:", results_dic)


def exercice4() -> None:
	for n in range(1, 5):
		language_ngram_count = language_dic_ngrams(train_files_list, n)
		lmodels_ngram = create_lmodels_wc(language_ngram_count)
		dic_to_json(lmodels_ngram, f"language_models_n{n}.json")
		print(f"language_models_n{n}.json creée")
		test_and_evaluate(n)

	# lmodels_wc_ngrams = language_dic_ngrams(train_files_list, n=2)
	# dic_to_json(lmodels_wc_ngrams, "language_models_ngrams.json")
	# print("lmodels_wc_ngrams.json créé")

	# pred_results_ngrams = [(test_file.split('/')[-3], lpredict_ngrams(test_file, "language_models_ngrams.json", n=2)) for test_file in test_files_list]

	# results_dic_ngrams, correct_predictions_ngrams = evaluate_wc_model(pred_results_ngrams)

	# total_tests = len(pred_results_ngrams)
	# overall_accuracy = (correct_predictions_ngrams / total_tests) * 100
	# print(f"Précision Globale: {overall_accuracy:.2f}%")
	# print("Résultats par Langue:", results_dic_ngrams)



if __name__ == "__main__":
	# show_files(files_list)

	# exercice1()
	# exercice2()
	# exercice3()
	exercice4()


