# %% [markdown]
# # Test: Clustering

# %% [markdown]
# ## Load Data

# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# %%
data = pd.read_csv('data/heart_failure_clinical_records_dataset.csv')

# %%
data.head()

# %%
data.info()

# %%
data.isnull().sum()

# %% [markdown]
# ## Prepare Data

# %%
def min_max_scaling(df):
	for column in df.columns:
		min_col = df[column].min()
		max_col = df[column].max()
		df[column] = (df[column] - min_col) / (max_col - min_col)
	return df

# %%
data_scaled = min_max_scaling(data.drop(['DEATH_EVENT'], axis=1))
data_scaled.head()

# %% [markdown]
# ## Clustering Algorithms

# %%
from sklearn.metrics import silhouette_score

# %% [markdown]
# ### K-Means

# %%
from sklearn.cluster import KMeans

# %%
def apply_kmeans(data, n_clusters=3):
	kmeans = KMeans(n_clusters=n_clusters, random_state=0)
	clusters = kmeans.fit_predict(data)
	return clusters

# %%
# Apply K-Means
kmeans_clusters = apply_kmeans(data_scaled)

# %%
score_kmeans = silhouette_score(data_scaled, kmeans_clusters)
print("Silhouette Score for K-Means:", score_kmeans)

# %% [markdown]
# ### Hierarchical Clustering

# %%
from sklearn.cluster import AgglomerativeClustering

# %%
def apply_hierarchical(data, n_clusters=3):
	clustering = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = clustering.fit_predict(data)
	return clusters

# %%
hierarchical_clusters = apply_hierarchical(data_scaled)

# %%
score_hierarchical = silhouette_score(data_scaled, hierarchical_clusters)
print("Silhouette Score for Hierarchical Clustering:", score_hierarchical)

# %% [markdown]
# ### DBSCAN

# %%
from sklearn.cluster import DBSCAN

# %%
def apply_dbscan(data, eps=0.5, min_samples=5):
	dbscan = DBSCAN(eps=eps, min_samples=min_samples)
	clusters = dbscan.fit_predict(data)
	return clusters

# %%
dbscan_clusters = apply_dbscan(data_scaled)

# %%
score_dbscan = silhouette_score(data_scaled, dbscan_clusters)
print("Silhouette Score for DBSCAN:", score_dbscan)

# %% [markdown]
# ### Mean Shift

# %%
from sklearn.cluster import MeanShift

# %%
def apply_mean_shift(data, bandwidth=None):
	mean_shift = MeanShift(bandwidth=bandwidth)
	clusters = mean_shift.fit_predict(data)
	return clusters

# %%
mean_shift_clusters = apply_mean_shift(data_scaled)

# %% [markdown]
# ### Spectral Clustering

# %%
from sklearn.cluster import SpectralClustering

# %%
def apply_spectral(data, n_clusters=3):
	spectral = SpectralClustering(n_clusters=n_clusters, random_state=0)
	clusters = spectral.fit_predict(data)
	return clusters

# %%
spectral_clusters = apply_spectral(data_scaled)

# %%
score_spectral = silhouette_score(data_scaled, spectral_clusters)
print("Silhouette Score for Spectral Clustering:", score_spectral)

# %% [markdown]
# ### Agglomerative Clustering

# %%
def apply_agglomerative(data, n_clusters=3):
	agglomerative = AgglomerativeClustering(n_clusters=n_clusters)
	clusters = agglomerative.fit_predict(data)
	return clusters

# %%
agglomerative_clusters = apply_agglomerative(data_scaled)

# %%
score_agglomerative = silhouette_score(data_scaled, agglomerative_clusters)
print("Silhouette Score for Agglomerative Clustering:", score_agglomerative)

# %% [markdown]
# ## Evaluate Silhouette Scores

# %%
def evaluate_clustering_algorithms(data, cluster_labels):
	scores = {}
	for algorithm, labels in cluster_labels.items():
		if len(set(labels)) > 1:
			score = silhouette_score(data, labels)
			scores[algorithm] = score
		else:
			scores[algorithm] = None
	return pd.DataFrame(list(scores.items()), columns=['Algorithm', 'Silhouette Score'])

# %%
cluster_labels = {
	'K-Means': kmeans_clusters,
	'Hierarchical': hierarchical_clusters,
	'DBSCAN': dbscan_clusters,
	'Mean Shift': mean_shift_clusters,
	'Spectral': spectral_clusters,
	'Agglomerative': agglomerative_clusters
}

# %%
evaluation_results = evaluate_clustering_algorithms(data_scaled, cluster_labels)
evaluation_results

# %% [markdown]
# ## Etudier le nombre de clusters idémal

