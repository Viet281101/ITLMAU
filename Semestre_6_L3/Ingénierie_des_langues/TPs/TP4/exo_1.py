
import numpy as np

def doc_to_word_list(path) -> list:
	'''
	paramètre : chemin vers un corpus
	returns : liste de liste 
		- liste de phrases
		- chaque phrase est une liste de tokens
	'''
	with open(path) as input_stream:
		lines = input_stream.readlines()
		lines = [line.strip() for line in lines]
		lines = [line.split() for line in lines]
	return lines


def count_unigram_transitions(corpus) -> dict:
	'''
	paramètre : corpus (séquence de séquence de tokens)
	returns : dictionnaire à deux niveaux contenant pour chaque mot le nombre d'apparitions pour chaque mot suivant possible.
	'''
	transitions = {}
	
	for sentence in corpus:
		for i in range(len(sentence)-1):
			if sentence[i] not in transitions:
				transitions[sentence[i]] = {}
			if sentence[i+1] not in transitions[sentence[i]]:
				transitions[sentence[i]][sentence[i+1]] = 0
			transitions[sentence[i]][sentence[i+1]] += 1

	return transitions

corpus = []
corpus.extend(doc_to_word_list("proust/2998-0.txt"))
# print(count_unigram_transitions(corpus))


def probabilify(comptes_transitions) -> dict:
	'''
	paramètre : dictionnaire de transitions
	returns : dictionnaire à deux niveaux contenant pour chaque mot la probabilité d'apparition pour chaque mot suivant possible. 
	'''
	probabilites = {}
	for word in comptes_transitions:
		probabilites[word] = {}
		total = sum(comptes_transitions[word].values())
		for next_word in comptes_transitions[word]:
			probabilites[word][next_word] = comptes_transitions[word][next_word] / total
	return probabilites


# print(probabilify(count_unigram_transitions(corpus)) )

def markov_chain_unigram(corpus) -> dict:
	transitions = count_unigram_transitions(corpus)
	return probabilify(transitions)

markov_chain = markov_chain_unigram(corpus)
# print(markov_chain["le"])


ponctuation = [".", "!", "?", "…", ":", ";", ",", "(", ")", "[", "]", "{", "}", "«", "»", "“", "”", "‘", "’", "—", "–", "-", " ", "\n", "\t", "\r "]
NB_MOTS_MAXI = 100

def generate_unigram(markov_chain, start_token) -> list:
	'''
	paramètre : chaîne de Markov, token de départ
	returns : liste de tokens
	'''
	phrase = [start_token]
	for i in range(NB_MOTS_MAXI):
		if phrase[-1] not in markov_chain:
			break
		proba = markov_chain[phrase[-1]]
		next_word = np.random.choice(list(proba.keys()), p=list(proba.values()))
		if next_word in ponctuation:
			phrase.append(next_word)
			break
		phrase.append(next_word)
	return phrase


# print(generate_unigram(markov_chain, "Si"))

def generer_unigramme_alea(markov_chain, start_token, n_best=1) -> None:
	'''
	Paramètres : 
	- chaîne de Markov
	- token de départ
	- nombre de tokens dans lesquels choisir le token suivant
	
	Returns : void.
	Affiche la phrase générée.
	'''
	for i in range(n_best):
		phrase = generate_unigram(markov_chain, start_token)
		print(" ".join(phrase))
		print("\n")

generer_unigramme_alea(markov_chain, "Si", 2)
generer_unigramme_alea(markov_chain, "Si", 10)

