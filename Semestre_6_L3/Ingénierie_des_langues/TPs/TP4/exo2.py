
import numpy as np

def doc_to_word_list(path):
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


def count_unigram_transitions(corpus):
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

def probabilify(comptes_transitions):
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


def compter_transitions_bigrammes(corpus):
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
compter_transitions_bigrammes(corpus)


def chaine_markov_bigramme(corpus):
	transitions = compter_transitions_bigrammes(corpus)
	return probabilify(transitions)

markov_chain = chaine_markov_bigramme(corpus)
# print(markov_chain["le"])

ponctuation = [".", "!", "?", "…", ":", ";", ",", "(", ")", "[", "]", "{", "}", "«", "»", "“", "”", "‘", "’", "—", "–", "-", " ", "\n", "\t", "\r "]
NB_MOTS_MAXI = 100


def generate_bi(markov_chain, start_token):
	phrase = []
	maximum = NB_MOTS_MAXI
	token = start_token
	while len(phrase) < maximum:
		if token in markov_chain:
			next_tokens = markov_chain[token]
			token = max(next_tokens, key=next_tokens.get)
			phrase.append(token)
			if token in ponctuation:
				break
		else:
			break
	return ' '.join(phrase)


print(generate_bi(markov_chain, "Si"))


import random

def generate_bi(markov_chain, start_token, n_best=1):
	phrase = []
	maximum = NB_MOTS_MAXI
	token = start_token
	while len(phrase) < maximum:
		if token in markov_chain:
			next_tokens = list(markov_chain[token].items())
			next_tokens.sort(key=lambda x: x[1], reverse=True)
			top_tokens = next_tokens[:n_best] if len(next_tokens) > n_best else next_tokens
			token, _ = random.choice(top_tokens)
			phrase.append(token)
			if token in ponctuation:
				break
		else:
			break
	return ' '.join(phrase)



# print(generate_bi(markov_chain, "Si", 2))
# print(generate_bi(markov_chain, "Si", 10))
