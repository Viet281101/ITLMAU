
import numpy as np
import matplotlib.pyplot as plt


def read_csv(file_path):
	""" Read a csv file """
	data = []
	with open(file_path, "r") as file:
		for line in file:
			stripped_line = line.strip().rstrip(';')
			data.append(stripped_line.split(";"))
	return np.array(data, dtype=np.float32)


def epsilon_neighborhood(p, data, eps):
	""" Return the points in the epsilon neighborhood of p """
	neighbors = []
	for q in data:
		if np.linalg.norm(p - q) < eps:
			neighbors.append(q)
	return np.array(neighbors)


def is_core_point(p, data, eps, MinPts):
	""" Return True if p is a core point """
	neighbors = epsilon_neighborhood(p, data, eps)
	return len(neighbors) >= MinPts


def expand_cluster(p, neighborhood, clusters, cluster_id, data, eps, MinPts):
	""" Expand the cluster """
	clusters[data.tolist().index(p.tolist())] = cluster_id
	i = 0
	while i < len(neighborhood):
		p_neigh = neighborhood[i]
		if clusters[data.tolist().index(p_neigh.tolist())] == 0:
			clusters[data.tolist().index(p_neigh.tolist())] = cluster_id
			p_neighborhood = epsilon_neighborhood(p_neigh, data, eps)
			if len(p_neighborhood) >= MinPts:
				neighborhood = np.append(neighborhood, p_neighborhood, axis=0)
		elif clusters[data.tolist().index(p_neigh.tolist())] == -1:
			clusters[data.tolist().index(p_neigh.tolist())] = cluster_id
		i += 1


def dbscan(data, eps, MinPts):
	""" DBSCAN algorithm """
	clusters = np.zeros(len(data))
	cluster_id = 0
	for i in range(len(data)):
		if clusters[i] != 0:
			continue
		if is_core_point(data[i], data, eps, MinPts):
			cluster_id += 1
			clusters[i] = cluster_id
			neighborhood = epsilon_neighborhood(data[i], data, eps)
			expand_cluster(data[i], neighborhood, clusters, cluster_id, data, eps, MinPts)
	return clusters


def calculate_sse(clusters, data):
	""" Calculate the sum of squared errors """
	sse = 0
	for i in range(len(data)):
		cluster_id = int(clusters[i])
		sse += np.linalg.norm(data[i] - clusters[cluster_id])
	return sse


def calculate_silhouette(clusters, data):
	""" Calculate the silhouette """
	silhouette = 0
	for i in range(len(data)):
		cluster_id = int(clusters[i])
		cluster = data[clusters == cluster_id]
		a_i = np.mean(np.linalg.norm(data[i] - cluster))
		b_i = np.inf
		for j in range(len(data)):
			if clusters[j] != cluster_id:
				cluster_j = data[clusters == clusters[j]]
				b_i = min(b_i, np.mean(np.linalg.norm(data[i] - cluster_j)))
		silhouette += (b_i - a_i) / max(a_i, b_i)
	return silhouette / len(data)


def calculate_classification_rate(clusters, labels):
	""" Calculate the classification rate """
	nb_correct = 0
	for i in range(len(clusters)):
		if clusters[i] == labels[i]:
			nb_correct += 1
	return nb_correct / len(clusters)



def main():
	data_path = "iris/iris_data.csv"
	data = read_csv(data_path)

	label_path = "iris/iris_label.csv"
	labels = read_csv(label_path)


	eps = 0.5
	MinPts = 5
	clusters = dbscan(data, eps, MinPts)

	sse = calculate_sse(clusters, data)
	print(f"SSE: {sse}")

	silhouette = calculate_silhouette(clusters, data)
	print(f"Silhouette: {silhouette}")

	classification_rate = calculate_classification_rate(clusters, labels)
	print(f"Classification rate: {classification_rate}")


	# Plot the clusters
	plt.scatter(data[:, 0], data[:, 1], c=clusters)
	plt.show()


if __name__ == "__main__":
	main()

