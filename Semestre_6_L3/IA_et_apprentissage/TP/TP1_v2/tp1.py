
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

################################### TP1 : k-moyennes fleuries ######################################

## 1. Prendre en entrée deux fichiers, inclus dans l'archive iris/ : iris_data.csv & iris_label.csv
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
	print("Initial centroids:\n", centroids)
	
	history_centroids = [centroids]
	closest_history = []
	iteration = 0
	
	while True:
		distances = np.sqrt(((data - centroids[:, np.newaxis])**2).sum(axis=2))
		closest = np.argmin(distances, axis=0)
		closest_history.append(closest)
		new_centroids = np.array([data[closest==ki].mean(axis=0) for ki in range(k)])
		
		print(f"\nItération {iteration}:")
		print("Centroides:\n", centroids)
		print("Nouveaux centroïdes:\n", new_centroids)
		print("Point assignments:", closest)
		
		if np.all(centroids == new_centroids):
			print("Convergence atteinte à l'itération", iteration)
			break
		
		centroids = new_centroids
		history_centroids.append(centroids)
		closest_history.append(closest)
		iteration += 1
		
	return np.array(history_centroids), np.array(closest_history)


def update_plot(i, data, history_centroids, closest_history) -> None:
	plt.clf()
	colors = ['red', 'green', 'blue']
	centroids = history_centroids[i]
	closest = closest_history[i]

	for ki, color in zip(range(centroids.shape[0]), colors):
		plt.scatter(data[closest == ki, 0], data[closest == ki, 1], c=color, alpha=0.5)
		plt.scatter(*centroids[ki], marker='D', c=color, s=150)

	plt.title('Update Cluster Centers')
	plt.draw()


def animate(data):
	history_centroids, closest_history = k_means(data, k=3)

	fig = plt.figure()
	ani = FuncAnimation(fig, update_plot, frames=len(history_centroids), fargs=(data, history_centroids, closest_history), interval=300)

	plt.show()



## 3. Appliquer l'algorithme aux iris, en faisant varier la valeur de k (i.e. le nombre de clusters) et donnez le k minimal permettant d'obtenir des clusters contenant un unique type d'iris. Les classes (fichier label) seront utilisées pour vérifier la "pureté" des clusters.
def find_optimal_k(data, labels) -> (int, np.ndarray, np.ndarray):
	max_purity = 0
	optimal_k = 0
	optimal_centroids = None
	optimal_closest = None

	for k in range(1, len(data)):
		centroids, closest = k_means(data, k)
		print(data.shape)
		print(closest.shape)
		clusters = [data[closest == ki] for ki in range(k)]
		purity = sum([len(set(cluster)) == 1 for cluster in clusters]) / k
		if purity > max_purity:
			max_purity = purity
			optimal_k = k
			optimal_centroids = centroids
			optimal_closest = closest

	print(f"K optimal trouvé: {optimal_k}")
	print("Optimal centroides:\n", optimal_centroids)
	print("Optimal point assignments:", optimal_closest)
	
	return optimal_k, optimal_centroids, optimal_closest



## 4. Tester son implémentation sur les clusters gaussiens fournis dans le fichier clusters.py joint (sans utiliser les centres comme centroîdes). Comparer les résultats pour 2 à 6 clusters, que vous pourrez éloigner, rapprocher ou étendre (en taille).
def clusters_gen(n_clusters, n_points, centers, sigmas) -> np.ndarray:
	clusters = []

	for i in range(n_clusters):
		points = np.random.multivariate_normal(centers[i], sigmas[i], n_points[i])
		clusters.append(points)

	clusters = np.concatenate(clusters)

	# plt.scatter(clusters[:, 0], clusters[:, 1])
	# plt.show()

	return clusters



def main():
	data, labels = read_data('iris/iris_data.csv', 'iris/iris_label.csv')

	data = data.to_numpy()
	labels = labels.to_numpy()

	optimal_k, centroids, closest = find_optimal_k(data, labels)
	print(f"K optimal pour l'ensemble de données sur l'iris: {optimal_k}")
	print("Centroides pour optimal K:\n", centroids)
	print("Point assignments pour optimal K:\n", closest)

	n_clusters = 3
	n_points = [50, 50, 50, 50]
	centers = [[1, 1], [1, -1], [-1, -1], [-1, 1]]
	sigmas = [[[0.1, 0], [0, 0.1]]]*n_clusters

	clusters = clusters_gen(n_clusters, n_points, centers, sigmas)
	animate(clusters)

	optimal_k, centroids, closest = find_optimal_k(clusters, np.zeros(clusters.shape[0]))
	print(f'K optimal pour Gaussian clusters: {optimal_k}')



if __name__ == '__main__':
	main()
