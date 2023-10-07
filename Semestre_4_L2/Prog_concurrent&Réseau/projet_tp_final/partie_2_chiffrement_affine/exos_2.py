



################################# Exercice 2 : #################################


#### 1) Écrire une fonction chiffrer_aff qui prend en paramètres deux entiers a et b (laclé de chiffrement), et une chaîne de caractère, et qui renvoie le texte dont chaque lettre a été chiffrée individuellement.
def chiffrer_aff(a : int, b : int, message : str) -> str:
    """
    Chiffre un texte en utilisant le chiffrement affine avec la clé (a, b).
    """
    message_chiffre : str = ''
    n : int = 29
    for lettre in message:
        if lettre.isalpha():
            indice = ord(lettre.upper()) - 65
            lettre_chiffree = chr((a*indice + b) % n + 65)
            message_chiffre += lettre_chiffree
        elif lettre == ',':
            message_chiffre += chr((a*27 + b) % n + 65)
        elif lettre == '.':
            message_chiffre += chr((a*28 + b) % n + 65)
        elif lettre == ' ':
            message_chiffre += ' '
    return message_chiffre


#### 3) Écrire une fonction dechiffrer_aff qui prend en paramètres deux entiers a et b (la clé de chiffrement), et une chaîne de caractère, et qui renvoie la chaîne originale, c'est-à-dire le texte qui a permis d'obtenir la chaîne en paramètre après chiffrement
def dechiffrer_aff(a : int, b : int, message_chiffre : str) -> str:
    message : str = ''
    n : int = 29
    for lettre_chiffree in message_chiffre:
        if lettre_chiffree.isalpha():
            indice_chiffre = ord(lettre_chiffree.upper()) - 65
            inv_a = inverse_mod(a, n)
            indice = (inv_a * (indice_chiffre - b)) % n
            lettre = chr(int(indice) + 65)
            message += lettre
        elif lettre_chiffree == ',':
            inv_a = inverse_mod(a, n)
            indice = (inv_a * (27 - b)) % n
            message += chr(int(indice) + 65)
        elif lettre_chiffree == '.':
            inv_a = inverse_mod(a, n)
            indice = (inv_a * (28 - b)) % n
            message += chr(int(indice) + 65)
        elif lettre_chiffree == ' ':
            message += ' '
    return message



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





def main() -> None:
    a, b = 4, 21
    
    # Texte à chiffrer
    texte : str = "la clef est dans le coffre"
    
    # Chiffrement du texte
    texte_chiffre : str = chiffrer_aff(a, b, texte)
    
    print(texte_chiffre)
    
    print(dechiffrer_aff(4, 21, texte_chiffre))
    
    message : str = "v.vlukyu,fwtfyo oyn.ws"
    print(dechiffrer_aff(4, 21, message))




if __name__ == '__main__':
    main()


