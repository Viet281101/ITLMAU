
import random
import numpy as np
import matplotlib.pyplot as plt

def read_csv(file) -> list:
	"""Reads a csv file and returns a list of lists."""
	with open(file, "r") as f:
		data = f.readlines()
		data = [line.strip().split(";") for line in data]
	return data


def generate_clusters() -> np.ndarray:
	"""Generates clusters (keep this function unchanged as per your request)."""
	# C1 ---------->
	centre1=np.array([3,3])	           # centre du premier cluster
	sigma1=np.array([[1.5,0],[0,1.5]]) # matrice de covariance du premier cluster
	taille1=250                        # nombre de points du premier cluster
	cluster1=np.random.multivariate_normal(centre1,sigma1,taille1)
	# C1 <----------
	# C2 ---------->
	centre2=np.array([-3,-3])          # centre du second cluster
	sigma2=np.array([[1.5,0],[0,1.5]]) # matrice de covariance du second cluster
	taille2=200                        # nombre de points du second cluster
	cluster2=np.random.multivariate_normal(centre2,sigma2,taille2)
	# C2 <----------
	# C3 ---------->
	centre3=np.array([-3,3])          # centre du troisieme cluster
	sigma3=np.array([[1.5,0],[0,1.5]]) # matrice de covariance du second cluster
	taille3=300                        # nombre de points du second cluster
	cluster3=np.random.multivariate_normal(centre3,sigma3,taille3)
	# C3 <----------
	# C4 ---------->
	centre4=np.array([3,-3])          # centre du quatrieme cluster
	sigma4=np.array([[1.5,0],[0,1.5]]) # matrice de covariance du second cluster
	taille4=150                        # nombre de points du second cluster
	cluster4=np.random.multivariate_normal(centre4,sigma4,taille4)
	# C4 <----------
	clusters=np.concatenate((cluster1, cluster2, cluster3, cluster4))
	return clusters


def euclidean_distance(point1, point2) -> float:
	"""Calculate the Euclidean distance between two points."""
	return np.linalg.norm(np.array(point1) - np.array(point2))

def calculate_distance_matrix(data) -> np.ndarray:
	"""Calculate the distance matrix for a dataset."""
	n = len(data)
	distance_matrix = np.zeros((n, n))
	for i in range(n):
		for j in range(i + 1, n):
			distance = euclidean_distance(data[i], data[j])
			distance_matrix[i, j] = distance
			distance_matrix[j, i] = distance
	return distance_matrix


def hierarchical_clustering(data, linkage_method) -> tuple:
	"""Performs hierarchical clustering on a dataset."""
	distance_matrix = calculate_distance_matrix(data)
	n = len(data)
	cluster_labels = list(range(n))
	cluster_history = []

	while n > 1:
		i, j = np.unravel_index(np.argmin(distance_matrix + np.eye(n)*np.max(distance_matrix)), distance_matrix.shape)

		for k in range(len(cluster_labels)):
			if cluster_labels[k] == j:
				cluster_labels[k] = i

		cluster_history.append((i, j, distance_matrix[i, j]))

		for k in range(len(distance_matrix)):
			if k != i and k != j:
				if linkage_method == 'single':
					distance_matrix[i, k] = distance_matrix[k, i] = min(distance_matrix[i, k], distance_matrix[j, k])
				elif linkage_method == 'complete':
					distance_matrix[i, k] = distance_matrix[k, i] = max(distance_matrix[i, k], distance_matrix[j, k])
				elif linkage_method == 'average':
					distance_matrix[i, k] = distance_matrix[k, i] = (distance_matrix[i, k] + distance_matrix[j, k]) / 2
				### Le Ward linkage method n'est pas implémenté ici. Parce que c'est plus compliqué à implémenter.

		distance_matrix = np.delete(distance_matrix, j, axis=0)
		distance_matrix = np.delete(distance_matrix, j, axis=1)
		n -= 1

	final_clusters = {}
	for idx, label in enumerate(cluster_labels):
		if label in final_clusters:
			final_clusters[label].append(data[idx])
		else:
			final_clusters[label] = [data[idx]]

	return final_clusters, cluster_history



def main() -> None:
	data = generate_clusters()
	linkage_method = 'single' # 'single', 'complete', ou 'average'

	clusters, history = hierarchical_clustering(data, linkage_method)
	# print("History of clusters:", history)

	for label, points in clusters.items():
		points = np.array(points)
		plt.scatter(points[:, 0], points[:, 1], label=f"Cluster {label}")

	plt.legend()
	plt.show()




if __name__ == "__main__":
	main()
