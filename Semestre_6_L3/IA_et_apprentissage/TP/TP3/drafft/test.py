
import numpy as np
import matplotlib.pyplot as plt


def read_csv(file_path) -> list:
	"""Reads a CSV file and returns a list of lists."""
	data = []
	with open(file_path, "r") as file:
		for line in file:
			stripped_line = line.strip().rstrip(';')
			data.append(stripped_line.split(";"))
	return data


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
				else:
					raise ValueError("Invalid linkage method.")

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
	"""Main function."""
	data_path = "iris/iris_data.csv"
	label_path = "iris/iris_label.csv"
	data = np.array(read_csv(data_path), dtype=float)
	labels = np.array(read_csv(label_path), dtype=int).flatten()

	linkage_method = 'single'  # 'single', 'complete', 'average'
	final_clusters, cluster_history = hierarchical_clustering(data, linkage_method)

	print("History of clusters:", cluster_history)

	for label, points in final_clusters.items():
		points = np.array(points)
		plt.scatter(points[:, 0], points[:, 1], label=f"Cluster {label}")

	plt.legend()
	plt.show()



if __name__ == "__main__":
	main()
