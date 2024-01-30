
import numpy as np

def distance_euclidienne(x, y) -> float:
	return np.sqrt(np.sum((x - y)**2))


def distance_manhattan(x, y) -> float:
	return np.sum(np.abs(x - y))


def distance_chebyshev(x, y) -> float:
	return np.max(np.abs(x - y))


def distance_minkowski(x, y, p) -> float:
	return np.sum(np.abs(x - y)**p)**(1/p)


def distance_cosinus(x, y) -> float:
	return np.dot(x, y) / (np.linalg.norm(x) * np.linalg.norm(y))


def distance_correlation(x, y) -> float:
	return 1 - np.dot(x, y) / (np.linalg.norm(x) * np.linalg.norm(y))


def distance_hamming(x, y) -> float:
	return np.count_nonzero(x != y)


def distance_jaccard(x, y) -> float:
	return 1 - np.count_nonzero(x == y) / np.count_nonzero(x | y)


def distance_pearson(x, y) -> float:
	return 1 - np.corrcoef(x, y)[0, 1]


def distance_spearman(x, y) -> float:
	return 1 - np.corrcoef(x, y, rank=True)[0, 1]


def distance_kendall(x, y) -> float:
	return 1 - np.corrcoef(x, y, rank=True)[0, 1]


def distance_hellinger(x, y) -> float:
	return np.sqrt(np.sum((np.sqrt(x) - np.sqrt(y))**2)) / np.sqrt(2)


def distance_bhattacharyya(x, y) -> float:
	return -np.log(np.sum(np.sqrt(x * y))) / np.log(2)


def distance_kullback_leibler(x, y) -> float:
	return np.sum(x * np.log(x / y)) / np.log(2)


def distance_jensen_shannon(x, y) -> float:
	return np.sqrt(distance_kullback_leibler(x, y) / 2 + distance_kullback_leibler(y, x) / 2)