


################ Exercice 3 :



def characterCount(trame:str) -> str:
    n : int = len(trame)
    ## pour convertir le nombre de caractères en binaire, 
    # puis utiliser la méthode 'zfill()' pour remplir les 0 à gauche jusqu'à obtenir une longueur de 8 bits
    n = bin(n)[2:].zfill(8) 
    trame += n
    if len(trame) % 8 != 0:
        trame = trame + '0' * (8 - len(trame) % 8)
    return trame

def byteStuffing(trame:str) -> str:
    ## pour remplacer les séquence de cinq 1 consécutifs par une séquence de cinq 1 suivis d'un 0.
    trame = trame.replace('1111', '11110')
    ## Puis ajouter les octets de drapeau au début et à la fin de la trame
    trame = '01111110' + trame + '01111110'
    return trame


def main() -> None:
    trame : str = '110011000110100'
    print(characterCount(trame))
    print(byteStuffing(trame))


if __name__ == '__main__':
    main()



