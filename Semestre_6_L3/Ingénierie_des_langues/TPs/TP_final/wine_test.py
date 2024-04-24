# IDL TP Final `scikit-learn` Wine dataset testing

import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import cross_val_score

import pandas as pd
import polars as pl
import seaborn as sns

def load_data() -> pd.DataFrame:
	"""Load wine dataset and return data as a pandas DataFrame."""
	wine = datasets.load_wine()
	df_wine = pd.DataFrame(data=wine.data, columns=wine.feature_names)
	df_wine['target'] = wine.target.astype(str)
	return df_wine

def describe_data(df: pd.DataFrame) -> None:
	"""Print basic statistical information about the data."""
	print("Description statistique de base des caractéristiques :")
	print(df.describe())

def visualize_data(df: pd.DataFrame) -> None:
	"""Create a histogram plot for each feature in the data."""
	fig, axs = plt.subplots(nrows=4, ncols=4, figsize=(20, 15))
	fig.subplots_adjust(hspace=0.5, wspace=0.5)
	axs = axs.flatten()

	for i, col in enumerate(df.columns[:-1]):
		sns.histplot(df[col], kde=True, ax=axs[i])
		axs[i].set_title(f'Distribution de {col}')
		axs[i].set_ylabel('Nombre')
		axs[i].set_xlabel('Valeur')

def boxplot(df: pd.DataFrame) -> None:
	"""Create a boxplot of the data."""
	plt.figure(figsize=(12, 6))
	sns.boxplot(data=df.drop(columns=['target']), orient='h')
	plt.title('Boîte à moustaches des caractéristiques')
	plt.show()

def standardize_data(df: pd.DataFrame) -> tuple:
	"""Standardize the data using the StandardScaler."""
	X = df.drop(columns=['target']).values
	y = df['target'].values
	scaler = StandardScaler()
	X_scaled = scaler.fit_transform(X)
	return X_scaled, y

def train_test_split_data(X: pd.DataFrame, y: pd.DataFrame, test_size=0.3, random_state=42) -> tuple:
	"""Split the data into training and test sets."""
	X_train, X_test, y_train, y_test = train_test_split(
		X, y, test_size=test_size, random_state=random_state, stratify=y)
	return X_train, X_test, y_train, y_test

def train_model(X_train: pd.DataFrame, y_train: pd.DataFrame) -> LinearSVC:
	"""Train a LinearSVC model on the training data."""
	clf = LinearSVC(dual=True)
	clf.fit(X_train, y_train)
	return clf

def evaluate_model(clf: LinearSVC, X_test: pd.DataFrame, y_test: pd.DataFrame) -> tuple:
	"""Evaluate the trained model on the test data."""
	y_pred = clf.predict(X_test)
	accuracy = accuracy_score(y_test, y_pred)
	conf_matrix = confusion_matrix(y_test, y_pred)
	class_report = classification_report(y_test, y_pred)
	print(f"Taux d'exactitude du modèle : {accuracy}")
	print("Matrice de confusion :")
	print(conf_matrix)
	print("Rapport de classification :")
	print(class_report)
	return accuracy, conf_matrix, class_report

def gridsearch_model(X_train: pd.DataFrame, y_train: pd.DataFrame) -> GridSearchCV:
	"""Perform a grid search to find the best parameters for the model."""
	model = LinearSVC(dual=False, random_state=42)
	param_grid = {
		'C': [0.1, 1, 10, 100],
		'loss': ['hinge', 'squared_hinge']
	}
	grid_search = GridSearchCV(model, param_grid, cv=5, scoring='accuracy', verbose=3, n_jobs=-1)
	grid_search.fit(X_train, y_train)
	return grid_search

def cross_validate_model(model, X, y, cv=5):
	"""Perform cross-validation on a given model."""
	scores = cross_val_score(model, X, y, cv=cv, scoring='accuracy')
	print(f"Cross-validation scores: {scores}")
	print(f"Average cross-validation score: {scores.mean():.3f}")
	return scores

def main() -> None:
	"""Main function."""
	df = load_data()
	# describe_data(df)
	# visualize_data(df)
	# boxplot(df)
	X, y = standardize_data(df)
	X_train, X_test, y_train, y_test = train_test_split_data(X, y)

	clf = train_model(X_train, y_train)
	accuracy, conf_matrix, class_report = evaluate_model(clf, X_test, y_test)
	print(f"Score du modèle sur le jeu de tests : {clf.score(X_test, y_test):.3f}")

	## Grid search to find the best parameters
	grid_search = gridsearch_model(X_train, y_train)
	print("Meilleur score :", grid_search.best_score_)
	print("Meilleurs paramètres :", grid_search.best_params_)
	best_model = grid_search.best_estimator_
	print("Score du modèle avec les meilleurs paramètres :", best_model.score(X_test, y_test))

	## Cross-validation
	cross_validate_model(best_model, X, y, cv=10)


if __name__ == '__main__':
	main()


