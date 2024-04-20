from sklearn import datasets
import pandas as pd

wine = datasets.load_wine()

wine_data_structure = {
	"Type": type(wine),
	"Keys": wine.keys(),
	"Feature names": wine.feature_names,
	"Target names": wine.target_names,
	"Number of samples": wine.data.shape[0],
	"Number of features": wine.data.shape[1],
	"Sample data point": wine.data[0],
	"Sample target": wine.target[0]
}

df_wine = pd.DataFrame(data=wine.data, columns=wine.feature_names)
df_wine['target'] = wine.target

wine_data_structure, df_wine.head()
