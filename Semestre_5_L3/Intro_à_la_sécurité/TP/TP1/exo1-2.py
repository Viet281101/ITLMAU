
########## EXERCICE 1 ##########

#### 1)
# Boîte S
sbox : list = [12, 5, 6, 11, 9, 0, 10, 13, 3, 14, 4, 15, 7, 8, 1, 2]

# Fonction de la boîte S
def sbox_lookup(value):
    return sbox[value]

# Fonction de tour
def round(state, round_key):
    # # Ajout de la clé
    # print(f"État avant ajout de la clé : {bin(state)[2:].zfill(4)}")
    # print(f"Clé de tour : {bin(round_key)[2:].zfill(4)}")
    state ^= round_key
    # print(f"État après ajout de la clé : {bin(state)[2:].zfill(4)}")

    # Application de la boîte S
    # print(f"État avant la boîte S : {bin(state)[2:].zfill(4)}")
    state = sbox_lookup(state)
    # print(f"État après la boîte S : {bin(state)[2:].zfill(4)}")

    return state

# Fonction principale pour chiffrer un message
def toy_cipher_encrypt(message: str, key: tuple) -> str:
    # Assurez-vous que la longueur du message et de la clé est correcte
    if len(message) != 4 or len(key) != 2:
        raise ValueError("La taille du message doit être de 4 bits et la taille de la clé doit être de 8 bits (2 clés de 4 bits).")

    # Divisez la clé en deux clés de tour
    round_key0, round_key1 = int(key[0], 2), int(key[1], 2)

    # Convertissez le message en un entier (4 bits)
    state = int(message, 2)

    # # Premier tour
    # print("\nPremier tour :")
    state = round(state, round_key0)

    # # Deuxième tour
    # print("\nDeuxième tour :")
    state = round(state, round_key1)

    # Convertir le résultat en une chaîne binaire de 4 bits
    ciphertext = bin(state)[2:].zfill(4)

    return ciphertext


#### 2)
# Fonction de chiffrement principale
def enc(message: str, key: tuple) -> str:
    # print("\nChiffrement en cours...")
    ciphertext = toy_cipher_encrypt(message, key)
    # print("\nMessage chiffré:", ciphertext)
    return ciphertext



#### 3)
# Boîte S inverse
sbox_inv = [5, 14, 15, 8, 12, 1, 2, 13, 6, 11, 3, 4, 9, 10, 7, 0]

# Fonction de la boîte S inverse
def sbox_lookup_inv(value):
    return sbox_inv[value]

# Fonction de tour inverse
def back_round(state, round_key):
    # # Application de la boîte S inverse
    # print(f"État avant la boîte S inverse : {bin(state)[2:].zfill(4)}")
    state = sbox_lookup_inv(state)
    # print(f"État après la boîte S inverse : {bin(state)[2:].zfill(4)}")

    # # Soustraction de la clé inverse
    # print(f"État avant soustraction de la clé inverse : {bin(state)[2:].zfill(4)}")
    # print(f"Clé de tour inverse : {bin(round_key)[2:].zfill(4)}")
    state ^= round_key
    # print(f"État après soustraction de la clé inverse : {bin(state)[2:].zfill(4)}")

    return state

# Fonction principale pour déchiffrer un message
def toy_cipher_decrypt(ciphertext, key):
    # Assurez-vous que la longueur du message chiffré et de la clé est correcte
    if len(ciphertext) != 4 or len(key) != 2:
        raise ValueError("La taille du message chiffré doit être de 4 bits et la taille de la clé doit être de 8 bits (2 clés de 4 bits).")

    # Divisez la clé en deux clés de tour
    round_key0, round_key1 = int(key[0], 2), int(key[1], 2)

    # Convertissez le message chiffré en un entier (4 bits)
    state = int(ciphertext, 2)

    # # Premier tour inverse
    # print("\nPremier tour inverse :")
    state = back_round(state, round_key1)

    # # Deuxième tour inverse
    # print("\nDeuxième tour inverse :")
    state = back_round(state, round_key0)

    # Convertir le résultat en une chaîne binaire de 4 bits
    plaintext = bin(state)[2:].zfill(4)

    return plaintext


#### 4)
# Fonction de déchiffrement principale
def dec(ciphertext, key) -> str:
    # print("\nDéchiffrement en cours...")
    plaintext = toy_cipher_decrypt(ciphertext, key)
    # print("\nMessage déchiffré:", plaintext)
    return plaintext


#### 5)
def exercise_1_debug() -> None:
    # Exemple d'utilisation
    message : str = "1101"  # Message de 4 bits
    key : tuple = ("1010", "0101")  # Clé de 8 bits divisée en deux clés de 4 bits

    enc(message, key)

    dec(enc(message, key), key)
    
    

########## EXERCICE 2 ##########

#### 1)
def enc_byte(byte, key) -> int:
    # Vérifiez que l'octet est une valeur entre 0 et 255 (8 bits)
    if not (0 <= byte <= 255):
        raise ValueError("L'octet doit être une valeur entre 0 et 255 (8 bits).")

    # Divisez l'octet en deux nibbles (4 bits chacun)
    nibble1 = (byte >> 4) & 0x0F
    nibble2 = byte & 0x0F

    # Chiffrez chaque nibble avec la fonction enc()
    encrypted_nibble1 = int(enc(format(nibble1, '04b'), key), 2)
    encrypted_nibble2 = int(enc(format(nibble2, '04b'), key), 2)

    # Concaténez les nibbles chiffrés pour obtenir l'octet chiffré complet
    encrypted_byte = (encrypted_nibble1 << 4) | encrypted_nibble2

    return encrypted_byte


