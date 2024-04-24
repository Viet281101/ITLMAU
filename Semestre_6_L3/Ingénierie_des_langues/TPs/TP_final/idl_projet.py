# IDL TP Final `scikit-learn`


import os
import pandas as pd


## Chargement des données

def load_reviews(data_dir):
	reviews = []
	labels = []
	for label in ["pos", "neg"]:
		directory = os.path.join(data_dir, label)
		for filename in os.listdir(directory):
			if filename.endswith(".txt"):
				file_path = os.path.join(directory, filename)
				with open(file_path, 'r', encoding='utf-8') as file:
					reviews.append(file.read())
					labels.append(1 if label == "pos" else 0)
	return reviews, labels

data_dir = 'imdb_smol'
reviews, labels = load_reviews(data_dir)
reviews_df = pd.DataFrame({'review': reviews, 'label': labels})


print(reviews_df.head())
print("\nNombre de notes positives:", (reviews_df['label'] == 1).sum())
print("Nombre de notes négatives:", (reviews_df['label'] == 0).sum())
print("\nInformations générales sur le DataFrame:")
print(reviews_df.info())
for index, row in reviews_df.sample(5).iterrows():
	print("\nIndex de la note de review:", index, "\nTexte de la note de review:\n", row['review'])
	print("Étiquette:", "Positive" if row['label'] == 1 else "Négative")
	print("\nIndex de la note de review:", index, "\nTexte de la note de review:\n", row['review'])
	print("Étiquette:", "Positive" if row['label'] == 1 else "Négative")



## Vectorisation des données

from sklearn.feature_extraction.text import TfidfVectorizer

def vectorize_text(data):
	"""Vectorize text data using TF-IDF vectorizer."""
	tfidf_vectorizer = TfidfVectorizer(stop_words='english', max_features=5000)
	features = tfidf_vectorizer.fit_transform(data)
	return features, tfidf_vectorizer

features, tfidf_vectorizer = vectorize_text(reviews_df['review'])
print("Forme de la matrice TF-IDF :", features.shape)



## Entrainement du modèle

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, accuracy_score

def train_and_evaluate(features, labels):
	"""Train and evaluate a logistic regression model."""
	X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.25, random_state=42)
	model = LogisticRegression(random_state=42)
	model.fit(X_train, y_train)
	y_pred = model.predict(X_test)
	print("Accuracy:", accuracy_score(y_test, y_pred))
	print("Classification Report:\n", classification_report(y_test, y_pred))

train_and_evaluate(features, reviews_df['label'])