# %% [markdown]
# ### K-Means (Elbow Method)

# %%
from sklearn.cluster import KMeans

# %%
def find_optimal_clusters_kmeans(data, max_k):
	sse = []
	for k in range(1, max_k+1):
		kmeans = KMeans(n_clusters=k, random_state=42)
		kmeans.fit(data)
		sse.append(kmeans.inertia_)
	plt.figure(figsize=(10, 6))
	plt.plot(range(1, max_k+1), sse, marker='o')
	plt.xlabel('Number of clusters')
	plt.ylabel('SSE')
	plt.title('The Elbow Method to Determine Optimal Number of Clusters')
	plt.show()

# %%
find_optimal_clusters_kmeans(data_scaled, 10)

# %% [markdown]
# ### Silhouette Score

# %%
from sklearn.metrics import silhouette_score

# %%
def silhouette_analysis(data, max_k):
	silhouette_scores = []
	for k in range(2, max_k+1):
		kmeans = KMeans(n_clusters=k, random_state=42)
		labels = kmeans.fit_predict(data)
		score = silhouette_score(data, labels)
		silhouette_scores.append(score)
	plt.figure(figsize=(10, 6))
	plt.plot(range(2, max_k+1), silhouette_scores, marker='o')
	plt.xlabel('Number of clusters')
	plt.ylabel('Silhouette Score')
	plt.title('Silhouette Analysis For Optimal Number of Clusters')
	plt.show()

# %%
silhouette_analysis(data_scaled, 10)

# %% [markdown]
# ### Hierarchical Clustering (Dendrogram)

# %%
from scipy.cluster.hierarchy import dendrogram, linkage

# %%
def plot_dendrogram(data, method='ward'):
	linked = linkage(data, method=method)
	plt.figure(figsize=(10, 7))
	dendrogram(linked, truncate_mode='lastp', p=12, leaf_rotation=90., leaf_font_size=12.)
	plt.title('Dendrogram for Hierarchical Clustering')
	plt.xlabel('Cluster Size')
	plt.ylabel('Distance')
	plt.show()

# %%
plot_dendrogram(data_scaled)

# %% [markdown]
# ### Mean Shift

# %%
from sklearn.cluster import estimate_bandwidth

# %%
def find_optimal_bandwidth(data):
	bandwidth = estimate_bandwidth(data, quantile=0.2)
	print("Estimated Bandwidth:", bandwidth)
	mean_shift = MeanShift(bandwidth=bandwidth)
	clusters = mean_shift.fit_predict(data)
	return clusters

# %%
mean_shift_clusters = find_optimal_bandwidth(data_scaled)

# %% [markdown]
# ### DBSCAN

# %%
from sklearn.cluster import DBSCAN
from sklearn.metrics import silhouette_score

# %%
def tune_dbscan(data, eps_range, min_samples_range):
	best_score = -1
	best_eps = None
	best_min_samples = None
	for eps in eps_range:
		for min_samples in min_samples_range:
			dbscan = DBSCAN(eps=eps, min_samples=min_samples)
			labels = dbscan.fit_predict(data)
			if len(set(labels)) > 1:
				score = silhouette_score(data, labels)
				if score > best_score:
					best_score = score
					best_eps = eps
					best_min_samples = min_samples
	return best_eps, best_min_samples, best_score

# %%
eps_range = np.arange(0.1, 1.0, 0.1)
min_samples_range = range(2, 10)
best_eps, best_min_samples, best_score = tune_dbscan(data_scaled, eps_range, min_samples_range)
print("Best eps:", best_eps, "Best min_samples:", best_min_samples, "Best Silhouette Score:", best_score)

# %% [markdown]
# ### Spectral Clustering & Agglomerative Clustering

# %%
from sklearn.metrics import silhouette_score

# %%
def find_optimal_clusters_silhouette(data, algorithm_class, max_clusters=10):
	scores = []
	for k in range(2, max_clusters + 1):
		model = algorithm_class(n_clusters=k)
		clusters = model.fit_predict(data)
		score = silhouette_score(data, clusters)
		scores.append(score)
	plt.figure(figsize=(8, 6))
	plt.plot(range(2, max_clusters + 1), scores, marker='o')
	plt.title('Silhouette Score for Optimal Clusters')
	plt.xlabel('Number of clusters')
	plt.ylabel('Silhouette Score')
	plt.show()

# %%
find_optimal_clusters_silhouette(data_scaled, SpectralClustering)

# %%
find_optimal_clusters_silhouette(data_scaled, AgglomerativeClustering)

# %% [markdown]
# ## La qualité de la classification des clusters idéma

# %%



