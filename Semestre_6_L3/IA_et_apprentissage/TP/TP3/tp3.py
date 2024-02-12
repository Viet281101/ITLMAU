
import numpy as np
import matplotlib.pyplot as plt


### Read CSV files
def read_csv(file_path):
	data = []
	with open(file_path, "r") as file:
		for line in file:
			stripped_line = line.strip().rstrip(';')
			data.append(stripped_line.split(";"))
	return np.array(data, dtype=np.float32)


### Compute distance matrix
def compute_distance_matrix(data):
	num_samples = data.shape[0]
	distance_matrix = np.zeros((num_samples, num_samples))
	for i in range(num_samples):
		for j in range(i + 1, num_samples):
			distance = np.sqrt(np.sum((data[i] - data[j])**2))
			distance_matrix[i, j] = distance_matrix[j, i] = distance
	return distance_matrix


### Linkage methods
def simple_linkage(cluster1, cluster2, distance_matrix):
	return np.min([distance_matrix[i, j] for i in cluster1 for j in cluster2])

def complete_linkage(cluster1, cluster2, distance_matrix):
	return np.max([distance_matrix[i, j] for i in cluster1 for j in cluster2])

def average_linkage(cluster1, cluster2, distance_matrix):
	return np.mean([distance_matrix[i, j] for i in cluster1 for j in cluster2])


### Hierarchical clustering
def clustering(data, linkage_method, num_clusters):
	distance_matrix = compute_distance_matrix(data)
	clusters = [[i] for i in range(len(data))]
	while len(clusters) > num_clusters:
		min_distance = np.inf
		for i in range(len(clusters)):
			for j in range(i + 1, len(clusters)):
				distance = linkage_method(clusters[i], clusters[j], distance_matrix)
				if distance < min_distance:
					min_distance = distance
					to_merge = (i, j)
		new_cluster = clusters[to_merge[0]] + clusters[to_merge[1]]
		clusters.pop(max(to_merge))
		clusters.pop(min(to_merge))
		clusters.append(new_cluster)
	return clusters


### Visualization Dendrogram
def visualize_clusters(data, clusters, title):
	colors = ['red', 'green', 'blue']
	plt.figure(figsize=(10, 6))
	for cluster_index, cluster in enumerate(clusters):
		cluster_points = data[cluster]
		plt.scatter(cluster_points[:, 0], cluster_points[:, 1], color=colors[cluster_index])
	plt.title(title)
	plt.show()


def main():
	data_path = "iris/iris_data.csv"
	data = read_csv(data_path)

	label_path = "iris/iris_label.csv"
	labels = read_csv(label_path)

	
	clusters_simple = clustering(data, simple_linkage, 3)
	visualize_clusters(data, clusters_simple, "Clustering with Simple Linkage")

	
	clusters_complete = clustering(data, complete_linkage, 3)
	visualize_clusters(data, clusters_complete, "Clustering with Complete Linkage")

	
	clusters_average = clustering(data, average_linkage, 3)
	visualize_clusters(data, clusters_average, "Clustering with Average Linkage")


if __name__ == "__main__":
	main()
