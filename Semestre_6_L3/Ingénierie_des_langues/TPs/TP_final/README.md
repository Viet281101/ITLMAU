# IDL TP Final

Rapport de TP réalisé par **Viet Nguyen -- 20006303**.

## Introduction

Au cours de ce projet, j'ai été chargé de réaliser une analyse approfondie sur un jeu de données de critiques de films, extrait de l'archive [`imdb_smol.tar.gz`](https://github.com/LoicGrobol/apprentissage-artificiel/blob/main/data/imdb_smol.tar.gz). Ce jeu comprend 602 critiques textuelles, classées en critiques positives et négatives.

## Objectifs du projet

L'objectif principal de ce travail était de charger et vectoriser ces données pour ensuite entraîner et comparer différents classifieurs afin de déterminer lequel est le plus adapté pour classer correctement les critiques en fonction de leur sentiment. Les modèles testés incluaient la régression logistique, les machines à vecteurs de support (SVM), les arbres de décision, les forêts aléatoires, et le modèle bayésien naïf.

## Méthodologie

### Chargement et préparation des données

Les données ont été chargées et préparées pour l'analyse. Chaque critique a été associée à une étiquette : `1` pour positive et `0` pour négative.

### Vectorisation des textes

Pour traiter le texte, deux méthodes de vectorisation ont été utilisées : TF-IDF et Count Vectorizer. Ces méthodes permettent de transformer le texte en un format numérique que les modèles de machine learning peuvent traiter.

### Entraînement des modèles

Plusieurs modèles ont été entraînés en utilisant les caractéristiques extraites. Pour chaque modèle, la précision, la précision macro, le rappel macro et le score F1 macro ont été calculés et comparés.

## Résultats

Les modèles SVM et la régression logistique ont montré les meilleures performances, avec une précision atteignant jusqu'à 88,7% pour le SVM avec vectorisation TF-IDF. Les modèles basés sur les arbres, tels que les forêts aléatoires et les arbres de décision, ont montré des performances inférieures, ce qui suggère une moins bonne adaptation à ce type de données de texte.

## Conclusion

En conclusion, les expériences menées ont permis d'identifier les SVM comme le classifieur le plus performant pour ce jeu de données spécifique.

