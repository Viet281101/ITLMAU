
# ACH : hiérarchiser la connaissance

Le but de ce TP est de programmer (toujours en python) l’algorithme de clustering hiérarchique ascendant. Les principes en sont rappelés dans les transparents joints. Il faut implémenter les quatre méthodes de linkage (i.e. comparaison de clusters) et prévoir une méthode de visualisation du dendrogramme. De la même manière, une méthode de visualisation des clusters, après la sélection d'un niveau de coupe est à prévoir, ainsi que les méthodes SSE et silhouette vues précédemment. Pour ce qui concerne la structure du dendrogramme, vous pouvez vous inspirer de ceci : https://pro.arcgis.com/fr/pro-app/latest/tool-reference/spatial-analyst/how-dendrogram-works.htm.

En application, comme la fois précédente, on commencera par les iris, en calculant SSE et silhouette pour toutes les coupures, et on finira par les clusters normaux, en en faisant varier le nombre et en appliquant les mêmes calculs.
