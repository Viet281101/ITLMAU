
############# ~~ TP2 : RSA ~~ #############

import random
import math
import hashlib
from Crypto.Util import number

############# Exercice 1 #############


#### 1)
def is_prime(num) -> bool:
    if num <= 1:
        return False
    if num <= 3:
        return True
    if num % 2 == 0 or num % 3 == 0:
        return False
    i = 5
    while i * i <= num:
        if num % i == 0 or num % (i + 2) == 0:
            return False
        i += 6
    return True

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    if x1 < 0:
        x1 += m0
    return x1


def gen_rsa_keypair(keysize) -> tuple:
    if keysize < 64:
        raise ValueError("La taille de la clé doit être d'au moins 64 bits.")

    while True:
        p = random.getrandbits(keysize // 2)
        if p % 2 != 0 and is_prime(p):
            break

    while True:
        q = random.getrandbits(keysize // 2)
        if q % 2 != 0 and is_prime(q) and q != p:
            break

    n = p * q

    phi_n = (p - 1) * (q - 1)

    while True:
        e = random.randint(2, phi_n - 1)
        if gcd(e, phi_n) == 1:
            break

    d = mod_inverse(e, phi_n)

    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key



#### 2)
"""
La taille de la clé RSA est en effet la taille du module (n), 
qui est le produit de p et q. 
Par conséquent, si la taille de la clé demandée est "bits", 
alors chaque nombre premier aléatoire p et q devrait avoir une taille d'environ bits / 2 bits, 
car bits est la taille totale du module.

Donc, pour générer les nombres premiers aléatoires p et q en fonction de la taille de la clé (bits), 
on doit les générer avec une taille d'environ bits / 2 bits chacun. 
Par exemple, si je veux une clé RSA de 2048 bits, 
je dois générer p et q avec une taille d'environ 1024 bits chacun.
"""



#### 3)
def gen_rsa_keypair(keysize) -> tuple:
    # Génération des nombres premiers p et q avec la bibliothèque Crypto
    p = number.getPrime(keysize // 2)
    q = number.getPrime(keysize // 2)

    n = p * q

    # Calcul de l'indicatrice d'Euler de n (φ(n))
    phi_n = (p - 1) * (q - 1)

    while True:
        e = random.randint(2, phi_n - 1)
        if gcd(e, phi_n) == 1:
            break

    d = mod_inverse(e, phi_n)

    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key


#### 4)
"""
Les conditions nécessaires pour choisir un exposant de chiffrement e sont les suivantes :

1)    e doit être un nombre entier positif.
2)    e doit être strictement supérieur à 1 (e > 1).
3)    e doit être strictement inférieur à l'indicatrice d'Euler de n (φ(n)). 
    Cela garantit que l'exposant de chiffrement est inférieur à φ(n), 
    ce qui est essentiel pour le chiffrement RSA.
4)    e et φ(n) doivent être premiers entre eux (c'est-à-dire que leur plus grand commun diviseur doit être égal à 1). 
    Cette condition garantit que l'exposant de chiffrement e a un inverse modulaire dans l'anneau modulo φ(n).

La valeur typique de 65537 est choisie parce qu'elle satisfait toutes ces conditions 
et présente des avantages en termes de performance lors de l'opération de chiffrement, 
car elle a une représentation binaire simple avec de nombreux bits 1 (ce qui est efficace pour les opérations modulo). 
Elle est également sûre car elle est supérieure à 1 et inférieure à φ(n) dans la plupart des cas.
"""


#### 5)
def gen_rsa_keypair(keysize) -> tuple:
    p = number.getPrime(keysize // 2)
    q = number.getPrime(keysize // 2)

    n = p * q

    phi_n = (p - 1) * (q - 1)

    while True:
        e = random.randint(2, phi_n - 1)
        
        if gcd(e, phi_n) == 1 and e > 1:
            break

    d = mod_inverse(e, phi_n)

    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key


#### 6)
"""
Pour calculer d, on utilise l'algorithme de l'inverse modulaire avec la formule suivante :

d = e^-1 mod φ(n)

où :
e est l'exposant de chiffrement.
φ(n) est l'indicatrice d'Euler de n.

Et pour calculer l'inverse modulaire, on peut utiliser l'algorithme d'Euclide étendu.
Cet algo nous donne la valeur de d telle que (d * e) % φ(n) = 1.

Exemple code dans la fonction mod_inverse.
"""



#### 7) et 8)
def gen_rsa_keypair(keysize) -> tuple:
    p = number.getPrime(keysize // 2)
    q = number.getPrime(keysize // 2)

    n = p * q

    phi_n = (p - 1) * (q - 1)

    while True:
        e = random.randint(2, phi_n - 1)
        
        if gcd(e, phi_n) == 1 and e > 1:
            break

    d = number.inverse(e, phi_n) ## ou d = mod_inverse(e, phi_n)

    public_key = (n, e)
    private_key = (n, d)

    return public_key, private_key



def exercice_1():
    print("\n############# Exercice 1 #############")
    
    keysize = 128  # Taille de la clé en bits
    public_key, private_key = gen_rsa_keypair(keysize)
    
    print("Clé publique (n, e):", public_key)
    print("Clé privée (n, d):", private_key)
    
    
    # Exemple d'utilisation pour calculer d
    e = 65537  # Exposant de chiffrement (clé publique)
    phi_n = 123456789  # Indicatrice d'Euler de n
    d = mod_inverse(e, phi_n)
    print("Exposant de déchiffrement d:", d)




############# Exercice 2 #############

#### 1)
"""
(a) Pour chiffrer un message à destination d'Alice, 
    Bob doit utiliser la clé publique d'Alice (Ap). 
    La clé publique (Ap) est utilisée pour le chiffrement car elle est connue de tous et permet à n'importe qui 
    de chiffrer un message qui ne pourra être déchiffré que par la clé privée correspondante (As) d'Alice.

(b) Pour déchiffrer un message qui lui est adressé, 
    Alice doit utiliser sa clé privée (As). 
    La clé privée (As) est gardée secrète par Alice et est utilisée pour le déchiffrement des messages chiffrés à l'aide de sa clé publique (Ap). 
    Seule Alice, en possession de sa clé privée, peut déchiffrer ces messages avec succès.
    
==> Bob utilise la clé publique d'Alice pour chiffrer un message destiné à Alice, 
    et Alice utilise sa clé privée pour déchiffrer ce message.

"""


#### 2)
"""
Chacune des opérations décrites à la question précédente consiste en une opération mathématique spécifique dans le contexte du chiffrement RSA

"""




#### 3)
def rsa(message, key) -> int:
    exponent, modulus = key
    result = pow(message, exponent, modulus)
    return result




#### 5)
def rsa_enc(plaintext, public_key) -> int:
    message = int.from_bytes(plaintext.encode('utf-8'), 'big')

    ciphertext = rsa(message, public_key)
    return ciphertext

def rsa_dec(ciphertext, private_key) -> str:
    message = rsa(ciphertext, private_key)
    
    plaintext = message.to_bytes((message.bit_length() + 7) // 8, 'big').decode('utf-8')
    return plaintext



#### 6)
def gen_rsa_keypair(keysize) -> tuple:
    p = number.getPrime(keysize // 2)
    q = number.getPrime(keysize // 2)
    n = p * q
    phi_n = (p - 1) * (q - 1)
    e = 65537  # Exposant de chiffrement couramment utilisé
    d = number.inverse(e, phi_n)
    public_key = (n, e)
    private_key = (n, d)
    return public_key, private_key



#### 4)
def exercice_2() -> None:
    print("\n############# Exercice 2 #############")
    
    # Exemple d'utilisation pour le chiffrement
    message_clair = 42
    cle_publique = (65537, 123456789)  # Exemple de clé publique (exposant, module)
    message_chiffre = rsa(message_clair, cle_publique)
    print("Message chiffré:", message_chiffre)

    # Exemple d'utilisation pour le déchiffrement
    cle_privee = (987654321, 123456789)  # Exemple de clé privée (exposant, module)
    message_dechiffre = rsa(message_chiffre, cle_privee)
    print("Message déchiffré:", message_dechiffre)
    
    




############# Exercice 3 #############

#### 1)
"""
(a) Bob pour signer un message : Bob doit utiliser sa clé privée (Bs) pour signer un message. 
La clé privée est utilisée pour générer la signature numérique d'un message. 
Cela signifie que Bob utilise son exposant de déchiffrement (Bs) pour créer une signature du message en question.

(b) Alice pour vérifier l'authenticité du message signé par Bob : 
Alice doit utiliser la clé publique de Bob (Bp) pour vérifier l'authenticité du message signé par Bob. 
La clé publique de Bob est utilisée pour vérifier si la signature numérique du message correspond à la signature que Bob aurait générée avec sa clé privée. 
Si la vérification réussit, Alice peut être assurée que le message provient bien de Bob et qu'il n'a pas été altéré en cours de route.
"""


#### 2)
"""
la procédure de signature et la forme du message signé :

 -  Condensation (Hash) du Message : Avant de signer un message, 
 on applique une fonction de condensation (hash) au message original pour obtenir une empreinte (digest) fixe de taille constante. 
 Cette empreinte est généralement beaucoup plus courte que le message original, quelle que soit sa taille. 
 Un algorithme couramment utilisé pour cela est SHA-256, qui produit une empreinte de 256 bits (32 octets).

 -  Signature du Condensé : Une fois que l'empreinte du message est obtenue, on signe cette empreinte à l'aide de la clé privée. 
 Pour cela, on effectue une opération d'exponentiation modulaire sur l'empreinte du message en utilisant la clé privée. 
 Le résultat de cette opération est la signature numérique du message.

 -  Message Signé : La signature numérique obtenue est le message signé. 
 Elle est généralement représentée sous forme d'un nombre entier, qui est la sortie de l'opération d'exponentiation modulaire. 
 Cette signature est jointe au message original ou envoyée séparément pour vérification.

==> La procédure de signature avec RSA implique de condenser le message en une empreinte (hash) de taille fixe, puis de signer cette empreinte avec la clé privée. 
La signature résultante est le message signé, qui est généralement un nombre entier. 
La vérification de la signature implique de condenser le message reçu, 
de déchiffrer la signature avec la clé publique correspondante, 
puis de comparer l'empreinte du message condensé avec l'empreinte obtenue lors de la vérification.

"""


#### 3)
def h(message) -> int:
    if isinstance(message, int):
        message_str = str(message)
    elif isinstance(message, str):
        message_str = message
    else:
        raise TypeError("Input message must be a string or an integer")

    message_bytes = message_str.encode('utf-8')
    sha256_hash = hashlib.sha256(message_bytes)
    hash_bytes = sha256_hash.digest()
    return int.from_bytes(hash_bytes, 'big')


#### 4)
def rsa_sign(message, private_key) -> int:
    hashed_message = h(message)
    signature = rsa(hashed_message, private_key)
    
    return signature

def rsa_verify(message, signature, public_key) -> bool:
    hashed_message = h(message)
    decrypted_signature = rsa(signature, public_key)
    
    return hashed_message == decrypted_signature




def exercice_3() -> None:
    print("\n############# Exercice 3 #############")
    
    integer_value = 12345
    hash_result = h(integer_value)
    print("Condensé SHA-256 de l'entier :", hash_result)
    
    
    #### 5)
    alice_public_key, alice_private_key = gen_rsa_keypair(2048)
    bob_public_key, bob_private_key = gen_rsa_keypair(2048)
    message_from_alice = "Salut Bob, c'est Alice !"
    
    signature = rsa_sign(message_from_alice, alice_private_key)
    message_signed = message_from_alice + "|" + str(signature)
    parts = message_signed.split("|")
    message_received = parts[0]
    signature_received = int(parts[1])
    
    is_valid = rsa_verify(message_received, signature_received, alice_public_key)
    if is_valid:
        print("La signature est valide. Le message provient bien d'Alice.")
    else:
        print("La signature n'est pas valide. Le message peut être altéré ou non signé par Alice.")





############# Exercice 4 #############

#### 1)
"""
Voici comment cela peut être réalisé :

 -  Multiplication par un facteur : L'attaquant peut multiplier un chiffré C par un facteur arbitraire F (un entier) pour obtenir un nouveau chiffré C' = C * F. 
 Puisque le chiffrement RSA consiste en une exponentiation modulaire, cela signifie que décrypter C' donnera un message M' tel que M' = M * F, où M est le message d'origine.

 -  Ajout d'un nombre : L'attaquant peut ajouter un nombre arbitraire A (un entier) au chiffré C pour obtenir un nouveau chiffré C' = C + A. 
 Le décryptage de C' donnera un message M' tel que M' = M + A, où M est le message d'origine.

 -  Combinaison des deux : L'attaquant peut également combiner les deux techniques en multipliant le chiffré C par un facteur F et en ajoutant un nombre A pour obtenir un chiffré C' = (C * F) + A.

==> La malléabilité permet à un attaquant de modifier le chiffré de manière à obtenir des messages pertinents, bien qu'il ne puisse pas nécessairement déterminer le contenu exact du message. 
Cela peut être préjudiciable, en particulier si le chiffré est utilisé pour des protocoles de sécurité qui s'appuient sur l'intégrité des données chiffrées.

"""


#### 2)
"""
Le déterminisme du chiffrement, c'est-à-dire le fait que chiffrer deux fois le même message avec la même clé donne le même chiffré, pose plusieurs problèmes de sécurité :

 -   Révélation de la similitude des messages : Lorsque deux messages identiques sont chiffrés de manière déterministe avec la même clé, les chiffrés résultants seront également identiques. 
 Cela signifie que même si le contenu du message est confidentiel, l'attaquant peut détecter que les deux messages sont les mêmes, ce qui peut révéler des informations sur le modèle de communication. 
 Par exemple, si un attaquant observe que le même chiffré est envoyé à des moments différents, il peut en déduire que les messages sont identiques.

 -   Attaques par texte clair choisi (CPA) : La déterminisme du chiffrement facilite les attaques par texte clair choisi (CPA) où l'attaquant peut choisir des messages à chiffrer et observer les chiffrés résultants. 
 Étant donné que le même message donnera toujours le même chiffré, l'attaquant peut utiliser ces informations pour analyser le chiffrement et potentiellement retrouver la clé secrète.

 -   Attaques de répétition : Dans certaines situations, un attaquant peut répéter des chiffrés identiques pour provoquer une réaction indésirable ou pour identifier des modèles dans le comportement du système.
 
"""


#### 3)
"""
L'implémentation correcte d'algorithmes cryptographiques est une tâche complexe et sujette aux erreurs. 
La cryptographie est une discipline spécialisée qui nécessite une expertise approfondie pour garantir la sécurité des systèmes. 
Voici quelques raisons pour lesquelles il est recommandé d'éviter de mettre en œuvre soi-même des algorithmes cryptographiques et de préférer des bibliothèques existantes :

 -  Complexité : Les algorithmes cryptographiques sont complexes, et des erreurs de mise en œuvre peuvent avoir des conséquences graves sur la sécurité.

 -  Vulnérabilités : Les cryptosystèmes sont continuellement évalués et testés par des experts en sécurité. 
 Les implémentations amateurs sont plus susceptibles de contenir des vulnérabilités.

 -  Mises à jour et évolutions : La cryptographie évolue constamment pour faire face aux nouvelles menaces. 
 Les bibliothèques bien établies sont mises à jour régulièrement pour intégrer les dernières avancées.

 -  Interopérabilité : Les bibliothèques cryptographiques existantes sont conçues pour être compatibles avec d'autres systèmes et protocoles, ce qui facilite l'interopérabilité.

 -  Normes de sécurité : Les bibliothèques bien établies sont conformes aux normes de sécurité reconnues, ce qui garantit leur robustesse.

 -  Audit externe : Les bibliothèques populaires sont généralement soumises à des audits de sécurité par des tiers indépendants, ce qui renforce la confiance dans leur sécurité.

 -  Gain de temps : En utilisant des bibliothèques existantes, on économise du temps et des ressources, car on n'a pas besoin de réinventer la roue.

 -  Responsabilité : La mise en œuvre incorrecte de la cryptographie peut avoir des conséquences juridiques. 
 En utilisant des bibliothèques bien établies, on réduise la responsabilité potentielle.


==> il est recommandé d'utiliser des bibliothèques cryptographiques bien établies et éprouvées plutôt que de tenter de mettre en œuvre ses propres solutions. 
Cela contribue à garantir la sécurité et la robustesse de nos systèmes et applications en matière de sécurité.

"""




if __name__ == '__main__':
    exercice_1()
    exercice_2()
    exercice_3()

