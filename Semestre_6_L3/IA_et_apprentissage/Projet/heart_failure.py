import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import silhouette_score
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.cluster import KMeans, AgglomerativeClustering, DBSCAN, MeanShift, SpectralClustering
from sklearn.metrics import estimate_bandwidth
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
	# Load Data
	data = pd.read_csv('data/heart_failure_clinical_records_dataset.csv')

	# Prepare Data
	data_scaled = min_max_scaling(data.drop(['DEATH_EVENT'], axis=1))

	# Clustering Algorithms
	kmeans_clusters = apply_kmeans(data_scaled)
	hierarchical_clusters = apply_hierarchical(data_scaled)
	dbscan_clusters = apply_dbscan(data_scaled)
	mean_shift_clusters = apply_mean_shift(data_scaled)
	spectral_clusters = apply_spectral(data_scaled)
	agglomerative_clusters = apply_agglomerative(data_scaled)

	# Evaluate Silhouette Scores
	cluster_labels = {
		'K-Means': kmeans_clusters,
		'Hierarchical': hierarchical_clusters,
		'DBSCAN': dbscan_clusters,
		'Mean Shift': mean_shift_clusters,
		'Spectral': spectral_clusters,
		'Agglomerative': agglomerative_clusters
	}
	evaluation_results = evaluate_clustering_algorithms(data_scaled, cluster_labels)
	print(evaluation_results)

	# Optimize Number of Clusters
	optimal_kmeans = KMeans(n_clusters=7, random_state=42)
	optimal_kmeans_clusters = optimal_kmeans.fit_predict(data_scaled)
	score_kmeans_optimal = silhouette_score(data_scaled, optimal_kmeans_clusters)
	print("Silhouette Score for K-Means:", score_kmeans_optimal)

	hierarchical_optimal = AgglomerativeClustering(n_clusters=7)
	hierarchical_labels_optimal = hierarchical_optimal.fit_predict(data_scaled)
	score_hierarchical_optimal = silhouette_score(data_scaled, hierarchical_labels_optimal)
	print("Silhouette Score for Hierarchical Clustering:", score_hierarchical_optimal)

	# Visualisation des clusters
	# PCA
	pca = PCA(n_components=2)
	data_pca = pca.fit_transform(data_scaled)

	plot_clusters(data_pca, kmeans_clusters, 'K-Means Clustering')
	plot_clusters(data_pca, hierarchical_clusters, 'Hierarchical Clustering')
	plot_clusters(data_pca, dbscan_clusters, 'DBSCAN Clustering')
	plot_clusters(data_pca, mean_shift_clusters, 'Mean Shift Clustering')
	plot_clusters(data_pca, spectral_clusters, 'Spectral Clustering')
	plot_clusters(data_pca, agglomerative_clusters, 'Agglomerative Clustering')

	# t-SNE
	tsne = TSNE(n_components=2, random_state=42)
	data_tsne = tsne.fit_transform(data_scaled)

	plot_clusters(data_tsne, kmeans_clusters, 'K-Means Clustering (t-SNE)')
	plot_clusters(data_tsne, hierarchical_clusters, 'Hierarchical Clustering (t-SNE)')
	plot_clusters(data_tsne, dbscan_clusters, 'DBSCAN Clustering (t-SNE)')
	plot_clusters(data_tsne, mean_shift_clusters, 'Mean Shift Clustering (t-SNE)')
	plot_clusters(data_tsne, spectral_clusters, 'Spectral Clustering (t-SNE)')
	plot_clusters(data_tsne, agglomerative_clusters, 'Agglomerative Clustering (t-SNE)')



if __name__ == '__main__':
	main()

