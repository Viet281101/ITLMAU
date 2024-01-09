

PREFIX = "./"


## Dictionnaire pour représenter l'alphabet
D = { chr (i + ord("A") ): i for i in range (26) }
D[' '] = 26
D['.'] = 27
D[','] = 28

## Son dictionnaire inverse
invD : list = []
for i in range(29):
    invD.append( chr(i + ord("A")) )
invD += [' ', '.', ',']

# invD = { v: k for k, v in D.items() }


T : str = "BONJOUR."

def encode(T) -> list:
    res : list = []
    for c in T:
        res.append(D[c])
    return res
    # return [D[c] for c in T]

def decode(T):
    res : str = ""
    for c in T:
        res += invD[c]
    return res
    # return "".join([invD[c] for c in T])


def chiffre_cesar(T, k):
    liste_T = encode(T)
    enc_T = [ (c + k) % 29 for c in liste_T ]
    return decode(enc_T)
    # return [(c + k) % 29 for c in T]

def dechiffre_cesar(T, k):
    liste_T = encode(T)
    enc_T = [ (c - k) % 29 for c in liste_T ]
    return decode(enc_T)

    ### Autre solution
    # return [(c - k) % 29 for c in T]
    
    ### ou:
    # return chiffre_cesar(T, (29 - k) % 29)
    

def plus_frequente(T) -> int:
    # liste_T = encode(T)
    # occ = [0] * 29
    # for c in liste_T:
    #     occ[c] += 1
    # return invD[occ.index(max(occ))]

    ### Autre solution
    # return invD[max(T, key=T.count)]
    
    ### ou:
    tab = [0 for i in range(29)]
    for x in T:
        tab[D[x]] += 1
    return tab.index(max(tab))
    

def attaque_cesar(T):
    K = plus_frequente(T) - 26
    res = dechiffre_cesar(T, K)
    return res
    
    ### Autre solution
    # return dechiffre_cesar(T, D[plus_frequente(T)] - D['E'])


f = open(PREFIX + "file0" + "_upper.txt", "r")
M = f.read()
f.close()

C = chiffre_cesar(M, 3)
MM = dechiffre_cesar(C, 3)
print(MM == M)


def remove_special_characters(text : str) -> str:
    res : str = ''
    text = text.upper()
    for x in text:
        if x in ["à", "â", "ä", "é", "è", "ê", "ë", "î", "ï", "ô", "ö", "ù", "û", "ü", "ç", "œ", "æ", " "]:
            res += x
    return res


def deux_plus_frequents(text : str) -> tuple:
    text : str = remove_special_characters(text)
    tab = [0 for i in range(29)]
    for x in text:
        tab[D[x]] += 1
    max1 = tab.index(max(tab))
    tab[max1] = 0
    max2 = tab.index(max(tab))
    return (invD[max1], invD[max2])


def chiffre_vigenere(T, K):
    res : str = ''
    for i in range(len(T)):
        res += chiffre_cesar(T[i], D[K[i % len(K)]] - D['A'])
    return res

def dechiffre_vigenere(T, K):
    res = ''
    for i in range(len(T)):
        res += dechiffre_cesar(T[i], D[K[i % len(K)]] - D['A'])
    return res

def IC(T):
    text = remove_special_characters(T)
    n = len(text)
    tab = [0 for i in range(29)]
    for x in text:
        tab[D[x]] += 1
    res = 0
    for i in range(29):
        res += tab[i] * (tab[i] - 1)
    return res / (n * (n - 1))

def calcule_longeur_cle(T):
    text = remove_special_characters(T)
    n = len(text)
    res = 0
    for i in range(1, 20):
        res += abs(IC(text[::i]) - 0.0778)
    return res / 20

def calcule_decalage(T) -> int:
    text = remove_special_characters(T)
    n = len(text)
    tab = [0 for i in range(29)]
    for x in text:
        tab[D[x]] += 1
    max1 = tab.index(max(tab))
    return (max1 - D['E']) % 29

def attaque_vigenere(T) -> str:
    longeur_cle = calcule_longeur_cle(T)
    decalage = calcule_decalage(T)
    res = ''
    for i in range(int(longeur_cle)):
        res += invD[(D[attaque_cesar(T[i::int(longeur_cle)])] - decalage) % 29]
    return res


def main() -> None:
    ## Encode et decode
    print ("Encode(T):", encode(T))
    print ("Decode(T):", decode(encode(T)))
    
    ## Chiffre_cesar et dechiffre_cesar
    print ("Chiffre_cesar(T, 3):", chiffre_cesar(T, 3))
    print ("Dechiffre_cesar(T, 3):", dechiffre_cesar(chiffre_cesar(T, 3), 3))
    print ("Plus_frequente(T):", plus_frequente(T))
    print ("Attaque_cesar(T):", attaque_cesar(T))
    print ("Attaque_cesar(C):", attaque_cesar(C))
    print ("Deux_plus_frequents(M):", deux_plus_frequents(M))
    print ("Chiffre_vigenere(M, 'AB'): ", chiffre_vigenere(M, 'AB'))
    print ("Dechiffre_vigenere(M, 'AB'): ", dechiffre_vigenere(chiffre_vigenere(M, 'AB'), 'AB'))
    

if __name__ == "__main__":
    main()


