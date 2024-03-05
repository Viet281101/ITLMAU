
import re

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


corpus = []
corpus.extend(doc_to_word_list("proust/2998-0.txt"))
# print(corpus[:20])
corpus.extend(doc_to_word_list("proust/3000-0.txt"))
print(corpus[:20])