#### 2)
def dec_byte(encrypted_byte, key):
    # Vérifiez que l'octet chiffré est une valeur entre 0 et 255 (8 bits)
    if not (0 <= encrypted_byte <= 255):
        raise ValueError("L'octet chiffré doit être une valeur entre 0 et 255 (8 bits).")

    # Divisez l'octet chiffré en deux nibbles (4 bits chacun)
    nibble1 = (encrypted_byte >> 4) & 0x0F
    nibble2 = encrypted_byte & 0x0F

    # Déchiffrez chaque nibble avec la fonction dec()
    decrypted_nibble1 = int(dec(format(nibble1, '04b'), key), 2)
    decrypted_nibble2 = int(dec(format(nibble2, '04b'), key), 2)

    # Concaténez les nibbles déchiffrés pour obtenir l'octet déchiffré complet
    decrypted_byte = (decrypted_nibble1 << 4) | decrypted_nibble2

    return decrypted_byte


#### 3)
# Fonction pour chiffrer un caractère ASCII avec ToyCipher
def enc_char(char, key):
    # Vérifiez que le caractère est un seul caractère ASCII
    if len(char) != 1 or not (32 <= ord(char) <= 126):
        raise ValueError("Le caractère doit être un caractère ASCII imprimable.")
    
    # Convertir le caractère en valeur ASCII
    ascii_value = ord(char)
    
    # Chiffrer la valeur ASCII avec la fonction enc_byte()
    encrypted_byte = enc_byte(ascii_value, key)
    
    # Retourner l'octet chiffré sous forme d'hexadécimal
    return format(encrypted_byte, '02X')


# Fonction pour déchiffrer un caractère ASCII avec ToyCipher
def dec_char(encrypted_char, key):
    # Convertir l'hexadécimal en valeur numérique
    ascii_value = int(encrypted_char, 16)
    
    # Déchiffrer la valeur ASCII avec la fonction dec_byte()
    decrypted_byte = dec_byte(ascii_value, key)
    
    # Retourner l'octet déchiffré sous forme de caractère
    return chr(decrypted_byte)



#### 4)
def enc_file(input_file, key):
    # Ajoutez le suffixe ".enc" au nom du fichier de sortie
    output_file = input_file + ".enc"

    try:
        with open(input_file, 'rb') as f_in, open(output_file, 'wb') as f_out:
            while True:
                byte = f_in.read(1)  # Lire un octet du fichier d'entrée
                if not byte:
                    break  # Fin du fichier
                encrypted_byte = enc_byte(ord(byte), key)  # Chiffrer l'octet
                f_out.write(bytes([encrypted_byte]))  # Écrire l'octet chiffré dans le fichier de sortie
        print(f"Le fichier {input_file} a été chiffré avec succès et enregistré sous {output_file}")
    except Exception as e:
        print(f"Une erreur s'est produite : {str(e)}")



#### 5)
def dec_file(encrypted_file, key):
    # Ajoutez le suffixe ".dec" au nom du fichier de sortie
    decrypted_file = encrypted_file + ".dec"

    try:
        with open(encrypted_file, 'rb') as f_in, open(decrypted_file, 'wb') as f_out:
            while True:
                byte = f_in.read(1)  # Lire un octet du fichier chiffré
                if not byte:
                    break  # Fin du fichier
                decrypted_byte = dec_byte(ord(byte), key)  # Déchiffrer l'octet
                f_out.write(bytes([decrypted_byte]))  # Écrire l'octet déchiffré dans le fichier de sortie
        print(f"Le fichier {encrypted_file} a été déchiffré avec succès et enregistré sous {decrypted_file}")
    except Exception as e:
        print(f"Une erreur s'est produite : {str(e)}")




#### 6)
def exercise_2_debug() -> None:
    key = ("1010", "0101")  # Clé de 8 bits divisée en deux clés de 4 bits
    
    byte_to_encrypt = 150  # Exemple d'octet à chiffrer (par exemple)
    encrypted_byte = 85  # Exemple d'octet chiffré (par exemple)
    char_to_encrypt = 'A'  # Exemple de caractère ASCII (par exemple)
    file_to_encrypt = "hello.txt"  # Nom du fichier d'entrée
    file_to_decrypt = "hello.txt.enc"  # Nom du fichier chiffré


    encrypted_byte = enc_byte(byte_to_encrypt, key)
    print("Octet chiffré:", encrypted_byte)
    
    decrypted_byte = dec_byte(encrypted_byte, key)
    print(f"Octet déchiffré: {decrypted_byte}")
    
    
    # Chiffrement du caractère
    encrypted_char = enc_char(char_to_encrypt, key)
    print("Caractère chiffré:", encrypted_char)  # Affiche le caractère chiffré

    # Déchiffrement du caractère
    decrypted_char = dec_char(encrypted_char, key)
    print(f"Caractère déchiffré: {decrypted_char}")  # Affiche le caractère déchiffré
    
    enc_file(file_to_encrypt, key)
    dec_file(file_to_decrypt, key)




if __name__ == "__main__":
    exercise_1_debug()
    exercise_2_debug()

