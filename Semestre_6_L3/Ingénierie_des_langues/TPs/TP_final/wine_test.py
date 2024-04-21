
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn import datasets


wine = datasets.load_wine()
df_wine = pd.DataFrame(data=wine.data, columns=wine.feature_names)
df_wine['target'] = wine.target


print("Description statistique de base des caractéristiques :")
print(df_wine.describe())

fig, axs = plt.subplots(nrows=4, ncols=4, figsize=(20, 15))
fig.subplots_adjust(hspace=0.5, wspace=0.5)
axs = axs.flatten()

for i, col in enumerate(df_wine.columns[:-1]):
	sns.histplot(df_wine[col], kde=True, ax=axs[i])
	axs[i].set_title(f'Distribution de {col}')
	axs[i].set_ylabel('Nombre')
	axs[i].set_xlabel('Valeur')

plt.figure(figsize=(12, 6))
sns.boxplot(data=df_wine.drop(columns=['target']), orient='h')
plt.title('Boîte à moustaches des caractéristiques')
plt.show()



