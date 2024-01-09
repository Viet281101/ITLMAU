# Démarrage projet compiler

### Build & Compiler:
 - Utiliser dune buile :

```
dune buile main.exe
```

- Compiler (essayer avec les tests/), par exemple avec __"int.test"__:

```
./main.exe tests/int.test
```

puis

```
spim -file result.asm
```


### TODO liste: 
- [x] types de base :
	- [x] entiers,
	- [x] booléens,
	- [x] chaînes de caractères;

- [ ] bibliothèque de base :
	- [ ] lecture et écriture sur l’entrée et la sortie standard des types de bases,
	- [ ] opérateurs logiques de base sur les booléens (et, ou, non),
	- [ ] opérateurs arithmétiques de base sur les entiers (addition, soustraction, multiplication, division, modulo);

- [ ] expression :
	- [ ] valeur,
	- [ ] variable,
	- [ ] appel de fonction (de la bibliothèque de base ou définie par l’utilisateur·ice);

- [ ] instructions :
	- [ ] déclaration de variable,
	- [ ] assignation de la valeur d’une expression à une variable,
	- [ ] renvoie de la valeur d’une expression,
	- [ ] branchement conditionnel “si expression alors bloc sinon bloc”,
	- [ ] boucle “tant que expression faire bloc”;
	- [ ] un bloc est une séquence d’instructions;

- [ ] un programme est une liste de définitions de fonctions (dont une s’appelle main) :
	- [ ] une fonction déclare son nom, les noms et types de ses arguments, son type de retour, et son corps,
	- [ ] le corps d’une fonction est un bloc.


