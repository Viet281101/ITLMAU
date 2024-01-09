

# Projet d'Algorithmique et structures de données 1 -- Sudoku 

**Nom et group: Viet NGUYEN L2-A 20006303**

### Sujet:
- Implanter un résolveur de sudoku (9x9)  
- Eventuellement un générateur de grille de sudoku incomplète, 
valide (une unique solution) et essayer d'améliorer votre générateur de façon qu'il puisse 
potentiellement générer n'importe quelle grille (9x9) valide et incomplète. 


#### Compiler et exécuter le programme:

- Entrez cette commande sur votre Terminal:
```
$ make
```

- Pour exécuter le programme:
```
$ make run
```

- Pour rafraichir le progromme après make:
```
$ make clean
```


#### Les fonctions/aspects du projet:
- Mon idée était d'utiliser une forme de sudoku tabulaire 9x9 préexistante et puis trier ou mélanger l'ordre à l'intérieur pour générer une grille aléatoire.
- Cependant, ce programme ne convient qu'aux tailles de carte 9x9 et ne peut pas etre redimensionné, sauf s'il faut réécrire exempleTab[][] dans le code.

