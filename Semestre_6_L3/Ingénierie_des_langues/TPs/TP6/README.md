
# IDL 14: Word Embeddings (`plongements lexicaux`)

Rapport de TP réalisé par __Viet Nguyen -- 20006303__.

## Exercice 1 : Constitution des sous-corpus

La lecture et la division des flux de données du fichier `HYPERBASE_Droite_VS_Gauche.txt` et l'impression des résultats dans deux fichiers `DROITE.txt` et `GAUCHE.txt` ont été effectuées dans le fichier `ex1.ipynb` à l'aide du jupyter notebook.


## Exercice 2 : Définition d'une classe `Embeddings`

 - Librairie et Modèle Utilisés :

	- Librairie Utilisée : `gensim`.
	- Modèle Spécifique : `Word2Vec` de la bibliothèque `gensim.models`.

- Limitations :

	- Prétraitement Simple :
		- La fonction `preprocess` se limite à supprimer la ponctuation et à convertir tous les caractères en minuscules, sans considérer d'autres étapes de prétraitement telles que la suppression des mots vides (stop words), le stemming ou la lemmatisation.
		- Ces étapes peuvent améliorer la qualité et la précision des embeddings en réduisant le bruit et le nombre de fonctionnalités non nécessaires.

	- Configuration Par Défaut de `Word2Vec` :
		- En utilisant la méthode `learn`, le modèle `Word2Vec` est initialisé avec ses paramètres par défaut.
		- Cela peut ne pas être idéal pour tous types de données. Par exemple, la taille des vecteurs (dimensionality) ou la taille de la fenêtre de contexte (window size) peut nécessiter des ajustements pour mieux refléter la nature des données utilisées.

- Deux Améliorations Possibles :

	- Amélioration du Prétraitement :
		- Intégrer une étape de prétraitement plus complète incluant la suppression des mots vides et l'application de stemming ou de lemmatisation.
		- Cela aide à épuré le texte et à se concentrer sur le contenu important, réduisant la taille du vocabulaire et améliorant la performance du modèle.

	- Ajustement Fin des Hyperparamètres :
		- Procéder à un ajustement fin des hyperparamètres du modèle `Word2Vec`, incluant la taille du vecteur (size), la taille de la fenêtre de contexte (window), le min_count (nombre minimum d'apparitions d'un mot pour être considéré dans le modèle), et le nombre d'itérations sur les données.
		- Cet ajustement peut être effectué à travers des méthodes telles que la recherche sur grille (grid search) ou la recherche aléatoire (random search) pour trouver le meilleur ensemble d'hyperparamètres pour les données spécifiques. Cela améliore la capacité de généralisation du modèle et la qualité des embeddings.



## Exercice 3 : Apprentissage des Embeddings sur nos corpus



