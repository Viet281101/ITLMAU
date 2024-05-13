import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import silhouette_score
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.cluster import KMeans, AgglomerativeClustering, DBSCAN, MeanShift, SpectralClustering
from sklearn.preprocessing import MinMaxScaler


def plot_clusters(data, labels, title) -> None:
	unique_labels = np.unique(labels)
	plt.figure(figsize=(10, 6))
	for label in unique_labels:
		plt.scatter(data[labels == label, 0], data[labels == label, 1], label=f'Cluster {label}')
	plt.title(title)
	plt.xlabel('PCA Component 1')
	plt.ylabel('PCA Component 2')
	plt.legend()
	plt.show()

def min_max_scaling(df) -> pd.DataFrame:
	scaler = MinMaxScaler()
	return scaler.fit_transform(df)

def apply_kmeans(data, n_clusters=3) -> np.ndarray:
	kmeans = KMeans(n_clusters=n_clusters, random_state=0)
	clusters = kmeans.fit_predict(data)
	return clusters

def apply_hierarchical(data, n_clusters=3) -> np.ndarray:
	clustering = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = clustering.fit_predict(data)
	return clusters

def apply_dbscan(data, eps=0.5, min_samples=5) -> np.ndarray:
	dbscan = DBSCAN(eps=eps, min_samples=min_samples)
	clusters = dbscan.fit_predict(data)
	return clusters

def apply_mean_shift(data, bandwidth=None) -> np.ndarray:
	mean_shift = MeanShift(bandwidth=bandwidth)
	clusters = mean_shift.fit_predict(data)
	return clusters

def apply_spectral(data, n_clusters=3) -> np.ndarray:
	spectral = SpectralClustering(n_clusters=n_clusters, random_state=0)
	clusters = spectral.fit_predict(data)
	return clusters

def apply_agglomerative(data, n_clusters=3) -> np.ndarray:
	agglomerative = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = agglomerative.fit_predict(data)
	return clusters

def evaluate_clustering_algorithms(data, cluster_labels) -> pd.DataFrame:
	scores = {}
	for algorithm, labels in cluster_labels.items():
		if len(set(labels)) > 1:
			score = silhouette_score(data, labels)
			scores[algorithm] = score
		else:
			scores[algorithm] = None
	return pd.DataFrame(list(scores.items()), columns=['Algorithm', 'Silhouette Score'])


def main() -> None:
	# Charger les données
	data = pd.read_csv('data/heart_failure_clinical_records_dataset.csv')

	# Préparer les données
	data_scaled = min_max_scaling(data.drop(['DEATH_EVENT'], axis=1))

	# Algorithmes de clustering
	kmeans_clusters = apply_kmeans(data_scaled)
	hierarchical_clusters = apply_hierarchical(data_scaled)
	dbscan_clusters = apply_dbscan(data_scaled)
	mean_shift_clusters = apply_mean_shift(data_scaled)
	spectral_clusters = apply_spectral(data_scaled)
	agglomerative_clusters = apply_agglomerative(data_scaled)

	# Évaluer les scores de Silhouette
	cluster_labels = {
		'K-Means': kmeans_clusters,
		'Clustering hiérarchique': hierarchical_clusters,
		'DBSCAN': dbscan_clusters,
		'Clustering par décalage moyen': mean_shift_clusters,
		'Spectral': spectral_clusters,
		'Agglomération': agglomerative_clusters
	}
	evaluation_results = evaluate_clustering_algorithms(data_scaled, cluster_labels)
	print(evaluation_results)

	# Optimiser le nombre de clusters
	optimal_kmeans = KMeans(n_clusters=7, random_state=42)
	optimal_kmeans_clusters = optimal_kmeans.fit_predict(data_scaled)
	score_kmeans_optimal = silhouette_score(data_scaled, optimal_kmeans_clusters)
	print("Score de Silhouette pour K-Means:", score_kmeans_optimal)

	hierarchical_optimal = AgglomerativeClustering(n_clusters=7)
	hierarchical_labels_optimal = hierarchical_optimal.fit_predict(data_scaled)
	score_hierarchical_optimal = silhouette_score(data_scaled, hierarchical_labels_optimal)
	print("Score de Silhouette pour Clustering hiérarchique:", score_hierarchical_optimal)

	# Visualisation des clusters
	# PCA
	pca = PCA(n_components=2)
	data_pca = pca.fit_transform(data_scaled)

	plot_clusters(data_pca, kmeans_clusters, 'Clustering K-Means')
	plot_clusters(data_pca, hierarchical_clusters, 'Clustering hiérarchique')
	plot_clusters(data_pca, dbscan_clusters, 'Clustering DBSCAN')
	plot_clusters(data_pca, mean_shift_clusters, 'Clustering par décalage moyen')
	plot_clusters(data_pca, spectral_clusters, 'Clustering spectral')
	plot_clusters(data_pca, agglomerative_clusters, 'Agglomération')

	# t-SNE
	tsne = TSNE(n_components=2, random_state=42)
	data_tsne = tsne.fit_transform(data_scaled)

	plot_clusters(data_tsne, kmeans_clusters, 'Clustering K-Means (t-SNE)')
	plot_clusters(data_tsne, hierarchical_clusters, 'Clustering hiérarchique (t-SNE)')
	plot_clusters(data_tsne, dbscan_clusters, 'Clustering DBSCAN (t-SNE)')
	plot_clusters(data_tsne, mean_shift_clusters, 'Clustering par décalage moyen (t-SNE)')
	plot_clusters(data_tsne, spectral_clusters, 'Clustering spectral (t-SNE)')
	plot_clusters(data_tsne, agglomerative_clusters, 'Agglomération (t-SNE)')


if __name__ == '__main__':
	main()

