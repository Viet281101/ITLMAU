
def Eratosthene(lim:int) -> list:
    L : list = []
    for i in range(2, lim+1):
        if len(L) == 0:
            L.append(i)
        else: 
            prem : bool = True
            for j in L:
                if i % j == 0:
                    prem = False
            if prem == True:
                L.append(i)    
    return L


########### PGCD 
def euclide_itera(a:int, b:int) -> int:
    while( b != 0):
        temp = b
        b = a % b
        a = temp
    return a

        
def euclide_origin(a:int, b:int) -> int:
    while( a != b):
        if a > b: 
            a -= b
        else: 
            b -= a
    return a


def euclide_rec(a:int, b:int) -> int:
    if b == 0:
        return a
    else: 
        return euclide_rec(b, (a%b))


def main() -> None:
    print("\nLes nombres premiers de 0 à 1000 : ", Eratosthene(1000))
    print("\nPGCD avec algo euclide iterative de 21 et 15: ", euclide_itera(68, 24))
    print("\nPGCD avec algo euclide origin de 21 et 15: ", euclide_origin(21, 15))
    print("\nPGCD avec algo euclide recursive de 21 et 15: ", euclide_rec(21, 15))


if __name__ == "__main__":
    main()

