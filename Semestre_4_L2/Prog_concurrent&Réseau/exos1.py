

import time


################################### Exercice 1: ##############################
### 1) Définir une fonction pgcd qui prend en paramètres deux entiers a et b et renvoie leur PGCD.
def euclide_itera(a : int, b : int) -> int:
    while( b != 0):
        temp = b
        b = a % b
        a = temp
    return a
  
def euclide_origin(a : int, b : int) -> int:
    while( a != b):
        if a > b: 
            a -= b
        else: 
            b -= a
    return a

def euclide_rec(a : int, b : int) -> int:
    if b == 0:
        return a
    else: 
        return euclide_rec(b, (a%b))

### 2) Définir une fonction est_premier qui prend en paramètre deux entiers a et b, et qui renvoie 1 si a et b sont premiers entre eux, 0 sinon.
def est_premier(a : int, b : int) -> int:
    for i in range(a, b):
        if (i%i) == 0:
            return 0
    return 1

### 3) Définir une fonction indic_euler1 qui prend en paramètre un entier n, et qui renvoie la valeur de φ(n), en considérant que c'est le nombre d'entiers inférieurs à n premiers avec n.
def indic_euler1(n : int) -> int:
    pass




################################### Exercice 2: ##############################
### 1) Écrire une fonction decomp_prem qui afiche la décomp osition en facteurs premiers sous la forme d'une liste de couples (pi, ai)
def decomp_prem(n : int) -> list:
    pass

### 2) Définir une fonction récursive indic_euler2 qui prend en paramètre un entier n, et qui renvoie la valeur de φ(n)
def indic_euler2(n : int):
    pass



################################### Exercice 3: ##############################
'''
Définir une fonction puissance_mod qui prend en paramètres un entier a, un entier k
et un entier n, et qui calcule la quantité a^k[n] par une fonction itérative naïve (dans une
b oucle, on multiplie par a à chaque passage).
'''
def puissance_mod(a : int, k : int, n : int):
    pass



################################### Exercice 4: ##############################
### 1) Définir une fonction expo_rapide qui prend en paramètres un entier a, un entier k et un entier n, et qui calcule la quantité a^k[n] par l'algorithme d'exp onentiation rapide récursif.
def expo_rapide(a : int, k : int, n : int):
    pass


### 2) Comparer les résultats obtenus avec l'instruction pow(a,k,n) de Python.


### 3) Comparer l'efficacité des fonctions puissance_mod et expo_rapide en temps d'exécution pour calculer des puissances modulaires de plusieurs très grands entiers.






def main() -> None:
    pass



if __name__ == '__main__':
    main()


