"""
Apply different clustering algorithms to the heart failure dataset and evaluate
them using Silhouette Score.

The dataset is available at:
https://www.kaggle.com/datasets/rabieelkharoua/predict-survival-of-patients-with-heart-failure?resource=download

The goal is to cluster patients into groups based on their medical records.
"""

import numpy as np
import pandas as pd

# Load the dataset
data = pd.read_csv('data/heart_failure_clinical_records_dataset.csv')

# Check basic information about the dataset
data.info()

# Check for missing values
data.isnull().sum()


# Prepare the data for clustering
def min_max_scaling(df):
	"""
	Apply min-max scaling to a DataFrame without using external libraries.

	Parameters:
		df (DataFrame): The input data frame.

	Returns:
		DataFrame: The scaled data frame.
	"""
	for column in df.columns:
		min_col = df[column].min()
		max_col = df[column].max()
		df[column] = (df[column] - min_col) / (max_col - min_col)
	return df

# Applying min-max scaling manually
data_scaled = min_max_scaling(data.drop(['DEATH_EVENT'], axis=1))
data_scaled.head()


from sklearn.cluster import KMeans
def apply_kmeans(data, n_clusters=3):
	"""
	Apply K-Means clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		n_clusters (int): The number of clusters.

	Returns:
		array: The cluster labels for each patient.
	"""
	kmeans = KMeans(n_clusters=n_clusters, random_state=0)
	clusters = kmeans.fit_predict(data)
	return clusters
# Apply K-Means
kmeans_clusters = apply_kmeans(data_scaled)


from sklearn.cluster import AgglomerativeClustering
def apply_hierarchical(data, n_clusters=3):
	"""
	Apply Hierarchical Clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		n_clusters (int): The number of clusters.

	Returns:
		array: The cluster labels for each patient.
	"""
	clustering = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = clustering.fit_predict(data)
	return clusters
# Apply Hierarchical Clustering
hierarchical_clusters = apply_hierarchical(data_scaled)


from sklearn.cluster import DBSCAN
def apply_dbscan(data, eps=0.5, min_samples=5):
	"""
	Apply DBSCAN clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		eps (float): The maximum distance between two samples for them to be
			considered as in the same neighborhood.
		min_samples (int): The number of samples in a neighborhood for a
			point to be considered as a core point.

	Returns:
		array: The cluster labels for each patient.
	"""
	dbscan = DBSCAN(eps=eps, min_samples=min_samples)
	clusters = dbscan.fit_predict(data)
	return clusters
# Apply DBSCAN
dbscan_clusters = apply_dbscan(data_scaled)


from sklearn.cluster import MeanShift
def apply_mean_shift(data, bandwidth=None):
	"""
	Apply Mean Shift clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		bandwidth (float): The bandwidth of the kernel. If not provided, it is
			computed automatically.

	Returns:
		array: The cluster labels for each patient.
	"""
	mean_shift = MeanShift(bandwidth=bandwidth)
	clusters = mean_shift.fit_predict(data)
	return clusters
# Apply Mean Shift
mean_shift_clusters = apply_mean_shift(data_scaled)


from sklearn.cluster import SpectralClustering
def apply_spectral(data, n_clusters=3):
	"""
	Apply Spectral Clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		n_clusters (int): The number of clusters.

	Returns:
		array: The cluster labels for each patient.
	"""
	spectral = SpectralClustering(n_clusters=n_clusters, random_state=0)
	clusters = spectral.fit_predict(data)
	return clusters
# Apply Spectral Clustering
spectral_clusters = apply_spectral(data_scaled)


def apply_agglomerative(data, n_clusters=3):
	"""
	Apply Agglomerative Clustering to the data.

	Parameters:
		data (DataFrame): The scaled data.
		n_clusters (int): The number of clusters.

	Returns:
		array: The cluster labels for each patient.
	"""
	agglomerative = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = agglomerative.fit_predict(data)
	return clusters
# Apply Agglomerative Clustering
agglomerative_clusters = apply_agglomerative(data_scaled)


#### Evaluation
from sklearn.metrics import silhouette_score

def evaluate_clustering_algorithms(data, cluster_labels):
	"""
	Evaluate clustering algorithms using Silhouette Score.
	
	Parameters:
		data (DataFrame): The scaled data used for clustering.
		cluster_labels (dict): A dictionary containing the cluster labels from different algorithms.
	
	Returns:
		DataFrame: A DataFrame containing the silhouette scores of each algorithm.
	"""
	scores = {}
	for algorithm, labels in cluster_labels.items():
		if len(set(labels)) > 1:  # Check if there's more than one cluster
			score = silhouette_score(data, labels)
			scores[algorithm] = score
		else:
			scores[algorithm] = None  # Not applicable if only one cluster
	
	return pd.DataFrame(list(scores.items()), columns=['Algorithm', 'Silhouette Score'])

# Dictionary of cluster labels from various algorithms
cluster_labels = {
	'K-Means': kmeans_clusters,
	'Hierarchical': hierarchical_clusters,
	'DBSCAN': dbscan_clusters,
	'Mean Shift': mean_shift_clusters,
	'Spectral': spectral_clusters,
	'Agglomerative': agglomerative_clusters
}

# Evaluate all clustering algorithms
evaluation_results = evaluate_clustering_algorithms(data_scaled, cluster_labels)
evaluation_results


