



################################# Exercice 3 : #################################

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


#### 1) Écrire une fonction Python qui détermine les fréquences d'apparition des lettres d'un textee passé en paramètre dans une liste.
def frequencies(texte : str) -> list[float]:
    freq = [0] * 26
    for c in texte.lower():
        if c.isalpha():
            freq[ord(c) - 97] += 1
    total = sum(freq)
    return [f/total for f in freq]


#### 2) 
def cherche_cles(freqs : list) -> list[int]:
    sorted_freqs = sorted(freqs, reverse=True)
    cles : list = []
    for i in range(2):
        for j in range(26):
            if freqs[j] == sorted_freqs[i]:
                cle = (j-4)%26, (4-j)%26
                cles.append(cle)
                break
    return cles


def decrypt(texte : str, cle) -> str:
    a, b = cle
    decrypted : str = ""
    for c in texte:
        if c.isalpha():
            d = chr(((ord(c)-97-b)*inverse_mod(a, 26))%26 + 97)
            decrypted += d
        else:
            decrypted += c
    return decrypted




def main() -> None:
    #### 3)
    texte :str = "akdyne.vxnkbijdju.dfodjoujhrajdcjd.jyboigfjudgfid jnhj..jo.dcjdybiqqnjndj.dcjdcjybiqqnjndfodhjuukxjsdcvo.dajdyvo.jofdojdcvi.dj.njdyvoofdgfjdcjduvodj,jci.jfndj.dcjduvodcju.iok.kinjz"
    freqs : list = frequencies(texte)
    print(freqs)
    
    cles : list = cherche_cles(freqs)
    print(cles)




if __name__ == '__main__':
    main()



