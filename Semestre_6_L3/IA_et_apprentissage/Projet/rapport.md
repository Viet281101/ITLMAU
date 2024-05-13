# Clustering de données réelles, comparaison, évaluation et explications

Rapport de projet réalisé par __Viet Nguyen -- 20006303__.

## Introduction

### Objectif et Contexte

Ce projet vise à explorer et à comparer différents algorithmes de clustering sur un ensemble de données cliniques de défaillance cardiaque. L'objectif est de déterminer le nombre de clusters optimal et d'évaluer la qualité des clusters générés par chaque algorithme.

Source de donnée : [Heart Failure Clinical Records](https://www.kaggle.com/datasets/rabieelkharoua/predict-survival-of-patients-with-heart-failure?resource=download)

Ce projet repose sur le fichier notebook Jupyter `heart_failure.ipynb`, qui exécute chaque ligne de code en Python et affiche immédiatement les résultats dans le notebook.


## Méthodologie

### Préparation des Données

- Les données ont été normalisées à l'aide d'un scaling Min-Max pour garantir une contribution égale de chaque attribut dans le processus de clustering. Utilisation de la bibliotheque `pandas` pour le traitement des données.

```python
import pandas as pd
data = pd.read_csv('heart_failure_clinical_records_dataset.csv')
data.head()
```

- La colonne `DEATH_EVENT` a été supprimée car elle n'était pas pertinente pour l'analyse de clustering. Les données sont normalisées à l'aide d'un scaling Min-Max pour garantir une contribution égale de chaque attribut dans le processus de clustering.

```python
def min_max_scaling(df):
	for column in df.columns:
		min_col = df[column].min()
		max_col = df[column].max()
		df[column] = (df[column] - min_col) / (max_col - min_col)
	return df

data_scaled = min_max_scaling(data.drop(['DEATH_EVENT'], axis=1))
data_scaled.head()
```

### Algorithmes Utilisés

Les algorithmes suivants ont été utilisés :

- K-Means
- Clustering Hiérarchique
- DBSCAN
- Mean Shift
- Clustering Spectral
- Clustering Agglomératif

Détermination du Nombre Optimal de Clusters

- K-Means : Utilisation de la méthode du coude (Elbow Method) et de l'analyse Silhouette.
- Clustering Hiérarchique : Utilisation du dendrogramme pour déterminer le nombre de clusters.
- DBSCAN : Ajustement des paramètres eps et min_samples pour optimiser le clustering.
- Mean Shift : Estimation de la bande passante optimale pour déterminer le nombre de clusters.
- Clustering Spectral et Agglomératif : Utilisation de l'analyse Silhouette.




