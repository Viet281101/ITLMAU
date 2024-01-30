
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

	print(f"Initialisation des centres des clusters :")
	print(centroids)
	
	history_centroids = [centroids]
	closest_history = []
	iteration = 0
	
	while True:
		distances = np.sqrt(((data - centroids[:, np.newaxis])**2).sum(axis=2))
		closest = np.argmin(distances, axis=0)
		closest_history.append(closest)
		new_centroids = np.array([data[closest==ki].mean(axis=0) for ki in range(k)])
		
		if np.all(centroids == new_centroids):
			break
		
		centroids = new_centroids
		history_centroids.append(centroids)
		closest_history.append(closest)
		iteration += 1

	print(f"Algorithme k-moyennes terminé en {iteration} itérations.")
		
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

	max_k = min(len(data), 7)

	for k in range(2, max_k):
		centroids, closest = k_means(data, k)

		clusters = [data[closest == ki] for ki in range(k)]

		purity = 0
		for ki in range(k):
			cluster_labels = labels[closest == ki]
			if cluster_labels.size == 0:
				continue

			most_common = np.bincount(cluster_labels).argmax()
			purity += np.sum(cluster_labels == most_common)

		purity /= len(data)

		print(f"Comparaison des résultats pour k = {k}:")
		print(f" - Nombre de clusters : {k}")
		print(f" - Pureté des clusters : {purity*100:.2f}%")

		if purity > max_purity:
			max_purity = purity
			optimal_k = k
			optimal_centroids = centroids[-1]
			optimal_closest = closest[-1]

	return optimal_k, optimal_centroids, optimal_closest





## 4. Tester son implémentation sur les clusters gaussiens. Comparer les résultats pour 2 à 6 clusters, que vous pourrez éloigner, rapprocher ou étendre (en taille).
def clusters_gen(n_clusters, n_points, centers, sigmas) -> np.ndarray:
	clusters = []

	for i in range(n_clusters):
		points = np.random.multivariate_normal(centers[i], sigmas[i], n_points[i])
		clusters.append(points)

	clusters = np.concatenate(clusters)

	# plt.scatter(clusters[:, 0], clusters[:, 1])
	# plt.show()

	print(f"Clusters gaussiens générés avec succès.")

	return clusters



def main():
	data, labels = read_data('iris/iris_data.csv', 'iris/iris_label.csv')

	data = data.to_numpy()
	labels = labels.to_numpy()

	optimal_k, centroids, closest = find_optimal_k(data, labels)
	print(f"Nombre optimal de clusters pour les données Iris : {optimal_k}")

	n_clusters = 3
	n_points = [50, 50, 50, 50]
	centers = [[1, 1], [1, -1], [-1, -1], [-1, 1]]
	sigmas = [[[0.1, 0], [0, 0.1]]] * n_clusters

	print(f"Génération de {n_clusters} clusters gaussiens avec {sum(n_points)} points...")
	clusters = clusters_gen(n_clusters, n_points, centers, sigmas)
	print("Clusters gaussiens générés avec succès.")

	print(f"Application de l'algorithme k-moyennes sur les clusters gaussiens...")
	animate(clusters)

	optimal_k, centroids, closest = find_optimal_k(clusters, np.zeros(clusters.shape[0]))
	print(f"Nombre optimal de clusters trouvé pour les clusters gaussiens : {optimal_k}")




if __name__ == '__main__':
	main()
