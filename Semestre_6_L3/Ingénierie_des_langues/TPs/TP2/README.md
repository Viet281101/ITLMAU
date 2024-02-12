
# TP 2 : nombre moyen de mots par phrase et profilage morphosyntaxique

## 1. Découpage en phrases : test de différentes méthodes

Dans cette section, j'ai exploré différentes méthodes pour découper un texte en phrases, en vue de préparer le terrain pour une analyse morphosyntaxique plus approfondie.

### 1.1 Méthode basée sur des expressions régulières (Regex)

- **Description** : Utilisation de regex pour identifier les fins de phrases (., !, ?) et séparer le texte.
- **Implémentation** : Script `create_output_xml.py`, utilisant `re` pour les expressions régulières et `xml.etree.ElementTree` pour la création de XML.
- **Avantages** : Simplicité et efficacité sur des textes avec une ponctuation claire.
- **Inconvénients** : Peut échouer dans des cas où la ponctuation ne marque pas clairement la fin d'une phrase (ex. abréviations, nombres).

### 1.2 Méthode utilisant NLTK

- **Description** : Emploi de la bibliothèque NLTK pour un découpage plus nuancé, prenant en compte les particularités linguistiques du français.
- **Implémentation** : Script à développer, utilisant `nltk.tokenize` pour segmenter le texte.
- **Avantages** : Meilleure gestion des exceptions linguistiques grâce à l'analyse basée sur des modèles de langue.
- **Inconvénients** : Nécessite l'installation de NLTK et le téléchargement de modèles de langue spécifiques.

### 1.3 Méthode utilisant spaCy

- **Description** : Application de spaCy, une bibliothèque avancée de NLP, pour une segmentation précise et contextuelle des phrases.
- **Implémentation** : Script à développer, utilisant `spacy.load("fr_core_news_sm")` pour charger le modèle français et `doc.sents` pour la segmentation.
- **Avantages** : Précision accrue grâce à l'utilisation de modèles entraînés sur de larges corpus de texte.
- **Inconvénients** : Nécessite l'installation de spaCy et le téléchargement de modèles, ce qui peut être exigeant en termes de ressources.

### Conclusion

Cette exploration des différentes méthodes de segmentation de texte met en lumière les compromis entre simplicité et précision. La méthode idéale dépend des spécificités du corpus de texte à analyser ainsi que des objectifs de recherche.
