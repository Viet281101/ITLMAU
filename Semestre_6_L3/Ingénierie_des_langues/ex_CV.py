
from sklearn.feature_extraction.text import CountVectorizer

corpus = [
    'This is the first document',
    'This is the second document',
    'And this is the third one'
]

vectorizer = CountVectorizer()
X = vectorizer.fit_transform(corpus)
print("--------------------------------")
print("Représentation \"en mots\" : \n")
print(X.toarray())
print("--------------------------------")
