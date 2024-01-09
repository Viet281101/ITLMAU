

################ Exercice 2 :




def checksum(trame:list) -> int:
    somme : int = 0 
    for octet in trame:
        somme += int(octet, 2)
    
    ### pour convertir la somme en binaire et prendre le modulo 256, qui donne checksum de 8 bits sur la trame:
    somme = bin(somme % 256)[2:].zfill(8) 

    return somme




def main() -> None:
    trame : list = ['011001101', '01101001']
    print("Calculer le checksum pour la trame : ", checksum(trame))


if __name__ == '__main__':
    main()


