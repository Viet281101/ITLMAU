
import re
import string
import gensim.models

def preprocess(s):
	s_without_punct = s
	for char in string.punctuation:
		s_without_punct = s_without_punct.replace(char, ' ') # on replace les ponctuations par des espaces
	tokens = s_without_punct.split()
	return [token.lower() for token in tokens]


def get_corpus(corpus_path):
	# assume there's one sentence per line, tokens separated by whitespace
	# simple_preprocess: "Convert a document into a list of lowercase tokens, 
	# ignoring tokens that are too short or too long.""
	with open(corpus_path, mode='r', encoding='utf-8') as inFile:
		return [preprocess(line) for line in inFile.readlines()]


class Embeddings(object):
	"""Programs to learn, save and load embeddings."""
	def __init__(self, corpus_path, model_path):
		self._corpus_path = corpus_path
		self._model_path = model_path

	def learn(self):
		sentences = get_corpus(self._corpus_path) # List of sentences (a sentence = list of words)
		self._model = gensim.models.Word2Vec(sentences=sentences)
		self._model.save(self._model_path)

	def learn_restrictive(self, min_freq):
		sentences = get_corpus(self._corpus_path) # List of sentences (a sentence = list of words)
		self._model = gensim.models.Word2Vec(sentences=sentences, window=20, min_count=min_freq, workers=4)
		self._model.save(self._model_path)

	def load(self):
		self._model = gensim.models.Word2Vec.load(self._model_path)

	def most_similar(self, word, topN=10):
		return self._model.wv.most_similar(positive=[word], topn=topN)

	def most_similar_analogy(self, pos, neg, topN=10):
		return self._model.wv.most_similar(positive=pos, negative=neg, topn=topN)

	def similarity(self, w1, w2):
		if w1 in self._model.wv and w2 in self._model.wv:
			return self._model.wv.similarity(w1, w2)
		else:
			return -1

	def get_vocab(self):
		return self._model.wv

	def get_vector(self, word):
		return self._model.wv.get_vector(word)

	def get_model(self):
		return self._model


gauche_corpus_path = './data_embeddings/GAUCHE.txt'
droite_corpus_path = './data_embeddings/DROITE.txt'

gauche_model_path = './model/GAUCHE.W2Vmodel'
droite_model_path = './model/DROITE.W2Vmodel'

embeddings_gauche = Embeddings(gauche_corpus_path, gauche_model_path)
embeddings_droite = Embeddings(droite_corpus_path, droite_model_path)
embeddings_gauche.load()
embeddings_droite.load()

embeddings = {"GAUCHE": embeddings_gauche, "DROITE": embeddings_droite}


####### 1. Étude des vecteurs proches et éloignés ########

import numpy as np

def cosine_similarity(vec1, vec2): 
	dot = np.dot(vec1, vec2)
	norm1 = np.linalg.norm(vec1)
	norm2 = np.linalg.norm(vec2)
	cos = dot / (norm1 * norm2)
	return cos


NB_TO_SHOW = 30
emb1, emb2 = embeddings['DROITE'].get_model(), embeddings['GAUCHE'].get_model()
vocab1, vocab2 = set(emb1.wv.key_to_index.keys()), set(emb2.wv.key_to_index.keys())
sims = {}

for word in vocab1.intersection(vocab2): 
	vec1 = emb1.wv.get_vector(word)
	vec2 = emb2.wv.get_vector(word)
	sims[word] = cosine_similarity(vec1, vec2)

sims_sorted = sorted(sims.items(), key=lambda item: item[1], reverse=True)


print("*** Vecteurs proches :")
for w, s in sims_sorted[:NB_TO_SHOW]:
	print(f"{w}: {s}")

print("\n*** Vecteurs éloignés :")
for w, s in sims_sorted[-NB_TO_SHOW:]:
	print(f"{w}: {s}")



########## 2. Observation de vecteurs similaires ##############

words_to_explore = ["gauche", "droite", "homme", "action"]

for word in words_to_explore:
	print(f"\nAnalysing word: {word}")
	for corpus_name, emb in embeddings.items():
		print(f"\nTop 10 similar words in {corpus_name}:")
		try:
			similar_words = emb.most_similar(word, topN=10)
			sims = ' '.join([w for w, s in similar_words])
			print(f"{word}\t({corpus_name})\t{sims}")
		except KeyError:
			print(f"The word '{word}' is not in the vocabulary of the {corpus_name} corpus.")


############ 3. Analogies ###############
analogies = [
	(["président", "femme"], ["homme"]),
	(["candidat", "femme"], ["homme"]),
	(["député", "candidats"], ["candidat"])
]

for pos, neg in analogies:
	print(f"\nAnalysing analogy: {' + '.join(pos)} - {' + '.join(neg)}")
	for corpus_name, emb in embeddings.items():
		print(f"\n{corpus_name}:")
		try:
			analogy_result = emb.most_similar_analogy(pos, neg, topN=5)
			for word, similarity in analogy_result:
				print(f"{word}\t{similarity}")
		except KeyError as e:
			print(f"An error occurred: {e}")



############## 4. La method tsne ##############

from sklearn.manifold import TSNE
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

model = embeddings['GAUCHE'].get_model()

vectors = [model.wv[word] for word in model.wv.index_to_key]
labels = [word for word in model.wv.index_to_key]

vectors_np = np.array(vectors)

pca_model = PCA(n_components=50)
vectors_pca = pca_model.fit_transform(vectors_np)

tsne_model = TSNE(n_components=2, random_state=0)
vectors_2d = tsne_model.fit_transform(vectors_pca)

plt.figure(figsize=(10, 10))
for i, label in enumerate(labels[:200]):
	x, y = vectors_2d[i]
	plt.scatter(x, y)
	plt.annotate(label, xy=(x, y), xytext=(5, 2), textcoords='offset points', ha='right', va='bottom')
plt.show()

