

import nltk

from nltk.tag import StanfordPOSTagger
from textblob import TextBlob

# Le chemin est à spécifier selon la localisation du
# module punkt
tokenizer = nltk.data.load('nltk_data/tokenizers/punkt/french.pickle')
words_generator = tokenizer._tokenize_words(
	"Depuis huit jours, j'avais déchiré mes bottines Aux cailloux des chemins. \
		J'entrais à Charleroi. - Au Cabaret-Vert : je demandai des tartines De beurre et du jambon qui fût à moitié froid."
)
words = [word for word in words_generator]

print(words)

