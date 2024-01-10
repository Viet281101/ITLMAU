# Démarrage projet compiler

### Build & Compiler

- Utiliser dune buile (Attention la version dune dans les fichiers **"dune"** et **"dune-projet"** ) :

```
dune buile main.exe
```

ou

```
ocamlbuild -use-menhir main.byte
```

- Compiler (essayer avec les tests/) en utilisant **main.exe** ou **main.byte**, par exemple avec **"int.test"**:

```
./main.exe tests/int.test
```

puis

```
spim -file result.s
```

### TODO liste

- [x] types de base :
  - [x] entiers,
  - [x] booléens,
  - [x] chaînes de caractères;

- [X] bibliothèque de base :
  - [X] lecture et écriture sur l’entrée et la sortie standard des types de bases,
  - [X] opérateurs logiques de base sur les booléens (et, ou, non),
  - [X] opérateurs arithmétiques de base sur les entiers (addition, soustraction, multiplication, division, modulo);

- [X] expression :
  - [X] valeur,
  - [X] variable,
  - [X] appel de fonction (de la bibliothèque de base ou définie par l’utilisateur·ice);

- [X] instructions :
  - [X] déclaration de variable,
  - [X] assignation de la valeur d’une expression à une variable,
  - [X] renvoie de la valeur d’une expression,
  - [X] branchement conditionnel “si expression alors bloc sinon bloc”,
  - [X] boucle “tant que expression faire bloc”;
  - [X] un bloc est une séquence d’instructions;

- [X] un programme est une liste de définitions de fonctions (dont une s’appelle main) :
  - [X] une fonction déclare son nom, les noms et types de ses arguments, son type de retour, et son corps,
  - [X] le corps d’une fonction est un bloc.
