# Rapport de Développement Logiciels Libres


## Informations générales

| **Nom du projet** | Compte GitHub | Propriétaire du projet | Pull Request | Resolve l'issue |  Objectif |
| --- | --- | --- | --- | --- | --- |
| [Pixel Paint](https://github.com/Kully/pixel-paint) | [Viet281101](https://github.com/Viet281101), [Raphaelmos](https://github.com/Raphaelmos) | [Kully](https://github.com/Kully) | [Fix the line draw choppy on fast mouse movements issue #20](https://github.com/Kully/pixel-paint/pull/20) | [Line is drawn choppy on fast mouse movements #8](https://github.com/Kully/pixel-paint/issues/8) | Améliorer la fluidité du tracé des lignes avec une souris en déplacement rapide. |


## Description détaillée

### Problème

- **Symptôme**: Les lignes tracées sont saccadées lorsque la souris se déplace rapidement.
- **Cause**: L'algorithme actuel de dessin n'est pas optimisé pour les mouvements rapides de la souris.

### Solution

1. **Algorithme de Bresenham**:
	- **Raison du choix**: L'algorithme de Bresenham est particulièrement adapté pour le tracé de lignes droites dans les graphiques raster. Contrairement à la régression linéaire ou d'autres méthodes, il est rapide, efficace et n'implique pas de calculs en virgule flottante, ce qui le rend parfait pour une application en temps réel dans un contexte de dessin pixelisé.
	- **Mise en œuvre**: L'algorithme de Bresenham a été implémenté pour améliorer la fluidité du tracé en gérant les déplacements rapides de la souris.
	- Cet algorithme permet de tracer des lignes plus précises, réduisant les saccades lors des mouvements rapides de la souris.

2. **Réorganisation du code**:
	- Séparation des fonctions de gestion des événements (EventHandlers) dans un fichier distinct.
	- Optimisation de la structure du code pour faciliter la maintenance et l'extension futures.

### Processus de réalisation

1. **Analyse du problème**:
	- Étude du phénomène de saccades lors du tracé avec des mouvements rapides de la souris.
	- Recherche et compréhension de l'algorithme de Bresenham pour son application au projet.

2. **Amélioration du code**:
	- Réécriture du code de tracé des lignes en utilisant l'algorithme de Bresenham.
	- Réorganisation des fonctions de gestion des événements dans un fichier dédié pour améliorer la clarté et la gestion du code.

3. **Tests et évaluation**:
	- Tests des outils de crayon et de gomme pour assurer leur bon fonctionnement avec les modifications.
	- Évaluation des performances et de la fluidité du tracé après l'application du nouvel algorithme.

### Problèmes supplémentaires résolus

1. Tracé interrompu à la sortie rapide de la zone de dessin:
	- Utilisation de l'algorithme de Bresenham pour relier le point final du tracé à la bordure du canvas.

2. Tracé interrompu à la réentrée rapide dans la zone de dessin:
	- Suivi des événements de la souris et calcul du vecteur de déplacement pour déterminer le point d'entrée (`entryPoint`) et le relier au point cible (`targetPoint`) avec Bresenham.

3. Problème de tracé aux coins du canvas:
	- Ajustement des calculs de vecteur pour s'assurer que les points aux coins (0 ou 31) soient corrects, évitant ainsi les erreurs de tracé.

4. Corrections de syntaxe et optimisation du code:
	- Ajustements selon les commentaires de `Kully`: conversion des tabulations en espaces, renommage des fonctions, ajout de `JSDoc` pour l'algorithme de Bresenham.
	- Nettoyage du code, suppression des commentaires inutiles, et correction des erreurs dues aux nouvelles implémentations dans eventHandlers.js.

### Interaction et feedback

- **Feedback de `Kully`**:
	- Remarques sur l'amélioration de la fluidité du tracé.
	- Suggestions d'ajustements mineurs pour optimiser davantage le code.
- **Réponses et actions**:
	- Remerciements pour les retours et conseils.
	- Ajustements selon les suggestions de `Kully` et mise à jour de la Pull Request.

### Résultats

- **Tracé plus fluide**: L'algorithme de Bresenham améliore considérablement l'expérience de dessin lors des mouvements rapides de la souris.
- **Code plus propre**: La réorganisation des fonctions de gestion des événements rend le code plus facile à gérer et à étendre.

## Conclusion

Cette Pull Request a résolu efficacement le problème de saccades lors du tracé rapide, tout en améliorant la structure du code du projet Pixel Paint. Les modifications apportées améliorent non seulement l'expérience utilisateur, mais facilitent également la maintenance et le développement futur du projet. Le Pull Request a été fusionné et l'issue #8 a été fermée.