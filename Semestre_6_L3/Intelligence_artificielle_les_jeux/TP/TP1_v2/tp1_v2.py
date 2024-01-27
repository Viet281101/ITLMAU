
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

################################### TP1 : k-moyennes fleuries ######################################
"""
Il s'agit d'implémenter l'algorithme des k-moyennes à une base de données classique en apprentissage automatique : les iris. 
La base de données des iris est présentée ci-dessous, puis le travail est décrit. 
Enfin, l'algorithme est rappelé.
"""
## Présentation de la base de données des iris
# Classes :
# Iris setosa
# Iris versicolor
# Iris virginica

## Attributs :
# Longueur des sépales
# Largeur des sépales
# Longueur des pétales
# Largeur des pétales

# Répartition de la population, selon les attributs fournis : Iris Data (red=setosa, green=versicolor, blue=virginica)
# Travail à faire: k-moyennes et iris
#### IMPORTANT: sans utiliser scikit learn pour les k-moyennes.

# Rappel de l'algorithme des k-moyennes :
"""
INIT choisir aléatoirement k point comme centres
1. pour chaque point, affecter au cluster dont le centre est le plus proche
2. pour chaque cluster C, calculer le nouveau centre m
m = 1/|C| * somme des points de C
3. tant que affectation changent, itérer 1.
"""

## 1. Prendre en entrée deux fichiers, inclus dans l'archive iris/ : iris_data.csv & iris_label.csv
"""
Le fichier iris_data.csv est composé d'une donnée par ligne sous la forme :
5.0;3.3;1.4;0.2;
7.0;3.2;4.7;1.4;
6.5;3.2;5.1;2.0;

Le fichier label a le même nombre de lignes que le fichier data, chaque ligne indiquant la classe de la ligne correspondante dans le fichier data. Avec :
0 désigne la classe des iris setosa
1 désigne la classe des iris versicolor
2 désigne la classe des iris virginica
"""
def read_data(data_file, label_file) -> (pd.DataFrame, pd.DataFrame):
	data = pd.read_csv(data_file)
	labels = pd.read_csv(label_file)

	for column in data.columns:
		data[column] = pd.to_numeric(data[column], errors='coerce')

	data = data.dropna()

	return data, labels


## 2. Programmer, en python, l'algorithme des k-moyennes, de manière à pouvoir l'appliquer à différents jeux de données.
def k_means(data, k) -> (np.ndarray, np.ndarray):
	centroids = data[np.random.choice(data.shape[0], size=k, replace=False)]

	while True:
		distances = np.sqrt(((data - centroids[:, np.newaxis])**2).sum(axis=2))
		closest = np.argmin(distances, axis=0)

		new_centroids = np.array([data[closest==ki].mean(axis=0) for ki in range(k)])

		if np.all(centroids == new_centroids):
			break

		centroids = new_centroids

	return centroids, closest


## 3. Appliquer l'algorithme aux iris, en faisant varier la valeur de k (i.e. le nombre de clusters) et donnez le k minimal permettant d'obtenir des clusters contenant un unique type d'iris. Les classes (fichier label) seront utilisées pour vérifier la "pureté" des clusters.
def find_optimal_k(data, labels) -> (int, np.ndarray, np.ndarray):
	max_purity = 0
	optimal_k = 0
	optimal_centroids = None
	optimal_closest = None

	for k in range(1, len(data)):
		centroids, closest = k_means(data, k)
		clusters = [data[closest == ki] for ki in range(k)]
		purity = sum([len(set(cluster)) == 1 for cluster in clusters]) / k
		if purity > max_purity:
			max_purity = purity
			optimal_k = k
			optimal_centroids = centroids
			optimal_closest = closest

	return optimal_k, optimal_centroids, optimal_closest


## 4. Tester son implémentation sur les clusters gaussiens fournis dans le fichier clusters.py joint (sans utiliser les centres comme centroîdes). Comparer les résultats pour 2 à 6 clusters, que vous pourrez éloigner, rapprocher ou étendre (en taille).
def clusters_gen(n_clusters, n_points, centers, sigmas) -> np.ndarray:
	clusters = []

	for i in range(n_clusters):
		points = np.random.multivariate_normal(centers[i], sigmas[i], n_points[i])
		clusters.append(points)

	clusters = np.concatenate(clusters)

	plt.scatter(clusters[:, 0], clusters[:, 1])
	plt.show()

	return clusters


def main():
	data, labels = read_data('iris/iris_data.csv', 'iris/iris_label.csv')

	data = data.to_numpy()
	labels = labels.to_numpy()

	optimal_k, centroids, closest = find_optimal_k(data, labels)
	print(f'Optimal k for iris dataset: {optimal_k}')

	n_clusters = 3
	n_points = [50, 50, 50, 50]
	centers = [[1, 1], [1, -1], [-1, -1], [-1, 1]]
	sigmas = [[[0.1, 0], [0, 0.1]]]*n_clusters

	clusters = clusters_gen(n_clusters, n_points, centers, sigmas)

	optimal_k, centroids, closest = find_optimal_k(clusters, np.zeros(clusters.shape[0]))
	print(f'Optimal k for Gaussian clusters: {optimal_k}')



if __name__ == '__main__':
	main()
