
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import classification_report
import glob
import re

#### 1. Préparation des données
texts = {"appr":[], "test":[]}
classes = {"appr":[], "test":[]}

for path in glob.glob("corpus_multi/*/*/*")[:1500]:
	_, lg, corpus, filename = re.split(r'/|\\', path)
	classes[corpus].append(lg)
	with open(path, encoding="utf-8") as f:
		fstring = f.read()
		texts[corpus].append(fstring)



#### 2. Vectorisation des données
vectorizer = CountVectorizer(max_features=1000, analyzer='char', ngram_range=(1,2))
X_train = vectorizer.fit_transform(texts["appr"]).toarray()
X_test = vectorizer.transform(texts["test"]).toarray()
y_train = classes["appr"]
y_test = classes["test"]



#### 3. Classification et évaluation
gnb = GaussianNB()
y_pred = gnb.fit(X_train, y_train).predict(X_test)

#### Comparaison prédiction et attendu
NB_erreurs = (y_test != y_pred).sum()
print(f"Erreurs d'étiquetage sur {len(X_test)} textes: {NB_erreurs}")
print(classification_report(y_test, y_pred))



#### 4. Faire jouer les paramètres
def test_vectorizer(vectorizer):
	X_train = vectorizer.fit_transform(texts["appr"]).toarray()
	X_test = vectorizer.transform(texts["test"]).toarray()
	gnb = GaussianNB()
	y_pred = gnb.fit(X_train, y_train).predict(X_test)
	NB_erreurs = (y_test != y_pred).sum()
	print(f"Erreurs d'étiquetage sur {len(X_test)} textes: {NB_erreurs}")
	print(classification_report(y_test, y_pred))

vectorizer = CountVectorizer(max_features=1000, analyzer='char', ngram_range=(1,2))
test_vectorizer(vectorizer)


