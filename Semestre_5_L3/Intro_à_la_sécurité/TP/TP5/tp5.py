
############# ~~ TP 5 : BellCoRe ~~ #############

import random
import sympy
import time

############# Exercice 1 #############

#### 1)

## (a)
def generate_prime(bits):
    while True:
        num = random.getrandbits(bits)
        if sympy.isprime(num):
            return num

p = generate_prime(512)
q = generate_prime(512)

while p == q:
    q = generate_prime(512)

print("p =", p)
print("q =", q)


## (b)
n = p * q
print("n =", n)


## (c)
e = 65537
if sympy.gcd(e, (p-1)*(q-1)) == 1:
    print("e est premier avec (p-1)*(q-1)")
else:
    print("e n'est pas premier avec (p-1)*(q-1)")


## (d)
d = sympy.mod_inverse(e, (p-1)*(q-1))
print("d =", d)


## (e)
m = random.randint(1, n - 1)
print("m =", m)



#### 2)
"""
Voici comment la clé privée change avec l'optimisation CRT :

    Clé Privée Complète (Avant CRT) :
        d : L'exposant de déchiffrement privé.
        n : Le module RSA, qui est le produit de deux nombres premiers distincts, p et q.

    Clé Privée Optimisée avec CRT :
        dp : L'exposant de déchiffrement privé partiel modulo (p-1). C'est d mod (p-1).
        dq : L'exposant de déchiffrement privé partiel modulo (q-1). C'est d mod (q-1).
        qinv : L'inverse multiplicatif de q modulo p. C'est q^(-1) mod p.

L'optimisation CRT divise le calcul de la déchiffrement en deux parties indépendantes, une pour p et une pour q, ce qui accélère considérablement le processus de déchiffrement. 
Au lieu de calculer directement m^d mod n, on calcule m^dp mod p et m^dq mod q séparément, puis on combine les résultats à l'aide du CRT pour obtenir le résultat final. 
Cela réduit la complexité des calculs modulo n.

"""


#### 3)
p = 13382533362209595709783620343773084493752267135926929233126259477571084194938481643811502565371645938430281540599305471456917264652832844590520279848610269
q = 11168539544243530055303363043508824957071196210224815210912809344358792515503957860355610082195093677862431555864955292410866387123877460331451111358082677
d = 129255000959991947916761987567497292605756476684030216043767870351014942128579166552435739251464358681794809836968934087652085674914760437717997418350005221273489327327614873840612648483876144848481020526831503268070131440202465221908027701650237789308372774116447833097020477838003014838006393916361625555137

dp = d % (p - 1)
dq = d % (q - 1)
qinv = sympy.mod_inverse(q, p)

print("dp =", dp)
print("dq =", dq)
print("qinv =", qinv)



#### 4)
def rsa_signature_classic(m, d, n):
    return pow(m, d, n)

start_time = time.time()
for _ in range(1000):
    signature = rsa_signature_classic(m, d, p * q)
end_time = time.time()
elapsed_time = end_time - start_time

print(f"Temps total pour 1000 signatures RSA classiques : {elapsed_time} secondes")




#### 5)
def rsa_signature_crt(m, dp, dq, p, q, qinv):
    m1 = pow(m, dp, p)
    m2 = pow(m, dq, q)
    h = (qinv * (m1 - m2)) % p
    return m2 + h * q

start_time_2 = time.time()
for _ in range(1000):
    signature = rsa_signature_crt(m, dp, dq, p, q, qinv)
end_time_2 = time.time()
elapsed_time_2 = end_time_2 - start_time_2

print(f"Temps total pour 1000 signatures CRT-RSA : {elapsed_time_2} secondes")



#### 6)
"""
Le facteur de vitesse dépend de la taille des clés et de la complexité du calcul, 
mais en général, il peut être beaucoup plus rapide.
"""
signature_classic = rsa_signature_classic(m, d, p * q)
signature_crt = rsa_signature_crt(m, dp, dq, p, q, qinv)

if signature_classic == signature_crt:
    print("Les signatures RSA classiques et CRT-RSA sont identiques.")
else:
    print("Les signatures RSA classiques et CRT-RSA ne sont pas identiques.")





############# Exercice 2 #############

#### 1)
"""
s = 3f010be37eb5eca9

"""


#### 2)




