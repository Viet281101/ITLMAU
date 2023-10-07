


import numpy as np


################################# Exercice 4 : #################################


##### 1)
def multiply_matrices(matrix1, matrix2):
    """
    Multiplies two matrices together.
    """
    return np.dot(matrix1, matrix2)

def multiply_matrix_by_vector(matrix, vector):
    """
    Multiplies a matrix by a vector.
    """
    return np.dot(matrix, vector)

def multiply_matrix_by_scalar(matrix, scalar):
    """
    Multiplies all the coefficients of a matrix by a scalar.
    """
    return scalar * matrix

def add_vectors(vector1, vector2):
    """
    Adds two vectors together.
    """
    return np.add(vector1, vector2)


##### 2)
def decouper_texte(texte):
    """
    Cuts a string of characters into a list of lists of two characters.
    """
    if len(texte) % 2 == 1:
        texte += " "
    pairs = [texte[i:i+2] for i in range(0, len(texte), 2)]
    return [list(pair) for pair in pairs]


##### 3)
def rassembler_texte(paires):
    """
    Combines a list of pairs of characters into a single string.
    """
    flattened = [char for pair in paires for char in pair]
    return "".join(flattened).rstrip()



##### 4)
def chiffrer_hill(texte : str, A, B):
    """
    Encrypts a string using the Hill cipher.
    """
    paires = decouper_texte(texte)
    numerique = [[ord(char) - 97 for char in pair] for pair in paires]
    A = np.matrix(A)
    B = np.array(B)
    chiffre = [multiply_matrix_by_vector(A, np.transpose(np.matrix(pair))) + np.transpose(np.matrix(B)) for pair in numerique]
    chiffre = [[chr(int(element % 29) + 97) for element in np.array(pair)] for pair in chiffre]
    return rassembler_texte(chiffre)




################################# Exercice 5 : #################################

def inverse_modulo(n, mod):
    """
    Calculates the inverse of n modulo mod.
    """
    t, newt = 0, 1
    r, newr = mod, n
    while newr != 0:
        quotient = r // newr
        t, newt = newt, t - quotient * newt
        r, newr = newr, r - quotient * newr
    if r > 1:
        raise ValueError(f"{n} is not invertible modulo {mod}")
    return (t % mod)

##### 1)
def est_inversible_modulo_29(matrice):
    """
    Determines if a matrix is invertible modulo 29 and, if so, calculates its modular inverse.
    """
    A = np.matrix(matrice)
    det = int(np.round(np.linalg.det(A)))
    if det % 29 == 0:
        return False, None
    else:
        inv_det = inverse_modulo(det, 29)
        A_inv = inv_det * np.round(np.linalg.inv(A)) % 29
        return True, A_inv.tolist()


##### 2)
def dechiffrer_hill(texte_chiffre : str, A, B):
    """
    Decrypts a string using the Hill cipher.
    """
    paires_chiffrees = decouper_texte(texte_chiffre)
    chiffre = [[ord(char) - 97 for char in pair] for pair in paires_chiffrees]
    A = np.matrix(A)
    B = np.array(B)
    est_inversible, A_inv = est_inversible_modulo_29(A)
    if not est_inversible:
        return "La matrice de chiffrement n'est pas inversible modulo 29."
    dechiffre = [multiply_matrix_by_vector(A_inv, np.transpose(np.matrix(pair - B))) + np.transpose(np.matrix(B)) for pair in chiffre]
    dechiffre = [[chr(int(element % 29) + 97) for element in np.array(pair)] for pair in dechiffre]

    return rassembler_texte(dechiffre)



##### 3)
def retrouver_matrice_dechiffrement(message_chiffre):
    # On récupère les 4 derniers caractères du message (la signature)
    signature = message_chiffre[-4:]
    
    # On calcule les vecteurs correspondants aux paires "b." et "d."
    b_vect = np.array([[1], [1]])
    d_vect = np.array([[3], [0]])
    
    # On calcule les vecteurs correspondants aux paires de caractères
    signature_vect = np.array([[ord(signature[0])-97], [ord(signature[2])-97]])
    avant_dernier_vect = np.array([[ord(message_chiffre[-5])-97], [ord(message_chiffre[-6])-97]])
    deuxieme_dernier_vect = np.array([[ord(message_chiffre[-7])-97], [ord(message_chiffre[-8])-97]])
    troisieme_dernier_vect = np.array([[ord(message_chiffre[-9])-97], [ord(message_chiffre[-10])-97]])
    
    # On résout le système d'équations pour retrouver la matrice de déchiffrement
    M = np.array([b_vect, d_vect, avant_dernier_vect, deuxieme_dernier_vect, troisieme_dernier_vect])
    inv_M = np.linalg.inv(M)
    
    # On renvoie la matrice de déchiffrement
    return inv_M[:2, :2] % 29




def main() -> None:
    a : list = [[2, 3], [1, 4]]
    b : list = [1, 2]

    message_clair = "vive les vacances"
    
    message_chiffre = chiffrer_hill(message_clair, a, b)
    print(message_chiffre)

    message_dechiffre = dechiffrer_hill(message_chiffre, a, b)
    print(message_dechiffre)


if __name__ == "__main__":
    main()

