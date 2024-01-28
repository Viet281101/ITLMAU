
import random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

####### TP1 #######

# 1) Prendre enentrée deux fichiers csv dans le folder iris/ : iris_data.csv et iris_label.csv
# Le fichier iris_data est composé d'une donnée par ligne sous la forme :
# 5.0;3.3;1.4;0.2;
# 7.0;3.2;4.7;1.4;
# 6.5;3.2;5.1;2.0;
# Le fichier label a le même nombre de lignes que le fichier data, chaque ligne indiquant la classe de la ligne correspondante dans le fichier data. Avec :
# - 0 désigne la classe des iris setosa
# - 1 désigne la classe des iris versicolor
# - 2 désigne la classe des iris virginica

def read_csv(file) -> list:
	"""Reads a csv file and returns a list of lists"""
	with open(file, "r") as f:
		data = f.readlines()
		data = [line.strip().split(";") for line in data]
	return data


# 2) Programmer, en python, l'algorithme des k-moyennes, de manière à pouvoir l'appliquer à différents jeux de données.

def k_means(data, k) -> list:
	"""Applies the k-means algorithm to the data"""
	centroids = random.sample(data, k)

	while True:
		clusters = [[] for _ in range(k)]
		for point in data:
			distances = [np.linalg.norm(np.array(point) - np.array(centroid)) for centroid in centroids]
			closest_centroid = np.argmin(distances)
			clusters[closest_centroid].append(point)

		new_centroids = []
		for cluster in clusters:
			if cluster:
				new_centroid = np.mean(cluster, axis=0)
				new_centroids.append(new_centroid)
			else:
				new_centroids.append(data[random.randint(0, len(data) - 1)])

		if all(np.allclose(a, b) for a, b in zip(centroids, new_centroids)):
			break

		centroids = new_centroids

	return [i for point in data for i, cluster in enumerate(clusters) if point in cluster]



# 3) Appliquer l'algorithme aux iris, en faisant varier la valeur de k (i.e. le nombre de clusters) et donnez le k minimal permettant d'obtenir des clusters contenant un unique type d'iris. Les classes (fichier label) seront utilisées pour vérifier la "pureté" des clusters. 

def purity(clusters, labels) -> float:
	"""Computes the purity of the clusters"""
	total = 0
	unique_clusters = set(clusters)
	for cluster in unique_clusters:
		cluster_labels = [labels[i] for i, c in enumerate(clusters) if c == cluster]
		counts = np.bincount(cluster_labels)
		total += np.max(counts)
	return total / len(labels)


# 4)  Tester son implémentation sur les clusters gaussiens fournis dans le fichier clusters.py joint (sans utiliser les centres comme centroîdes). Comparer les résultats pour 2 à 6 clusters, que vous pourrez éloigner, rapprocher ou étendre (en taille).

def generate_clusters() -> np.ndarray:
	"""Generates clusters"""
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


def main() -> None:
	data = read_csv("iris/iris_data.csv")
	labels = read_csv("iris/iris_label.csv")
	labels = [int(label[0]) for label in labels]
	data = [[float(x) for x in point if x] for point in data]

	colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

	fig, ax = plt.subplots()

	def update(k):
		ax.clear()
		clusters = k_means(data, k)
		print("k =", k, "purity =", purity(clusters, labels))

		for i in range(k):
			cluster_points = [point for point, cluster in zip(data, clusters) if cluster == i]
			ax.scatter([point[0] for point in cluster_points], [point[1] for point in cluster_points], color=colors[i % len(colors)])

	ani = animation.FuncAnimation(fig, update, frames=range(2, 7), repeat=False)
	plt.show()


if __name__ == "__main__":
	main()

