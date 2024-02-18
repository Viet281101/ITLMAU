
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def epsilon_neighborhood(p, data, eps) -> np.ndarray:
	""" Return the points in the epsilon neighborhood of p """
	distances = np.linalg.norm(data - p, axis=1)
	neighbors_idx = np.where(distances <= eps)[0]
	return neighbors_idx


def is_core_point(p_idx, data, eps, MinPts) -> bool:
	"""
	Check if the point at index p_idx is a core point.
	
	Parameters:
	p_idx (int): Index of the point in the dataset.
	data (numpy.ndarray): The dataset.
	eps (float): The epsilon value for the neighborhood.
	MinPts (int): The minimum number of points to define a core point.
	
	Returns:
	bool: True if the point is a core point, False otherwise.
	"""
	neighbors_idx = epsilon_neighborhood(data[p_idx], data, eps)
	return len(neighbors_idx) >= MinPts


def expand_cluster(core_pt_idx, data, eps, MinPts, cluster_id, clusters, visited):
	"""
	Expand the cluster to include all density-reachable points.
	
	Parameters:
	core_pt_idx (int): Index of the core point from which to expand the cluster.
	data (numpy.ndarray): The dataset.
	eps (float): The epsilon value for the neighborhood.
	MinPts (int): The minimum number of points to define a core point.
	cluster_id (int): The cluster ID to assign to the new points in the cluster.
	clusters (numpy.ndarray): The array where cluster IDs are stored.
	visited (numpy.ndarray): The array to keep track of visited points.
	"""
	neighbors = epsilon_neighborhood(data[core_pt_idx], data, eps)

	clusters[core_pt_idx] = cluster_id
	for neighbor_idx in neighbors:
		clusters[neighbor_idx] = cluster_id

	i = 0
	while i < len(neighbors):
		neighbor_idx = neighbors[i]
		if not visited[neighbor_idx]:
			visited[neighbor_idx] = True

			neighbor_pt_neighbors = epsilon_neighborhood(data[neighbor_idx], data, eps)

			if len(neighbor_pt_neighbors) >= MinPts:
				neighbors = np.append(neighbors, neighbor_pt_neighbors)

		if clusters[neighbor_idx] == 0:
			clusters[neighbor_idx] = cluster_id
		i += 1


def calculate_sse(clusters, data) -> float:
	""" Calculate the sum of squared errors """
	sse = 0
	for cluster_id in np.unique(clusters):
		if cluster_id == 0:
			continue
		cluster_data = data[clusters == cluster_id]
		centroid = np.mean(cluster_data, axis=0)
		sse += np.sum((cluster_data - centroid) ** 2)
	return sse


def calculate_silhouette(clusters, data) -> float:
	""" Calculate the silhouette """
	silhouette = 0
	for i in range(len(data)):
		cluster_id = int(clusters[i])
		cluster = data[clusters == cluster_id]
		a_i = np.mean(np.linalg.norm(data[i] - cluster, axis=1))
		b_i = np.inf
		for j in np.unique(clusters):
			if j != cluster_id and j != 0:
				cluster_j = data[clusters == j]
				distance = np.mean(np.linalg.norm(data[i] - cluster_j, axis=1))
				b_i = min(b_i, distance)
		if b_i == np.inf:
			b_i = a_i
		silhouette += (b_i - a_i) / max(a_i, b_i)
	return silhouette / len(data)


def calculate_classification_rate(clusters, labels) -> float:
	""" Calculate the classification rate """
	nb_correct = 0
	for i in range(len(clusters)):
		if clusters[i] == labels[i]:
			nb_correct += 1
	return nb_correct / len(clusters)



def dbscan(data, eps, MinPts) -> np.ndarray:
	""" DBSCAN algorithm """
	clusters = np.zeros(len(data))
	cluster_id = 0
	visited = np.zeros(len(data), dtype=bool)
	for i in range(len(data)):
		if visited[i]:
			continue
		visited[i] = True
		if is_core_point(i, data, eps, MinPts):
			cluster_id += 1
			expand_cluster(i, data, eps, MinPts, cluster_id, clusters, visited)
	return clusters


def main() -> None:
	iris_data_path = 'iris/iris_data.csv'
	iris_label_path = 'iris/iris_label.csv'

	iris_data = pd.read_csv(iris_data_path, header=None, delimiter=';')
	iris_labels = pd.read_csv(iris_label_path, header=None, delimiter=';')
	
	iris_labels = iris_labels.iloc[:, 0]

	eps = 0.5
	MinPts = 5

	clusters = dbscan(iris_data.values, eps, MinPts)
	sse = calculate_sse(clusters, iris_data.values)
	silhouette = calculate_silhouette(clusters, iris_data.values)
	classification_rate = calculate_classification_rate(clusters, iris_labels)

	print(f"SSE: {sse}")
	print(f"Silhouette: {silhouette}")
	print(f"Classification rate: {classification_rate}")

	plt.figure(figsize=(12, 8))
	unique_clusters = np.unique(clusters)
	for cluster_id in unique_clusters:
		if cluster_id == 0:
			label = 'Bruit'
			color = 'k'
			alpha = 0.5
		else:
			label = f'Cluster {int(cluster_id)}'
			color = None
			alpha = 1.0
		plt.scatter(iris_data.values[clusters == cluster_id, 0], 
					iris_data.values[clusters == cluster_id, 1], 
					c=color, label=label, alpha=alpha, edgecolors='w')

	plt.title("Visualisation des résultats de DBSCAN")
	plt.xlabel("Caractéristique 1")
	plt.ylabel("Caractéristique 2")
	plt.legend()
	plt.show()



if __name__ == "__main__":
	main()

