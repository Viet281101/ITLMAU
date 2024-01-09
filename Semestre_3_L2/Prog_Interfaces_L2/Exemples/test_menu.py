

#!/usr/bin/env python

# -*- coding: utf-8 -*-

from tkinter import *

from tkinter.filedialog import *

from PIL import Image as Img

from PIL import ImageTk

def ouverture_de_l_image():
    """
    Permet de modifier l'image à traiter en modifiant la variable presentation.
    Aucun argument à transmettre.
    Presentation est déclarée global car on veut lui affecter une nouvelle valeur.
    *
    La variable presentation contient la référence de l'objet Img qui contient l'image à traiter.
    La variable filepath est locale à la fonction.
    La variable nomImage fait référence à un objet de classe StringVar du programme principal
    La variable labelphoto fait référence à un objet de classe Label du programme principal.
    """
    global presentation
    #permet d'ouvrir l'image
    filepath = askopenfilename(title="Ouvrir une image",filetypes=[('jpg files','.jpg'),('png files','.png'),('all files','.*')])
    nomImage.set(filepath)
    #change l'image de base de presentation avec l'image choisie
    presentation = Img.open(filepath)
    presentationTk = ImageTk.PhotoImage(presentation)
    # la ligne ci-dessous permet de placer presentationTk (créée dans la fonction) comme image de labelphoto
    labelphoto.configure (image = presentationTk)
    # la ligne ci-dessous permet d'éviter le ramasse-miettes : la réf est dans un objet externe à la fonction
    labelphoto.image = presentationTk

def enregistrement_de_la_valeur_de_montexte():
    """
    Permet de modifier la valeur affichée dans le label sous le curseur.
    Elle correspond alors à la valeur de pixellisation du curseur.
    On modifie variable valeurCurseur qui correspond à un StringVar.
    Aucun argument à transmettre.
    *
    La variable valeurCurseur contient la référence de l'objet StringVar du programme principal.
    La variable valeur2 contient la référence de l'objet IntVar qui stocke la valeur du Scale (curseur) nommé curseur2.
    Cela permettra de l'enregistrer à l'aide d'une autre fonction.
    """
    valeurCurseur.set(valeur2.get())

def pixellisation():
    """
    Permet de pixelliser l'image stockée en réduisant sa taille puis en l'agrandissant.
    Aucun argument à transmettre.
    *
    On utilise valeur2, un IntVar du programme principal qui fait stocke la valeur de pixellisation voulue.
    La variable presentation est un objet Img qui contient l'image à traiter.
    La variable valeurCurseur contient la référence de l'objet StringVar du programme principal.
    La variable valeur2 contient la référence de l'objet IntVar qui stocke la valeur du Scale (curseur) nommé curseur2.
    La variable imageStockage permet de garder en mémoire la nouvelle image Img pixellisée une fois qu'on sort de la fonction.
    La variable labelphoto fait référence à un objet de classe Label du programme principal.
    """
    # Permet de modifier la variable imageStockage depuis la fonction
    global imageStockage
    #enregistrement de valeur2 dans la variable x
    x = valeur2.get()
    #enregistrement de la largeur et de la hauteur de l'image dans des variables
    # http://pillow.readthedocs.io/en/4.2.x/reference/ImageTk.html
    larg = presentation.width
    haut = presentation.height
    #taille de la redimension dans une variables
    larg2 = int(larg/x)
    haut2 = int(haut/x)
    #redimension de l'image
    z = presentation.resize((larg2,haut2))
    z2 = z.resize((larg,haut))
    #affichage de l'image pixeliser
    presentationTk = ImageTk.PhotoImage(z2)
    labelphoto.configure (image = presentationTk)
    labelphoto.image = presentationTk
    imageStockage = z2

def sauvegarder() :
    """
    Permet de sauvarder l'image Img stockée dans imageStockage.
    Aucun argument à transmettre.
    *
    On stocke sous le nom 'image-pixellisee.jpg'
    """
    imageStockage.save("image-pixellisee.jpg")

# - - - - - - - - - - -

# PROGRAMME PRINCIPAL

# - - - - - - - - - - -

#creation d'une fenetre

fen_princ = Tk()

#code pour faire la variable de l'image et afficher le nom de l'image choisi

nomImage = StringVar()

monAffichage = Label(fen_princ, textvariable = nomImage)

monAffichage.pack()

#creation des boutons

Button(fen_princ, text="ouvrir image", command=ouverture_de_l_image).pack()

Button(fen_princ, text="Afficher variable", command=enregistrement_de_la_valeur_de_montexte).pack()

Button(fen_princ, text="pixelliser", command=pixellisation).pack()

Button(fen_princ, text="sauvegarder", command=sauvegarder).pack()

#creation d'une image objet

presentation=Img.new("RGB", (50,50) , (0,0,0) )

presentationTk= ImageTk.PhotoImage(presentation)

labelphoto = Label(fen_princ, image=presentationTk)

labelphoto.pack()

#creation d'un curseur

valeur2 = IntVar()

curseur2 = Scale(fen_princ, from_=0, to=50, variable=valeur2)

curseur2.pack()

# création d'un label montrant la valeur du curseur

valeurCurseur=IntVar()

valeurCurseur.set(0)

monaffichage = Label(fen_princ, textvariable=valeurCurseur, width=35)

monaffichage.pack()

#creation d'une variable de stockage

imageStockage=0

#fin du programme pour garder la fenetre ouverte

fen_princ.mainloop()
