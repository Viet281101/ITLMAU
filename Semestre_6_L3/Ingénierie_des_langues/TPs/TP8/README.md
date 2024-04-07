
# IDL 16 Système de recommandation de films

Rapport de TP réalisé par __Viet Nguyen -- 20006303__.
Les codes et résultats sont tout dans le fichier `tp8.ipynb` sur Jupyter Notebook. Voici juste un résumé de ce que j'ai fait dans les étapes:

## I. Préparation du dataset

### Étape 1: Lecture du jeu de données

- Lecture des données à partir d'un fichier JSON et transformation en un dictionnaire Python où les clés sont les titres des films et les valeurs sont les résumés.

```python
import json

def json_to_dict(filename):
	with open(filename, 'r', encoding='utf-8') as file:
		data = json.load(file)
		movie_dict = { item['Title']: item['Plot'] for item in data }
	return movie_dict

movie_dict = json_to_dict('films.json')
```

### Étape 2: Chaîne de traitement en TAL

- Application de techniques de TAL (Traitement Automatique du Langage) pour le prétraitement des résumés des films, incluant la tokenisation, la suppression des stop-words, et la lemmatisation.

```python
import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer

def nlp(sentence):
	tokens = word_tokenize(sentence)
	tokens = [word for word in tokens if word.isalpha() and word not in stopwords.words('english')]
	lemmatizer = WordNetLemmatizer()
	tokens = [lemmatizer.lemmatize(word) for word in tokens]
	return tokens
```

### Étape 3: Application de la chaîne de traitement au dictionnaire

- Application de la fonction `nlp` sur chaque résumé de film pour obtenir des tokens nettoyés et lemmatisés.

```python
def nlp_dico(movie_dict):
	processed_dict = {}
	for title, plot in movie_dict.items():
		processed_dict[title] = nlp(plot)
	return processed_dict

processed_movies = nlp_dico(movie_dict)
```

## II. Calcul de la similarité de Jaccard

- Définition et utilisation d'une fonction pour calculer la similarité de Jaccard entre les ensembles de tokens de deux résumés de films.

```python
def jaccard_similarity(list1, list2):
	set1, set2 = set(list1), set(list2)
	intersection = len(set1.intersection(set2))
	union = len(set1.union(set2))
	return intersection / union if union != 0 else 0
```


## III. Calcul de la représentation vectorielle

### Étape 1 : Calcul de TF et d'IDF

- Calcul de la fréquence des termes (TF) et de la fréquence inverse des documents (IDF) pour chaque terme dans le corpus.

```python
def compute_TF(document):
	tf_dict = {}
	len_doc = len(document)
	for word in document:
		tf_dict[word] = tf_dict.get(word, 0) + 1/len_doc
	return tf_dict

def compute_IDF(documents):
	N = len(documents)
	idf_dict = {}
	for document in documents:
		for word in set(document):
			idf_dict[word] = idf_dict.get(word, 0) + 1
	for word, val in idf_dict.items():
		idf_dict[word] = log10(N / float(val))
	return idf_dict
```

## Étape 2 : Calcul des vecteurs TF-IDF

- Génération de vecteurs TF-IDF pour chaque résumé de film en multipliant TF par IDF pour chaque terme.

```python
def compute_TFIDF(tf_dict, idf_dict):
	tfidf_dict = {}
	for word, tf in tf_dict.items():
		tfidf_dict[word] = tf * idf_dict.get(word, 0)
	return tfidf_dict
```

## IV. Recommandation

- Utilisation des vecteurs TF-IDF et de la similarité cosine pour recommander des films similaires à un film donné.

```python
import numpy as np

def cosine_similarity(list1, list2):
	dot = np.dot(list1, list2)
	norm1 = np.linalg.norm(list1)
	norm2 = np.linalg.norm(list2)
	return dot / (norm1 * norm2)

def recommend_movies(base_title, tfidf_vectors, n_recommendations=3):
	base_vector = tfidf_vectors[base_title]
	similarities = {title: cosine_similarity(base_vector, vector)
					for title, vector in tfidf_vectors.items() if title != base_title}
	recommended_titles = sorted(similarities, key=similarities.get, reverse=True)[:n_recommendations]
	return [(title, similarities[title]) for title in recommended_titles]
```

- Affichage des recommandations basées sur "The Shawshank Redemption".

```python
recommendations = recommend_movies('The Shawshank Redemption', tfidf_vectors, 3)
for title, score in recommendations:
	print(f"{title}: {score}")
```



