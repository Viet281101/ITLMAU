import pathlib
from sklearn.neighbors import NearestNeighbors


docs = []
labels = []

directory = pathlib.Path('bbc')
label_names = ['business', 'politics', 'sports', 'technology', 'entertainment']

import numpy as np

def embed(tokens, nlp):
    #print("in embed")
    """Return the centroid of the embeddings for the given tokens.

    Out-of-vocabulary tokens are cast aside. Stop words are also
    discarded. An array of 0s is returned if none of the tokens
    are valid.

    """
    # ici on récupère les lexemes des tokens https://spacy.io/api/lexeme
    #print([token for token in tokens])
    lexemes = (nlp.vocab[token] for token in tokens)
    #print([lexeme.vector for lexeme in lexemes])
    # ici on récupère pour chaque lexeme le vecteur correspondant
    """ print([lexeme for lexeme in lexemes
        if lexeme.has_vector
        and not lexeme.is_stop
        and len(lexeme.text) > 1]) 
    """
    vectors = np.asarray([
        lexeme.vector
        for lexeme in lexemes
        if lexeme.has_vector
        and not lexeme.is_stop
        and len(lexeme.text) > 1
    ])

    # si on a des vecteurs (il peut arriver que lexemes soit vide si nlp.vocab ne contient pas les tokens du document
    if len(vectors) > 0:
        centroid = vectors.mean(axis=0)
    else:
        # sinon, on dit que les coordonnées du centroïde sont à 0
        width = nlp.meta['vectors']['width']  # typically 300
        centroid = np.zeros(width)

    return centroid



for label in label_names:
    for file in directory.joinpath(label).iterdir():
        labels.append(label)
        # docs contains every document. label information has been lost
        print(file)
        docs.append(file.read_text(encoding='unicode_escape'))

import string

def clean_text(text):
    text = text.lower()
    text = text.translate(str.maketrans('', '', string.punctuation))
    text = text.replace('\n', ' ')
    text = ' '.join(text.split())  # remove multiple whitespaces
    return text

doc = docs[0]
doc = clean_text(doc)
#print(doc)

import spacy

nlp = spacy.load('en_core_web_lg')

tokens = doc.split(' ')
centroid = embed(tokens, nlp)
print(centroid.shape)
print(centroid[:10])


label_vectors = np.asarray([
     embed(label.split(' '), nlp)
     for label in label_names
])

print("label_vectors", label_vectors)



neigh = NearestNeighbors(n_neighbors=1)
neigh.fit(label_vectors)

# closest_label = neigh.kneighbors([centroid], return_distance=False)[0, 0]
# print("### closest label ", closest_label)
# print(label_names[closest_label])


def predict(doc, nlp, neigh):
    doc = clean_text(doc)
    tokens = doc.split(' ')[:50]
    centroid = embed(tokens, nlp)
    #print(centroid.shape)
    closest_label = neigh.kneighbors([centroid], return_distance=False)[0][0]
    return closest_label

preds = [label_names[predict(doc, nlp, neigh)] for doc in docs]
print(labels)
print(preds)

from sklearn import metrics
 
report = metrics.classification_report(
    y_true=labels,
    y_pred=preds,
    labels=label_names
)

print(report)
