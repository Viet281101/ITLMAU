


################ Exercice 1 :


###### Question 1 :
def sommeListe(liste : list) -> int:
    somme : int = 0
    for element in liste:
        somme += element
    return somme


def mod2(compte:int) -> int:
    return (compte % 2)


def paritePaire(trame:list) -> list:
    somme : int = sommeListe(trame)
    parite : int = mod2(somme)
    trame.append(parite)
    return trame



###### Question 2 :
def pariteImpaire(trame:list) -> list:
    somme : int = sommeListe(trame)
    parite : int = 1 if mod2(somme) == 0 else 0
    trame.append(parite)
    return trame



###### Question 3 :
def verifierParitePaire(trame:list) -> bool:
    somme : int = sommeListe(trame[:-1])
    parite : int = mod2(somme)
    return (parite == trame[-1])


def verifierPariteImpaire(trame:list) -> bool:
    somme : int = sommeListe(trame[:-1])
    parite : int = 1 if mod2(somme) == 0 else 0
    return (parite == trame[-1])




def main() -> None:
    trame : list = [1, 0, 1, 0, 0, 1]
    ##### 1)
    print("La méthode de bit de parite paire : ", paritePaire(trame))
    ##### 2)
    print("La méthode de bit de parite impaire : ", pariteImpaire(trame))
    ##### 3)
    print("Pour vérifier si le bit de parité est paire : ", verifierParitePaire(trame))
    print("Pour vérifier si le bit de parité est impaire : ", verifierPariteImpaire(trame))



if __name__ == "__main__":
    main()



