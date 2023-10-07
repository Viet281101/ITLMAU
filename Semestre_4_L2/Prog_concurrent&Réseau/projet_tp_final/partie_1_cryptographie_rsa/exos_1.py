

import random


################################# Exercice 1 : #################################

#### 1) Écrire une fonction Python qui permet de vérifier qu'un nombre passé en paramètre est un nombre premier en testant les divisions successives de ce nombre par tous les nombres de 2 à sa racine
def est_premier(n : int) -> bool :
    """ 
    Vérifier si un nombre est premier 
    """
    if n <= 1: return False
    elif n <= 3: return True
    elif n % 2 == 0 or n % 3 == 0: return False
    else: 
        i : int = 5
        while (i * i) <= n:
            if n % i == 0 or n % (i + 2) == 0: return False
            i += 6
        return True
    


#### 2) Écrire une fonction Python qui permet de générer un nombre premier aléatoire supérieur à une borne passée en paramètre.
def genere_premier_superieur(borne : int) -> int:
    """
    Génère un nombre premier aléatoire supérieur à la borne passée en paramètre.
    """
    nombre : int = random.randint(borne+1, 2*borne)
    while not est_premier(nombre):
        nombre += 1
    return nombre



#### 3) Écrire une fonction qui permet de calculer l'inverse modulaire d'un nombre passé en paramètre.
def inverse_mod(a : int, n : int) -> int:
    # Initialisation de l'algorithme d'Euclide étendu
    r, r_prev = n, a
    s, s_prev = 0, 1
    while r != 0:
        # Calcul du quotient et du reste
        q = r_prev // r
        r_prev, r = r, r_prev - q * r
        s_prev, s = s, s_prev - q * s
    # Si le pgcd de a et n n'est pas 1, l'inverse n'existe pas
    if r_prev != 1:
        return None
    # Sinon, on renvoie l'inverse modulaire
    return (s_prev % n)



#### 5) Écrire une fonction chiffrer_rsa() qui prend en paramètre un entier n, et qui renvoie la valeur chiffrée à l'aide de la clé (d, n). 
def chiffrer_rsa(n : int, d : int, n_publique : int) -> int :
    return pow(n, d, n_publique)




#### 6) 
# Écrire une fonction dechiffrer_rsa qui prend en paramètre un entier m, qui calcule
# la partie privée de la clé (ce qui est difficile en général mais faisable dès lors que les
# nombres premiers ne sont pas trop grands), puis qui puis qui déchiffre le message m
# à l'aide de la clé privée.
def exp_rapide_modulaire(base : int, exposant : int, modulo : int) -> int:
    """
    Calcul de l'exponentiation rapide modulaire.
    """
    res : int = 1
    while exposant > 0:
        if exposant % 2 == 1:
            res = (res * base) % modulo
        base = (base * base) % modulo
        exposant //= 2
    return res

def dechiffrer_rsa(m : int, d : int, n : int) -> int:
    # Calcul de la clé privée (e, n)
    p : int = 3
    q : int = n // p
    phi_n : int = (p - 1) * (q - 1)
    e : int = inverse_mod(d, phi_n)
    # Déchiffrement du message m
    return exp_rapide_modulaire(m, e, n)





def main() -> None:
    ### Afficher est_premier() fonction :
    print("7 est un nombre premier : ", est_premier(7))
    
    #### 4) Générer deux nombres premiers aléatoires p et q, et stocker la partie n de la clé publique. Fixer une variable globale d contenant l'autre partie de la clé publique.
    p : int = genere_premier_superieur(100000)
    q : int = genere_premier_superieur(100000)
    
    ### Calculer la partie n de la clé publique
    n : int = p * q

    ### Fixer la variable globale d
    d : int = 65537
    
    print("p = ", p)
    print("q = ", q)
    print("n = ", n)
    print("d = ", d)
    
    
    m : int = 13
    message_dechiffre : int = dechiffrer_rsa(m, 3, 33)
    message_chiffre : int = chiffrer_rsa(m, 3, 33)
    
    print("La message dechiffré correspond à la note 13 : ", message_dechiffre)
    
    #### 7) Quel message chiffré correspond à la note 13 ?
    print("La message chiffré correspond à la note 13 : ", message_chiffre)
    
    
    #### 8) Vériffier que la clé privée de déchiffrement est 7.
    # --> il faut calculer l'inverse modulaire de 3 modulo 20 :
    print(inverse_mod(3, 20))
    
    
    #### 9) Si S reçoit le message chiffré "9", à quelle note cela correspond ?
    print("Si S reçoit le message chiffré '9' -> la note correspond : ", dechiffrer_rsa(9, 3, 33))


    #### 10) Supposons désormais que la clé publique de chiffrement soit (c = 3, n = 55). Quelle est alors la clé privée de déchiffrement ?
    print(inverse_mod(3, 55), f"Donc la clé privée de déchiffrement est (d = {inverse_mod(3, 55)}, n = 55)")



if __name__ == '__main__':
    main()


