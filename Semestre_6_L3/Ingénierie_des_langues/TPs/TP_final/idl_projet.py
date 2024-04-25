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

from sklearn.feature_extraction.text import TfidfVectorizer, CountVectorizer

def vectorize_text(data, vectorizer):
	"""Vectorize text data using specified vectorizer."""
	vectorized_data = vectorizer.fit_transform(data)
	return vectorized_data, vectorizer

### TF-IDF Vectorizer
tfidf_vectorizer = TfidfVectorizer(stop_words='english', max_features=5000)

### Count Vectorizer
count_vectorizer = CountVectorizer(stop_words='english', max_features=5000)

### TF-IDF
features, current_vectorizer = vectorize_text(reviews_df['review'], tfidf_vectorizer)
print("Forme de la matrice TF-IDF :", features.shape)

### Count
features_count, current_vectorizer = vectorize_text(reviews_df['review'], count_vectorizer)
print("Forme de la matrice Count :", features.shape)



## Entrainement du modèle

### 1. Logistic Regression

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

### TF-IDF
train_and_evaluate(features, reviews_df['label'])


### Count
train_and_evaluate(features_count, reviews_df['label'])


### 2. SVM & GridSearchCV

from sklearn.svm import SVC
from sklearn.model_selection import GridSearchCV

def train_and_evaluate_svm(X_train, y_train, X_test, y_test):
	param_grid = {
		'C': [0.1, 1, 10, 100],
		'kernel': ['linear', 'rbf'],
		'gamma': ['scale', 'auto']
	}
	grid_search = GridSearchCV(SVC(), param_grid, cv=5, scoring='accuracy', verbose=1)
	grid_search.fit(X_train, y_train)
	print("Best parameters:", grid_search.best_params_)
	best_model = grid_search.best_estimator_
	y_pred = best_model.predict(X_test)
	print("Accuracy:", accuracy_score(y_test, y_pred))
	print("Classification Report:\n", classification_report(y_test, y_pred))

### TF-IDF
train_and_evaluate_svm(features, reviews_df['label'], features, reviews_df['label'])

### Count
train_and_evaluate_svm(features_count, reviews_df['label'], features_count, reviews_df['label'])



### 3. Random Forest

from sklearn.ensemble import RandomForestClassifier

def train_and_evaluate_rf(features, labels):
	X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.25, random_state=42)
	model = RandomForestClassifier(n_estimators=100, random_state=42)
	model.fit(X_train, y_train)
	y_pred = model.predict(X_test)
	print("Accuracy:", accuracy_score(y_test, y_pred))
	print("Classification Report:\n", classification_report(y_test, y_pred))

### TF-IDF
train_and_evaluate_rf(features, reviews_df['label'])

### Count
train_and_evaluate_rf(features_count, reviews_df['label'])



### 4. Naive Bayes

from sklearn.naive_bayes import MultinomialNB

def train_and_evaluate_nb(features, labels):
	X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.25, random_state=42)
	model = MultinomialNB()
	model.fit(X_train, y_train)
	y_pred = model.predict(X_test)
	print("Accuracy:", accuracy_score(y_test, y_pred))
	print("Classification Report:\n", classification_report(y_test, y_pred))

### TF-IDF
train_and_evaluate_nb(features, reviews_df['label'])

### Count
train_and_evaluate_nb(features_count, reviews_df['label'])



### 5. Decision Tree

from sklearn.tree import DecisionTreeClassifier

def train_and_evaluate_dt(features, labels):
	X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.25, random_state=42)
	model = DecisionTreeClassifier(random_state=42)
	model.fit(X_train, y_train)
	y_pred = model.predict(X_test)
	print("Accuracy:", accuracy_score(y_test, y_pred))
	print("Classification Report:\n", classification_report(y_test, y_pred))

### TF-IDF
train_and_evaluate_dt(features, reviews_df['label'])

### Count
train_and_evaluate_dt(features_count, reviews_df['label'])



