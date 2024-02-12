
# TP 2 : nombre moyen de mots par phrase et profilage morphosyntaxique

Rapport de TP réalisé par Viet Nguyen -- 20006303.

__________________________________________________

## 1. Découpage en phrases : test de différentes méthodes

Dans cette première partie, j'ai exploré différentes méthodes pour découper le texte en phrases, visant à préparer le texte pour les analyses morphosyntaxiques ultérieures.

### 1.1 Méthode basée sur des expressions régulières (Regex)

Cette méthode utilise des expressions régulières pour détecter les fins de phrases, marquées par des points, des points d'interrogation ou des points d'exclamation. Le script `convert_txt_xml.py` lit le contenu de `conte.txt`, découpe le texte en phrases, et génère un fichier XML `output.xml` où chaque phrase est identifiée par une balise `<sentence>` unique.

- [x] module re
- [X] utilisation de regex
- [X] input/output de fichiers

### 1.2 Utilisation de librairies dédiées (python)

1. Sentencizer
2. Senter Rappel pipeline spacy


__________________________________________________

## 2. Découpage en mots : test de différentes méthodes

Dans cette deuxième partie, j'ai exploré différentes méthodes pour découper le texte en mots, visant à préparer le texte pour les analyses morphosyntaxiques ultérieures.

### 2.1 Tokéniseur "à base de règles" (Rule-based tokenizer)

J'ai utilisé [regex101.com](https://regex101.com/) pour tester des expressions régulières pour découper le texte en mots. J'ai commencé par une expression simple pour séparer les mots par des espaces, puis j'ai ajouté des règles pour gérer les cas spéciaux, comme les nombres, les abréviations, les mots composés, etc.


### 2.2 Librairie NLTK (Natural Language ToolKit)



### 2.3 Remarque et tokéniseur custom

