import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets as ds

# On va ici utiliser des fonctions de la librairie NumPy
# (www.numpy.org) pour générer aléatoirement des données, autour d'un
# centre. Il s'agit de données générées à partir d'une distribution
# normale, soit d'une gaussienne. Les paramètres fournis à la fonction
# sont le centre, c'est à dire le point autour duquel les autres
# seront répartis, soit la moyenne de la gaussienne ; la covariance :
# la matrice diagonale d'étalement des éléments ; ainsi que le nombre
# de points à générer. Si on veut enlever des clusters, on peut
# commenter, si on veut en ajouter, on peut copier-coller (en faisant
# attention aux centres):
# C1 ---------->
centre1=np.array([3,3])            # centre du premier cluster
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

# données circulaires
donnees=np.concatenate((cluster1, cluster2, cluster3, cluster4))

# données non circulaires : le nombre d'exemple est fixé, ainsi que la
# graîne d'aléas, histoire que les données générées restent les mêmes
nb_ex = 500
seed = 10
bruit = 0.05
# cercles concentriques (ignorer cercles_classe, sauf si on veut
# tester le taux de classif), les données sont dans cercles
cercles, cercles_classe = ds.make_circles(n_samples=nb_ex, factor=0.5, noise=bruit, random_state=seed)
# demi-lunes imbriquées (ignorer lunes_classe, sauf si on veut
# tester le taux de classif), les données sont dans lunes
lunes, lunes_classe = ds.make_moons(n_samples=nb_ex, noise=bruit, random_state=seed)

