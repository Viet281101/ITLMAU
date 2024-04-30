# Rattrapage compilation 2023–2024

1- Le projet qui vous est fournit est un interpréteur.
	Décrivez rapidement les différentes étapes de son fonctionnement.
(2 points)


- Analyse lexicale (Lexing) :
	Transforme le code source en une séquence de jetons (tokens) à l'aide du fichier lexer.mll, qui définit les règles pour reconnaître les mots clés, identifiants, littéraux, etc.
- Analyse syntaxique (Parsing) :
	Construit un arbre de syntaxe abstraite (AST) à partir des jetons générés par l'analyse lexicale en utilisant les règles définies dans le fichier `parser.mly`.
- Analyse sémantique :
	Effectuée par le module `semantics.ml`, cette étape vérifie la cohérence et la validité du code en termes de types et de portées des variables. Elle génère une représentation intermédiaire (IR) en vérifiant les types et les contraintes.
- Exécution :
	`IR` est exécutée par le module `Interp`, qui traite les instructions et les expressions, gère l'affectation des variables, évalue les expressions, et traite les appels de fonction.
- Gestion des erreurs et affichage des résultats :
	Les erreurs comme les caractères non reconnus ou les erreurs de syntaxe sont gérées et affichées. Si aucune erreur n'est détectée, les résultats sont formatés et affichés par le module `Printer`.



2- Donnez au format BNF la syntaxe des programmes valides pour cet interpréteur.
(2 points)

Le format BNF la syntaxe des programmes valides pour cet interpréteur est le suivant :
```BNF
<block> ::= <instr> ";" <block> 
			 | "end"

<instr> ::= <ident> "=" <expr>
			 | "return" <expr>

<expr> ::= <int>
			| "-" <int>
			| <ident>
			| <expr> "+" <expr>
			| <expr> "-" <expr>
			| <expr> "*" <expr>
			| <expr> "/" <expr>
			| "(" <expr> ")"
```
- <int> représente un entier, tel que reconnu par le lexer à partir des séquences de chiffres.
- <ident> est un identifiant pour les variables ou les fonctions, reconnaissable par des lettres, des chiffres, des tirets ou des tirets bas, commençant par une lettre.
- Les opérateurs "+", "-", "*", "/" sont utilisés pour les opérations arithmétiques de base.
- Les parenthèses "(" et ")" sont utilisées pour contrôler l'ordre des opérations dans les expressions.


3- Dans le dossier "tests" il n'y a que des tests fonctionnels.
	Ajoutez des tests de gestion des erreurs.
(2 points)


J'ai ajouté des fichiers tests pour gestion des erreurs dans le dossier `tests/` suivant :

- Fichier `tests/8.test`:
return z;

```bash
$ ./main.exe tests/8.test
Error on line 1 col 7: unbound variable 'z'.
```

- Fichier `tests/9.test` :
x = 10 / 0;
return x;

```bash
$ ./main.exe tests/9.test
Fatal error: exception Division_by_zero
```

- Fichier `tests/10.test` :
x = 42;
y = %add(x);
return y;

```bash
$ ./main.exe tests/10.test
Error on line 2 col 4: unrecognized char '%'.
```

- Fichier `tests/11.test` :
x = "bonjour";
y = x * 2;
return y;

```bash
$ ./main.exe tests/11.test
Error on line 1 col 4: unrecognized char '"'.
```

- Fichier `tests/12.test` :
x = 42
return x;

```bash
$ ./main.exe tests/12.test
Error on line 2 col 0: syntax error.
```


4- Ajoutez à cet interpréteur le support du type booléen et des expressions conditionnelles.
(14 points)

	4.1- Ajoutez le support des valeurs booléennes "true" et "false" (sans forcément rajouté de mot clés).

	Tester dans le fichier `tests/13.test` et `tests/14.test` les valeurs booléennes `true` et `false`.


	4.2- Ajoutez au moins l'opérateur de comparaison "==" dans la baselib de sorte à ce que le tests 7 fonctionne.



	4.3- Dans l'analyse sémantique vérifiez que le type de l'expression utilisée comme condition est bien booléen, ainsi que les deux branches de l'expression conditionnelle renvoie une valeur du même type.



	4.4- Ajoutez des fichiers de tests fonctionnels et de gestion des erreurs pour faire la démo de votre implémentation.




Pour info cela peut être fait proprement en ajoutant entre quarante et cinquante de lignes de code au projet en tout (en touchant à l'ensemble des fichiers), sans compter les tests.
