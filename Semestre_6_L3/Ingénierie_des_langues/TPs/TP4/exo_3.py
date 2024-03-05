
import random
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


def count_transitions(corpus, ordre) -> dict:
	'''
	paramètre : corpus (séquence de séquence de tokens)
	returns : dictionnaire à deux niveaux contenant pour chaque mot le nombre d'apparitions pour chaque mot suivant possible.
	'''
	transitions = {}

	for sentence in corpus:
		for i in range(len(sentence)-ordre):
			if tuple(sentence[i:i+ordre]) not in transitions:
				transitions[tuple(sentence[i:i+ordre])] = {}
			if sentence[i+ordre] not in transitions[tuple(sentence[i:i+ordre])]:
				transitions[tuple(sentence[i:i+ordre])][sentence[i+ordre]] = 0
			transitions[tuple(sentence[i:i+ordre])][sentence[i+ordre]] += 1

	return transitions


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


def markov_chain(corpus, ordre) -> dict:
	transitions = count_transitions(corpus, ordre)
	return probabilify(transitions)



corpus = []
corpus.extend(doc_to_word_list("proust/2998-0.txt"))
markov_chain_ = markov_chain(corpus, 3)
# print(markov_chain_)


ponctuation = [".", "!", "?", "…", ":", ";", ",", "(", ")", "[", "]", "{", "}", "«", "»", "“", "”", "‘", "’", "—", "–", "-", " ", "\n", "\t", "\r "]
NB_MOTS_MAXI = 100


def generate(markov_chain, ordre, start_tokens):
	if isinstance(start_tokens, str):
		start_tokens = tuple(start_tokens.split())
	phrase = list(start_tokens)
	for _ in range(NB_MOTS_MAXI - len(start_tokens)):
		current_tuple = tuple(phrase[-(ordre-1):])
		if current_tuple in markov_chain:
			next_words = markov_chain[current_tuple]
			next_word = max(next_words, key=next_words.get)
			phrase.append(next_word)
			if next_word in ponctuation:
				break
		else:
			break
	return ' '.join(phrase)



generate(markov_chain, 3, "Si")



def generate_alea(markov_chain, ordre, start_token, n_best=1):
	phrase = [start_token]
	for _ in range(NB_MOTS_MAXI):
		current_tuple = tuple(phrase[-ordre:])
		if current_tuple in markov_chain:
			next_words = list(markov_chain[current_tuple].items())
			next_words.sort(key=lambda x: x[1], reverse=True)
			top_next_words = next_words[:n_best] if len(next_words) > n_best else next_words
			next_word, _ = random.choice(top_next_words)
			phrase.append(next_word)
			if next_word in ponctuation:
				break
		else:
			break
	return ' '.join(phrase)



generate_alea(markov_chain, 3, "Si", 2)
