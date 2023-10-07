
########## EXERCICE 3 ##########


# Boîte S
sbox: list = [12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 4, 15, 7, 8, 1, 2]

# Fonction de la boîte S
def sbox_lookup(value):
    return sbox[value]

# Fonction de tour
def round(state, round_key):
    state ^= round_key
    state = sbox_lookup(state)
    return state

# Fonction principale pour chiffrer un message en mode ECB
def enc(plaintext, key):
    if len(plaintext) % 4 != 0:
        raise ValueError("La longueur du message doit être un multiple de 4.")

    # Divisez la clé en deux clés de tour
    round_key0, round_key1 = int(key[0], 2), int(key[1], 2)

    # Chiffrez le message par blocs de 4 bits
    encrypted_text = ""
    for i in range(0, len(plaintext), 4):
        block = plaintext[i:i+4]
        state = int(block, 2)

        # Premier tour
        state = round(state, round_key0)

        # Deuxième tour
        state = round(state, round_key1)

        # Convertir le résultat en une chaîne binaire de 4 bits
        encrypted_block = bin(state)[2:].zfill(4)
        encrypted_text += encrypted_block

    return encrypted_text


# Fonction pour convertir du texte en binaire
def text_to_binary(text):
    binary_text = ""
    for char in text:
        binary_char = bin(ord(char))[2:].zfill(8)  # Convertir le caractère en binaire sur 8 bits
        binary_text += binary_char
    return binary_text


#### 1)

def question1():
    key = ("1001", "0000")  # Clé de 8 bits divisée en deux clés de 4 bits
    # Ouvrir le fichier en mode lecture
    with open("test.txt", "r") as file:
        # Lire le contenu du fichier
        plaintext = file.read()

    # Vérifier si le fichier a bien été lu
    if plaintext:
        # Convertir le texte en binaire
        binary_plaintext = text_to_binary(plaintext)
        print("\nTexte en binaire:", binary_plaintext)

        # Chiffrer le texte en binaire
        encrypted_text = enc(binary_plaintext, key)
        print("\nTexte chiffré en mode ECB:", encrypted_text)
    else:
        print("Le fichier est vide ou n'a pas pu être lu.")



"""
Pour le résultat:

Texte en binaire: 011000110110111101110101011000110110111101110101001111110010000001100011011011110111010101100011011011110111010100100001

Texte chiffré en mode ECB: 011010010110010001011101011010010110010001011101100101000010000101101001011001000101110101101001011001000101110100101011
"""



#### 2)
"""

"""



#### 3)
import os


# Boîte S inverse
sbox_inv = [5, 14, 15, 8, 12, 1, 2, 13, 6, 11, 3, 4, 9, 10, 7, 0]

# Fonction de la boîte S inverse
def sbox_lookup_inv(value):
    return sbox_inv[value]

# Fonction de tour inverse pour ToyCipher
def back_round(state, round_key):
    # Application de la boîte S inverse
    state = sbox_lookup_inv(state)

    # Soustraction de la clé inverse
    state ^= round_key

    return state


def dec(ciphertext, key):
    if len(ciphertext) != len(key[0]):
        raise ValueError("La taille du message chiffré doit être égale à la taille de la clé.")

    round_key0, round_key1 = int(key[0], 2), int(key[1], 2)

    state = int(ciphertext, 2)

    state = back_round(state, round_key1)

    state = back_round(state, round_key0)

    plaintext = format(state, '0' + str(len(ciphertext)) + 'b')

    return plaintext


def enc_block_cbc(plaintext_block, previous_ciphertext_block, key):
    if len(plaintext_block) != len(previous_ciphertext_block):
        raise ValueError("Les blocs doivent avoir la même longueur.")

    xored_block = format(int(plaintext_block, 2) ^ int(previous_ciphertext_block, 2), '0' + str(len(plaintext_block)) + 'b')

    encrypted_block = enc(xored_block, key)

    return encrypted_block


def enc_file_cbc(input_filename, output_filename, key):
    block_size = len(key[0])
    iv = format(int.from_bytes(os.urandom(block_size // 8), byteorder='big'), '0' + str(block_size) + 'b')
    
    with open(input_filename, 'rb') as file:
        with open(output_filename, 'wb') as output_file:
            previous_ciphertext_block = iv  # Initialisez le bloc de texte chiffré précédent avec le vecteur d'initialisation
            
            while True:
                plaintext_block = file.read(block_size // 8)
                if not plaintext_block:
                    break
                
                if len(plaintext_block) < block_size // 8:
                    plaintext_block = plaintext_block.ljust(block_size // 8, b'\x00')
                
                encrypted_block = enc_block_cbc(format(int.from_bytes(plaintext_block, byteorder='big'), '0' + str(block_size) + 'b'), previous_ciphertext_block, key)
                
                output_file.write(int(encrypted_block, 2).to_bytes(block_size // 8, byteorder='big'))
                
                previous_ciphertext_block = encrypted_block


def dec_block_cbc(ciphertext_block, previous_ciphertext_block, key):
    if len(ciphertext_block) != len(previous_ciphertext_block):
        raise ValueError("Les blocs doivent avoir la même longueur.")
    
    decrypted_block = dec(ciphertext_block, key)
    
    xored_block = format(int(decrypted_block, 2) ^ int(previous_ciphertext_block, 2), '0' + str(len(decrypted_block)) + 'b')
    
    return xored_block


def dec_file_cbc(input_filename, output_filename, key):
    with open(input_filename, 'rb') as file:
        with open(output_filename, 'wb') as output_file:
            previous_ciphertext_block = None
            
            while True:
                ciphertext_block = file.read(len(key[0]) // 8)
                if not ciphertext_block:
                    break
                
                if len(ciphertext_block) < len(key[0]) // 8:
                    ciphertext_block = ciphertext_block.ljust(len(key[0]) // 8, b'\x00')
                
                decrypted_block = dec_block_cbc(format(int.from_bytes(ciphertext_block, byteorder='big'), '0' + str(len(key[0])) + 'b'), previous_ciphertext_block, key)
                
                output_file.write(int(decrypted_block, 2).to_bytes(len(key[0]) // 8, byteorder='big'))
                
                previous_ciphertext_block = ciphertext_block


def question3():
    key = ("1010", "0101")
    input_file = "test.txt"
    encrypted_file = "test_encrypted_cbc.bin"
    decrypted_file = "test_decrypted_cbc.txt"

    # Chiffrez le fichier en mode CBC
    enc_file_cbc(input_file, encrypted_file, key)

    # Déchiffrez le fichier en mode CBC
    dec_file_cbc(encrypted_file, decrypted_file, key)




#### 4)
"""
la génération aléatoire de l'IV est une pratique bien en cryptographie 
car elle renforce la sécurité du chiffrement en introduisant de l'unicité, 
de l'imprédictibilité et en évitant les schémas répétitifs. 
Cependant, il est essentiel de stocker et de transmettre correctement l'IV 
lors de l'utilisation de modes de chiffrement qui en dépendent.
"""



if __name__ == "__main__":
    question1()
    question3()


