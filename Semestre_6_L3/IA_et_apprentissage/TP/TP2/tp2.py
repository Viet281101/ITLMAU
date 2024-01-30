

import numpy as np
import pandas as pd


"""
TP2 : Mesure, qualité et nombre de clusters ...
L'objectif de ce TP est d'étendre celui sur les k-moyennes. 
Si ce n'est pas déjà le cas, s'assurer que l'implémentation tourne indifféremment sur tout type de données, en particulier les iris et les clusters joints. 
Ensuite ajouter :

1. une (ou plusieurs) autre mesure de distance
2. un calcul de SSE (cf. transparents joints)
3. utiliser ce calcul pour vérifier le meilleur nombre de clusters à demander dans chacun des cas étudiés (iris et clusters) en faisant varier k de 1 à 10
4. implémenter la méthode silhouette et l'appliquer à tous les clusterings
"""

def read_data(data_file, label_file) -> (pd.DataFrame, pd.DataFrame):
	data = pd.read_csv(data_file)
	labels = pd.read_csv(label_file)

	for column in data.columns:
		data[column] = pd.to_numeric(data[column], errors='coerce')

	data = data.dropna()

	return data, labels


### 1. une (ou plusieurs) autre mesure de distance ###
def distance_euclidienne(x, y) -> float:
	return np.sqrt(np.sum((x - y)**2))

def distance_minkowski(x, y, p) -> float:
	return np.sum(np.abs(x - y)**p)**(1/p)

def distance_cosinus(x, y) -> float:
	return np.dot(x, y) / (np.linalg.norm(x) * np.linalg.norm(y))

def distance_chebyshev(x, y) -> float:
	return np.max(np.abs(x - y))

def distance_minkowski(x, y, p) -> float:
	return np.sum(np.abs(x - y)**p)**(1/p)

def distance_cosinus(x, y) -> float:
	return np.dot(x, y) / (np.linalg.norm(x) * np.linalg.norm(y))



### 2. un calcul de SSE (cf. transparents joints) ###
def k_means(data, k, distance_func, max_iterations=100) -> (pd.DataFrame, dict):
	centroids = data.sample(n=k)
	
	for iteration in range(max_iterations):
		clusters = {}
		for index, point in data.iterrows():
			closest_centroid_index = min(range(k), key=lambda i: distance_func(point, centroids.iloc[i]))
			if closest_centroid_index in clusters:
				clusters[closest_centroid_index].append(index)
			else:
				clusters[closest_centroid_index] = [index]

		new_centroids = pd.DataFrame(columns=data.columns)
		for i in range(k):
			cluster_points = data.loc[clusters[i]]
			new_centroid = cluster_points.mean()
			new_centroids = new_centroids.append(new_centroid, ignore_index=True)

		if centroids.equals(new_centroids):
			break
		centroids = new_centroids
	
	return centroids, clusters



def calculate_sse(data, k, distance_func, max_iterations=100) -> list:
	sse_values = []
	num_data_points = len(data)

	if k > num_data_points:
		raise ValueError("Number of clusters (k) should be less than or equal to the number of data points.")

	for num_clusters in range(1, k + 1):
		centroids, clusters = k_means(data, num_clusters, distance_func, max_iterations)
		sse = 0
		for i in range(num_clusters):
			cluster_points = data.loc[clusters[i]]
			cluster_centroid = centroids.iloc[i]
			sse += np.sum([distance_func(point, cluster_centroid) ** 2 for _, point in cluster_points.iterrows()])
		sse_values.append(sse)

	return sse_values




### 3. utiliser ce calcul pour vérifier le meilleur nombre de clusters à demander dans chacun des cas étudiés (iris et clusters) en faisant varier k de 1 à 10 ###
def calculate_silhouette(data, k, distance_func, max_iterations=100):
	silhouette_values = []
	
	for num_clusters in range(2, k+1):
		centroids, clusters = k_means(data, num_clusters, distance_func, max_iterations)
		silhouettes = []
		
		for index, point in data.iterrows():
			cluster_index = -1
			for i in range(num_clusters):
				if index in clusters[i]:
					cluster_index = i
					break
			
			a = np.mean([distance_func(point, data.loc[j]) for j in clusters[cluster_index]])
			b_values = []
			for i in range(num_clusters):
				if i != cluster_index:
					b_values.append(np.mean([distance_func(point, data.loc[j]) for j in clusters[i]]))
			
			b = min(b_values) if b_values else 0
			silhouette = (b - a) / max(a, b)
			silhouettes.append(silhouette)
		
		silhouette_avg = np.mean(silhouettes)
		silhouette_values.append(silhouette_avg)
	
	return silhouette_values



def main():
	data, labels = read_data('iris/iris_data.csv', 'iris/iris_label.csv')
	num_data_points = len(data)

	max_k = min(10, num_data_points)
	for k in range(1, max_k + 1):
		sse_values = calculate_sse(data, k, distance_euclidienne)

		for num_clusters, sse in enumerate(sse_values, start=1):
			print(f'Nombre de clusters (k) = {num_clusters}, SSE = {sse}')

		best_k_sse = np.argmin(sse_values) + 1

		print(f"Le meilleur nombre de clusters selon SSE est : {best_k_sse}")

		silhouette_values = calculate_silhouette(data, k, distance_euclidienne)

		for num_clusters, silhouette in enumerate(silhouette_values, start=2):
			print(f'Nombre de clusters (k) = {num_clusters}, Silhouette = {silhouette}')


if __name__ == '__main__':
	main()




