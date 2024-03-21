
# IDL 10 : Construction d'un HMM pour l'étiquetage morphosyntaxique automatique

## EXO 0 & 1:

Dans le cadre de l'exercice 0 et 1, j'ai construit un modèle de Markov caché (HMM) pour l'étiquetage morphosyntaxique automatique, en utilisant l'algorithme de Viterbi pour trouver la séquence d'étiquettes la plus probable étant donné une séquence de mots.

En complément de l'implémentation décrite ci-dessus, des résultats détaillés et des visualisations des performances de l'algorithme de Viterbi ont été obtenus à partir du notebook `exo_1.ipynb`. Ces résultats supplémentaires ont permis de mieux comprendre le comportement du modèle dans divers scénarios et d'affiner notre compréhension des probabilités de transition et d'émission au sein du HMM.

### Construction du modèle HMM

J'ai commencé par définir la classe `HMM`, qui inclut les probabilités initiales (`initial_prob`), les probabilités de transition (`transition_prob`) et les probabilités d'émission (`emission_prob`). Ces probabilités sont essentielles pour le fonctionnement de l'algorithme de Viterbi.

#### Méthodes implémentées

- `initial` : renvoie la probabilité initiale d'une étiquette, ou 0.0 si l'étiquette n'est pas trouvée.
- `transition` : calcule la probabilité de transition d'une étiquette à une autre, retournant 0.0 pour les transitions inconnues.
- `emission` : fournit la probabilité d'émission d'un mot pour une étiquette donnée, avec une valeur par défaut de 0.0 pour les paires inconnues.

### L'algorithme de Viterbi

#### Calcul des probabilités initiales

À l'aide de la méthode `initials`, j'ai calculé la probabilité de chaque étiquette pour le premier mot d'une phrase, en tenant compte à la fois des probabilités d'émission et des probabilités initiales.

#### Transitions et probabilités

Ensuite, j'ai implémenté `best_transition_to` pour trouver la meilleure transition vers une étiquette donnée, et `best_transitions` pour appliquer cette logique à toutes les étiquettes possibles.

#### Construction de la matrice de Viterbi

Avec `viterbi_matrix`, j'ai construit la matrice de Viterbi, qui contient les informations nécessaires pour retracer la séquence d'étiquettes la plus probable.

#### Reconstruction de la séquence d'étiquettes

Enfin, en utilisant la méthode `viterbi`, j'ai pu reconstruire la séquence d'étiquettes la plus probable pour une séquence de mots donnée, en naviguant de la fin au début de la phrase à l'aide des pointeurs stockés dans la matrice de Viterbi.

### Conclusion

Cette implémentation de l'algorithme de Viterbi pour le HMM s'est avérée être une méthode efficace pour l'étiquetage morphosyntaxique automatique, permettant de déterminer la séquence d'étiquettes la plus probable pour une séquence de mots donnée. Le travail réalisé ouvre des perspectives intéressantes pour l'application de modèles de Markov cachés dans le domaine du traitement automatique des langues.


## EXO 2:

Dans cet exercice, j'ai travaillé avec le corpus Sequoia pour créer un modèle de Markov caché (HMM) à partir de données d'entraînement. L'objectif était d'utiliser ce modèle pour effectuer l'étiquetage morphosyntaxique automatique, en exploitant les statistiques du corpus pour calculer les probabilités initiales, de transition et d'émission.


Le notebook `exo_2.ipynb` fournit une analyse approfondie du processus de construction du HMM à partir du corpus Sequoia, ainsi que des tests de performance après l'intégration du one-count smoothing. Les visualisations et les métriques de performance présentées dans ce notebook ont joué un rôle crucial dans l'évaluation de l'efficacité de notre modèle et de son amélioration grâce au lissage. Les résultats obtenus mettent en évidence l'importance du choix des paramètres et de la méthode de lissage pour optimiser la précision du modèle.

### Préparation des données

J'ai écrit une fonction `lire` pour charger et prétraiter les données du corpus. Cette fonction transforme chaque phrase en une liste de couples mot/étiquette, facilitant ainsi l'utilisation des données pour entraîner le HMM.

### Construction du HMM

À l'aide de la fonction `depuis_corpus`, j'ai calculé les probabilités nécessaires pour le HMM en parcourant le corpus. Cette fonction crée trois dictionnaires : un pour les probabilités initiales de chaque étiquette, un pour les probabilités de transition entre les étiquettes, et un dernier pour les probabilités d'émission des mots étant donné une étiquette.

### Amélioration avec le one-count smoothing

Pour gérer les mots inconnus lors de l'application du modèle sur de nouvelles données, j'ai intégré une heuristique de lissage, appelée "one count smoothing". Cela a permis d'assigner une petite probabilité à l'émission de mots non vus lors de l'entraînement, améliorant significativement la performance du modèle.

### Évaluation du modèle

J'ai évalué le HMM sur un corpus de développement, en calculant l'accuracy, c'est-à-dire le pourcentage de tags correctement prédits par le modèle. Grâce à l'ajustement apporté par le one-count smoothing, le modèle a atteint une accuracy d'environ 93%, démontrant une amélioration notable par rapport à une implémentation sans ce lissage.

### Conclusion

La création d'un HMM à partir d'un jeu d'entraînement et son amélioration avec le one-count smoothing se sont révélées être des étapes cruciales pour l'étiquetage morphosyntaxique automatique. Ces méthodes ont permis d'obtenir un modèle performant et adaptable à de nouvelles données, soulignant l'importance de techniques de lissage dans le traitement des langues naturelles.
