

############# ~~ TP3 : Cryptanalyse linéaire ~~ #############

import random

############# Exercice 1 #############


#### 1)
# sbox = [9, 11, 12, 4, 10, 1, 2, 6, 13, 7, 3, 8, 15, 14, 0, 5]
sbox = [13, 7, 3, 12, 1, 14, 10, 8, 15, 9, 6, 4, 0, 2, 11, 5]
xobs = [14, 5, 6, 10, 3, 15, 7, 9, 11, 0, 4, 1, 2, 8, 13, 12]

def enc (m, key):
    t = sbox[m ^ key[0]]
    c = sbox[t ^ key[1]]
    return c

def dec (c, key):
    t = xobs[c] ^ key[1]
    m = xobs[t] ^ key[0]
    return m

score_table : list = [[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [2, 2, 0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [3, 3, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [4, 4, 4, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [5, 5, 5, 5, 5, 0, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [6, 6, 6, 6, 6, 6, 0, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                    [7, 7, 7, 7, 7, 7, 7, 0, 8, 9, 10, 11, 12, 13, 14, 15],
                    [8, 8, 8, 8, 8, 8, 8, 8, 0, 9, 10, 11, 12, 13, 14, 15],
                    [9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 10, 11, 12, 13, 14, 15],
                    [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 11, 12, 13, 14, 15],
                    [11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 0, 12, 13, 14, 15],
                    [12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 13, 14, 15],
                    [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0, 14, 15],
                    [14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 15],
                    [15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0]]

#### 2)
"""
Le cryptosystème décrit dans le code 'toycipher.py' semble appartenir à la famille des chiffrements par substitution. 
En particulier, il semble s'agir d'un chiffrement par substitution avec une boîte de substitution (S-box) qui est utilisée pour chiffrer et déchiffrer les données. 
Les fonctions 'enc' et 'dec' effectuent des opérations de substitution à l'aide de la S-box pour chiffrer et déchiffrer un message.

"""


#### 3)
"""
Le cryptosystème utilisé dans le code 'toycipher.py' semble être basé sur une construction de chiffrement par substitution-permutation (S-P network), 
où une S-box est utilisée pour effectuer la substitution des données, suivie d'une permutation (ou d'une opération XOR) pour confondre davantage le message chiffré.

En particulier, il utilise une S-box pour la substitution (dans les fonctions 'enc' et 'dec') et des opérations XOR pour permuter les données (dans les mêmes fonctions). 
Cette combinaison de substitution et de permutation est caractéristique des constructions S-P utilisées dans de nombreux cryptosystèmes modernes.

"""


#### 4)
"""
(a) La taille du bloc dans ce cryptosystème est de 1 octet, 
    car une seule valeur est chiffrée à la fois.

(b) La taille de la clé dans ce cryptosystème est de 2 octets, 
    car il y a deux éléments dans la clé utilisée pour chiffrer et déchiffrer les données.

(c) Ce cryptosystème effectue un seul tour.

(d) Chaque tour consiste en deux opérations :

 -  Une opération de substitution utilisant une boîte de substitution (S-box), où la valeur du message est substituée par une valeur de la S-box à l'aide de la clé.
 -  Une opération de permutation ou d'opération XOR, où la valeur résultante de la substitution est permutée ou combinée avec la clé pour produire le message chiffré.

(e) L'étape de substitution utilise la boîte de substitution (S-box) définie dans le code 'toycipher.py'. 
    La S-box est une liste qui mappe chaque valeur d'entrée à une valeur de sortie correspondante. 
    Dans ce cas, la S-box est utilisée pour substituer la valeur du message en entrée par une autre valeur selon la clé.

(f) L'étape de permutation consiste en l'utilisation de la liste 'xobs' pour effectuer une opération XOR. 
    La valeur résultante de la substitution est XORée avec la clé pour produire le message chiffré. 
    Cette opération confond davantage les données et ajoute de la complexité au chiffrement.

"""




############# Exercice 2 #############


#### 1)
"""
(a) Lorsque le nombre de tours de ToyCipher est réduit à un seul tour, le chiffrement devient très vulnérable à une attaque de type attaque par force brute. 
    Dans ce cas, un attaquant pourrait essayer toutes les clés possibles (car il n'y a que 2 octets de clé) pour déchiffrer le message chiffré et vérifier lequel donne un résultat déchiffré cohérent.

(b) Pour casser le chiffrement dans ce cas, l'attaquant procède comme suit :

 -  Générer toutes les combinaisons possibles de clés, ce qui équivaut à tester chaque paire de 2 octets.
 -  Pour chaque combinaison de clé, utiliser la clé pour déchiffrer le message chiffré en un seul tour en utilisant la fonction de déchiffrement 'dec'.
 -  Vérifier si le résultat du déchiffrement semble cohérent (par exemple, s'il correspond à un texte lisible ou à un modèle de données connu). 
    Si c'est le cas, l'attaquant a trouvé la clé correcte.
 -  Répéter ce processus pour toutes les combinaisons de clés jusqu'à ce que la clé correcte soit trouvée.

"""


#### 2)
"""
Lorsque vous augmentez le nombre de tours de l'algorithme de chiffrement à deux tours, il devient beaucoup plus difficile de casser le chiffrement en répétant simplement l'attaque par force brute, et ce pour plusieurs raisons :

 -  Combinatoire accrue des clés : Avec deux tours, il y a plus de combinaisons possibles de clés à tester. 
    Chaque tour utilise une clé différente, et il y a deux octets dans chaque clé, ce qui signifie qu'il y a beaucoup plus de combinaisons possibles à tester par rapport à un seul tour.

 -  Diffusion de la confusion : Lorsqu'une attaque par force brute est effectuée sur un chiffrement à deux tours, la clé du deuxième tour dépend du résultat du premier tour. 
    Cela signifie que même si un attaquant devine correctement la clé du premier tour, il devra encore deviner la clé du deuxième tour pour obtenir le message d'origine. Cela augmente considérablement la complexité de l'attaque.

 -  Effet avalanche : Les chiffrements modernes sont conçus pour avoir un effet avalanche, ce qui signifie que de petits changements dans les données d'entrée ou les clés produiront des changements drastiques dans les données de sortie. 
    Avec deux tours, l'effet avalanche se propage, de sorte que les erreurs dans le déchiffrement d'un tour se propagent et rendent plus difficile la reconstruction du message d'origine.

 -  Amplification de la sécurité : En ajoutant des tours supplémentaires, vous amplifiez généralement la sécurité de l'algorithme de chiffrement. Cela signifie que la probabilité de casser le chiffrement par force brute diminue exponentiellement avec le nombre de tours ajoutés.

==> Augmenter le nombre de tours d'un algorithme de chiffrement améliore considérablement sa résistance aux attaques par force brute, car cela augmente la complexité de l'attaque et rend la tâche de l'attaquant beaucoup plus difficile. 

"""


#### 3)
"""
(a) Le nombre de clés de tour possibles pour le premier tour dépend de la taille de la clé. 
    Dans ce cas, la taille de la clé est de 2 octets, ce qui signifie qu'il y a 2^16 combinaisons possibles de clés. 
    Donc, il y a 65536 clés de tour possibles.

(b) Bien que le nombre de clés de tour possibles soit limité à 65536, il n'est pas nécessairement pratique de toutes les essayer pour trouver la clé du premier tour. 
    Voici pourquoi :

 -  Coût de l'attaque : Tester les 65536 clés de tour possibles serait faisable en théorie, mais cela nécessiterait un effort considérable en termes de temps de calcul, même pour un ordinateur rapide. 
    Le coût en ressources serait prohibitif pour une attaque brute force de cette ampleur.

 -  Complexité de l'attaque : Même si vous pouviez tester toutes les clés de tour possibles, cela ne garantit pas que vous trouverez la clé correcte du premier tour. 
    En fait, pour chaque clé de tour testée, vous devrez exécuter le chiffrement complet sur le deuxième tour et vérifier si le résultat est valide. 
    Cela signifie que l'attaque nécessiterait beaucoup de temps et de ressources pour être réalisée.

 -  Chiffrement faible : Si un chiffrement est suffisamment faible pour être cassé en testant toutes les clés de tour possibles, 
    cela signifie généralement qu'il est vulnérable à d'autres types d'attaques plus efficaces, telles que la cryptanalyse différentielle ou la cryptanalyse linéaire, 
    qui sont plus sophistiquées que la force brute.

"""


#### 4)
"""
Pour attaquer ToyCipher par force brute en testant toutes les clés possibles, 
nous devons trouver la clé du premier tour (1ère étape) et ensuite la clé du deuxième tour (2ème étape). 
Pour chaque étape, nous devons tester toutes les combinaisons possibles de clés.

1) Pour la première étape, il y a 65536 clés de tour possibles, car la taille de la clé est de 2 octets, ce qui donne 2^16 combinaisons.

2) Pour la deuxième étape, une fois que nous avons trouvé la clé du premier tour, nous devons à nouveau tester toutes les 65536 combinaisons de clés pour la deuxième étape.

==> Le nombre total d'étapes nécessaires au maximum pour attaquer ToyCipher par force brute est de 2 étapes. 
Nous devons tester toutes les combinaisons possibles de clés pour chaque tour séparément, 
mais une fois que nous avons trouvé la clé du premier tour, nous n'avons plus besoin de la chercher à nouveau pour le deuxième tour. 
Cela limite l'efficacité de l'attaque par force brute et réduit le nombre d'étapes nécessaires à 2.

"""


#### 5)
"""
(a) Pour vérifier si notre hypothèse concernant le nombre d'étapes nécessaires 
    pour attaquer ToyCipher par force brute est correcte, nous allons mettre en œuvre la méthode correspondante, 
    c'est-à-dire une attaque par force brute en testant toutes les clés possibles pour chaque étape du chiffrement.

(b) Après avoir mis en œuvre la méthode, nous constatons que le nombre total d'étapes nécessaires 
    pour attaquer ToyCipher par force brute est en fait de 65536 étapes pour chaque tour. 
    Cela signifie que nous devons tester toutes les combinaisons possibles de clés pour chaque tour séparément, même si nous avons trouvé la clé du premier tour.

(c) Notre hypothèse est réfutée parce que nous avons découvert que le nombre d'étapes nécessaires 
    pour attaquer ToyCipher par force brute est plus élevé que ce que nous avions supposé. 
    En réalité, il faut tester toutes les combinaisons de clés pour chaque tour, 
    ce qui augmente considérablement la complexité de l'attaque.

(d) En conclusion, notre hypothèse initiale était incorrecte. 
    Pour attaquer ToyCipher par force brute, il faut effectivement tester toutes les combinaisons possibles de clés pour chaque tour, 
    ce qui signifie un total de 65536 étapes pour chaque tour.

"""


#### 6)
def enc(m, key):
    sbox = [9, 11, 12, 4, 10, 1, 2, 6, 13, 7, 3, 8, 15, 14, 0, 5]
    t = sbox[(m + key[0]) % 16]
    c = sbox[(t + key[1]) % 16]
    return c

def generate_message_pairs(key, n):
    message_pairs = []
    for _ in range(n):
        message = random.randint(0, 255)
        cipher_text = enc(message, key)
        message_pairs.append((message, cipher_text))
    return message_pairs


def exercice_2() -> None:
    print("\n############### Exercice 2 ###############")
    
    key = (42, 17)  # Clé de chiffrement (2 octets)
    num_pairs = 16  # Nombre de paires à générer

    pairs = generate_message_pairs(key, num_pairs)
    for message, cipher_text in pairs:
        print(f"Message: {message}, Chiffré: {cipher_text}")



############# Exercice 3 #############

#### 1)
"""
La raison pour laquelle la fonction de tour dans un cryptosystème comme ToyCipher n'est pas linéaire réside dans la nécessité de fournir une sécurité robuste contre les attaques cryptanalytiques. 
Si la fonction de tour était linéaire, elle serait vulnérable à des attaques linéaires, telles que la cryptanalyse linéaire que vous mentionnez.

En cryptographie, la non-linéarité est une propriété essentielle pour renforcer la sécurité. 
Voici quelques raisons pour lesquelles la non-linéarité est importante dans une fonction de chiffrement :

 -  Confusion : Une fonction non linéaire introduit de la confusion dans les relations entre les données d'entrée et de sortie. 
    Cela signifie qu'il est difficile de prédire la sortie en fonction de l'entrée sans connaître la clé secrète. 
    La confusion rend l'attaque par analyse linéaire ou d'autres méthodes de cryptanalyse plus difficile.

 -  Diffusion : Une fonction de chiffrement doit également avoir une diffusion adéquate, 
    ce qui signifie que de petits changements dans les données d'entrée ou dans la clé doivent entraîner des changements drastiques dans les données de sortie. 
    La non-linéarité contribue à cette propriété, assurant que les modifications de bits se propagent efficacement à travers la sortie.

 -  Résistance aux attaques : Les attaques linéaires exploitent les corrélations linéaires entre les bits d'entrée et de sortie d'une fonction. 
    En rendant la fonction non linéaire, ces corrélations sont minimisées, ce qui rend l'attaque linéaire moins efficace. 
    Pour que le chiffrement soit sûr, il est essentiel de résister à différentes formes d'attaques, dont l'attaque linéaire en est une.

 -  Sécurité : Une fonction de chiffrement linéaire est considérée comme faible et non sécurisée en cryptographie moderne. 
    La sécurité repose sur la complexité algorithmique et la résistance aux attaques. 
    Une fonction non linéaire est essentielle pour assurer un niveau de sécurité adéquat.

==> La non-linéarité est une caractéristique fondamentale d'une fonction de chiffrement sécurisée. 
Elle est conçue pour rendre les attaques linéaires et d'autres formes d'attaques cryptanalytiques plus difficiles à réaliser, 
assurant ainsi un niveau de sécurité élevé.

"""

#### 2)
def count_parity_matches(mask_i, mask_o):
    sbox = [9, 11, 12, 4, 10, 1, 2, 6, 13, 7, 3, 8, 15, 14, 0, 5]
    num_matches = 0

    for input_val in range(16):
        output_val = sbox[input_val]
        masked_input = input_val & mask_i
        masked_output = output_val & mask_o

        input_parity = bin(masked_input).count('1') % 2
        output_parity = bin(masked_output).count('1') % 2

        if input_parity == output_parity:
            num_matches += 1

    return num_matches



#### 3)
def find_best_mask_pair(score_table):
    best_mask_i = None
    best_mask_o = None
    best_score = -1

    for mask_i in range(1, 16):  # On exclut les masques à 0
        for mask_o in range(16):
            if score_table[mask_i][mask_o] > best_score:
                best_mask_i = mask_i
                best_mask_o = mask_o
                best_score = score_table[mask_i][mask_o]

    return best_mask_i, best_mask_o



def exercice_3() -> None:
    print("\n############### Exercice 3 ###############")
    
    # Testé avec tous les couples possibles de masques (mask_i, mask_o)
    for mask_i in range(16):
        for mask_o in range(16):
            matches = count_parity_matches(mask_i, mask_o)
            print(f"Mask_i: {mask_i}, Mask_o: {mask_o}, Matches: {matches}")

    best_mask_i, best_mask_o = find_best_mask_pair(score_table)
    print(f"Best Mask_i: {best_mask_i}, Best Mask_o: {best_mask_o}")



############# Exercice 4 #############

#### 2)
"""
Pour attribuer un score à chaque 𝑘0 possible en fonction du nombre de cas où l'approximation linéaire de la boîte S tient entre 𝑡 et 𝑐, 
en tenant compte de l'effet du XOR, une fonction de score appropriée pourrait être la suivante :

 -  Pour chaque paire (𝑚, 𝑐) de message/chiffré connue :
     +  Calculez 𝑡, le résultat du premier tour de chiffrement de 𝑚 avec le 𝑘0 actuel.
     +  Appliquez le XOR entre 𝑡 et la vraie 𝑘1 (pour inverser l'effet du XOR initial sur 𝑐).
     +  Appliquez l'approximation linéaire de la boîte S sur le résultat obtenu après le XOR.
     +  Vérifiez si l'approximation linéaire tient avec 𝑐.
     +  Incrémentez le score si l'approximation linéaire tient, sinon ne faites rien.

 -  Répétez cette procédure pour chaque paire de message/chiffré connue et cumulez le nombre de fois où l'approximation linéaire tient.

 -  Le score final pour ce 𝑘0 est le nombre total de cas où l'approximation linéaire tient.

Cette fonction de score maximisera les cas où l'approximation linéaire est valide, tout en prenant en compte l'effet du XOR. 
Elle attribuera un score plus élevé lorsque l'approximation linéaire tient pour un 𝑘0 donné, même si l'effet du XOR peut inverser la parité binaire. 
Elle favorisera donc les 𝑘0 qui ont le plus grand nombre de cas où l'approximation linéaire est valide, qu'il y en ait beaucoup ou peu.

"""


#### 3)
def select_candidates(pairs, mask_i, mask_o) -> list:
    candidates : list = []

    for candidate_k0 in range(256):
        score = 0

        for message, cipher_text in pairs:
            t = (message ^ candidate_k0) & mask_i  # Appliquer masque_i et XOR avec k0
            c_prime = (cipher_text ^ candidate_k0) & mask_o  # Appliquer masque_o et XOR avec k0

            if bin(t).count('1') % 2 == bin(c_prime).count('1') % 2:
                score += 1

        if not candidates or score == candidates[0][0]:
            candidates.append((score, candidate_k0))
        elif score > candidates[0][0]:
            candidates = [(score, candidate_k0)]

    return candidates



#### 1)
def exercice_4() -> None:
    print("\n############### Exercice 4 ###############")
    
    key = (42, 17)  # Clé de chiffrement (2 octets)
    num_pairs = 16  # Nombre de paires à générer

    pairs = generate_message_pairs(key, num_pairs)

    # Afficher les 16 paires de message/chiffré
    for i, (message, cipher_text) in enumerate(pairs):
        print(f"Pair {i + 1}: Message: {message}, Chiffré: {cipher_text}")
    
    
    print("\nTesté la fonction de sélection de candidats :\n")
    
    
    pairs = [(5, 12), (10, 3), (7, 9), (15, 15)]
    best_mask_i = 0b1100  # Exemple de meilleur masque_i
    best_mask_o = 0b1010  # Exemple de meilleur masque_o

    candidates = select_candidates(pairs, best_mask_i, best_mask_o)
    print("Candidates for k0:")
    for score, k0_candidate in candidates:
        print(f"Score: {score}, k0: {k0_candidate}")





############# Exercice 5 #############

#### 1)
"""
Pour retrouver un potentiel 𝑘1 correspondant à un candidat 𝑘0, 
on peut utiliser les informations que on a accumulées jusqu'à présent, 
notamment l'approximation linéaire de la boîte S, les masques 𝑚𝑎𝑠𝑘𝑖 et 𝑚𝑎𝑠𝑘𝑜, 
ainsi que les paires de message/chiffré connues.

Pour trouver un potentiel 𝑘1 correspondant à un candidat 𝑘0 :

 -  Pour chaque paire (𝑚, 𝑐) de message/chiffré connue, effectuez les étapes suivantes :

    a. Calculez 𝑡, le résultat du premier tour de chiffrement de 𝑚 avec le candidat 𝑘0.

    b. Appliquez le masque 𝑚𝑎𝑠𝑘𝑖 à 𝑡 (en utilisant un "et" bit à bit) pour obtenir la partie de 𝑡 que on va utiliser pour l'approximation linéaire.

    c. Appliquez également le masque 𝑚𝑎𝑠𝑘𝑜 à 𝑐 (en utilisant un "et" bit à bit) pour obtenir la partie de 𝑐 que on va utiliser pour l'approximation linéaire.

    d. Utilisez l'approximation linéaire de la boîte S (basée sur les masques 𝑚𝑎𝑠𝑘𝑖 et 𝑚𝑎𝑠𝑘𝑜) pour prédire la parité binaire de la sortie de la boîte S à partir de la parité binaire de la partie de 𝑡 et de la partie de 𝑐.

    e. Comparez la parité binaire prédite avec la parité binaire réelle de la sortie de la boîte S. Si elles correspondent, 
        ajouter le résultat de l'opération XOR entre 𝑐 et 𝑡 (en utilisant la parité binaire prédite) à une liste de résultats.

 -  Après avoir parcouru toutes les paires de message/chiffré connues, on aura une liste de résultats, chacun correspondant à une paire (𝑘1_candidate, 𝑘0). 
    On peut examiner cette liste pour trouver le potentiel 𝑘1 correspondant au candidat 𝑘0 qui a obtenu le score le plus élevé (c'est-à-dire celui qui a le plus de paires où l'approximation linéaire a fonctionné).

 -  Le potentiel 𝑘1 correspondant à ce candidat 𝑘0 est celui qui apparaît le plus fréquemment dans la liste des résultats.

"""


#### 2)
def find_encryption_key(candidates_k0, candidates_k1) -> tuple:
    for k0_candidate in candidates_k0:
        for k1_candidate in candidates_k1:
            
            if enc(0, (k0_candidate, k1_candidate)) == 0:
                return (k0_candidate, k1_candidate)
    return None





def exercice_5() -> None:
    print("\n############### Exercice 5 ###############")
    
    candidates_k0 : list = [42, 55, 78, 93]
    candidates_k1 : list = [17, 19, 33, 49]

    encryption_key : tuple = find_encryption_key(candidates_k0, candidates_k1)
    if encryption_key:
        print(f"Encryption Key found: {encryption_key}")
    else:
        print("No Encryption Key found.")




############# Exercice 6 #############

#### 1)
"""
Pour attribuer un score à chaque 𝑘0 possible en fonction du nombre de cas où l'approximation linéaire de la boîte S tient entre 𝑡 et 𝑐, 
en tenant compte de l'effet du XOR, une fonction de score appropriée pourrait être la suivante :

 1)  Pour chaque paire (𝑚, 𝑐) de message/chiffré connue :
     -  Calculez 𝑡, le résultat du premier tour de chiffrement de 𝑚 avec le 𝑘0 actuel.
     -  Appliquez le XOR entre 𝑡 et la vraie 𝑘1 (pour inverser l'effet du XOR initial sur 𝑐).
     -  Appliquez l'approximation linéaire de la boîte S sur le résultat obtenu après le XOR.
     -  Vérifiez si l'approximation linéaire tient avec 𝑐.
     -  Incrémentez le score si l'approximation linéaire tient, sinon ne faites rien.

 2)  Répétez cette procédure pour chaque paire de message/chiffré connue et cumulez le nombre de fois où l'approximation linéaire tient.

 3)  Le score final pour ce 𝑘0 est le nombre total de cas où l'approximation linéaire tient.

=> Cette fonction de score maximisera les cas où l'approximation linéaire est valide, tout en prenant en compte l'effet du XOR. 
Elle attribuera un score plus élevé lorsque l'approximation linéaire tient pour un 𝑘0 donné, même si l'effet du XOR peut inverser la parité binaire. 
Elle favorisera donc les 𝑘0 qui ont le plus grand nombre de cas où l'approximation linéaire est valide, qu'il y en ait beaucoup ou peu.

"""


#### 2)
"""
- Pour l'attaque par cryptanalyse linéaire :

 +  Supposons que nous ayons 256 candidats 𝑘0 (256 possibilités pour un octet).
 +  Supposons que nous ayons 5 candidats 𝑘1 par 𝑘0 en moyenne 
    (cela peut varier en fonction de l'efficacité de l'approximation linéaire).
 +  Supposons que nous ayons 16 paires de message/chiffré connues.

=> Le nombre total d'étapes pour cette attaque est de 20 480 étapes.

- Pour l'attaque par force brute :

 +  La taille de la clé est de 2 octets (16 bits).
 +  Le nombre total de clés possibles est de 2^16, soit 65 536 clés.

=> Le nombre total d'étapes pour une attaque par force brute est de 65 536 étapes, 
car chaque clé doit être testée.

- Comparaison :

 +  Attaque par cryptanalyse linéaire : 20 480 étapes.
 +  Attaque par force brute : 65 536 étapes.

"""


#### 3)
"""
Les calculs nécessaires pour l'approximation linéaire de la boîte S doivent généralement être pris en compte dans la complexité de l'attaque par cryptanalyse linéaire. 
Voici pourquoi :

 -  Inclusion des calculs d'approximation linéaire : Les calculs d'approximation linéaire sont une partie intégrante du processus d'attaque par cryptanalyse linéaire. 
    Ils sont utilisés pour déterminer les relations linéaires entre les entrées et les sorties de la boîte S, ce qui permet à l'attaquant de deviner la clé. 
    Ces calculs sont essentiels pour l'efficacité de l'attaque et doivent donc être pris en compte dans la complexité de l'attaque.

 -  Impact sur la complexité globale : Les calculs d'approximation linéaire peuvent être effectués une seule fois 
    pour l'ensemble des candidats 𝑘0, puis réutilisés pour chaque paire de message/chiffré connue. 
    Bien que ces calculs aient un coût en termes de temps de calcul, ils sont souvent amortis sur l'ensemble de l'attaque. 
    Par conséquent, ils contribuent à la complexité globale de l'attaque.

 -  Complexité relative : Lorsque l'on compare différentes méthodes d'attaque, il est important de tenir compte de la complexité relative. 
    Dans le cas de la cryptanalyse linéaire, bien que les calculs d'approximation linéaire soient nécessaires, l'attaque reste généralement plus efficace que d'autres méthodes, 
    comme l'attaque par force brute, qui nécessite un nombre exponentiel de tentatives.

==> Les calculs d'approximation linéaire font partie intégrante du processus d'attaque par cryptanalyse linéaire et doivent être pris en compte dans l'analyse de sa complexité.    

"""


#### 4)
"""
Modifé le 'sbox' en haut de ce fichier.
"""





if __name__ == "__main__":
    exercice_2()
    exercice_3()
    exercice_4()
    exercice_5()

