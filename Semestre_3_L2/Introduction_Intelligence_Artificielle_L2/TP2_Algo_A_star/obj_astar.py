import math
import copy

class points_cardinaux:
    def __init__(self): # constructeur avec coordonnees
        self.N=(0, +1)
        self.NO=(-1, +1)
        self.O=(-1, 0)
        self.SO=(-1, -1)
        self.S=(0, -1)
        self.SE=(+1, -1)
        self.E=(+1, 0)
        self.NE=(+1, +1)

    def deplacements(self):
        return [getattr(self, pt_card) for pt_card in priorite]

class etat:
    """Classe definissant un etat (cellule) ayant pour proprietes :
    - coords : ses coordonnes (x, y)
    - prec : l'etat precedent
    - g : le cout mesure du chemin entre lui et l'etat initial
    - h : l'estimation de sa distance au but
    - f : son cout, somme des deux precedents
    et pour methodes
    - dist : une mesure de distance a un autre etat
    - acc : la methode de generation des etats accessibles
    
    - maj: update total distance
    - colonnes, lignes: distance by line, col
    - manhattan: sum of distance by line, col
    
    """

    def __init__(self, *args, prec=None, arrivee=None, **kwargs):
        self.coords = kwargs.get('coords')
        self.prec = prec
        if prec:
            self.g = prec.g+1
        else:
            self.g = 0
        if arrivee:
            self.h = self.dist(arrivee)
            self.arrivee = arrivee
        else:
            self.h = None

        if self.g and self.h:
            self.f = self.g+self.h
        else:
            self.f = None
            
    def __str__(self):
        return "Cellule de coordonnes: %s, nb de deplacements:%s, distance au but: %s, evaluation: %s " % (self.coords, self.g, self.h, self.f)

    def __repr__(self):
        return "(x,y):%s g:%s h:%s f:%s" % (self.coords, self.g, self.h, self.f)

    def maj(self, but):
        if self.prec:
            self.g = self.prec.g + 1
        else:
            self.g = 0
        self.h = self.dist(but)
        self.f = self.g + self.h

    def acc(self):
        deplacements = points_cardinaux().deplacements()
        x = self.coords[0]; y = self.coords[1]

        accessibles=[(x+mv[0], y+mv[1]) for mv in deplacements]
        acceptables=[etat(coords=ac, prec=self, arrivee=self.arrivee) for ac in accessibles
                      if (
                        (1<=ac[0]<=labyrinthe.largeur) and
                            (1<=ac[1]<=labyrinthe.hauteur) and 
                                ac not in [mur.coords for mur in labyrinthe.murs]
                         )
                    ]
        return acceptables


    def dist(self, etat):
        return self.manhattan(etat)

    def euclidean(self, etat):
        return ((self.coords[0]-etat.coords[0])**2+(self.coords[1]-etat.coords[1])**2)**(1/2)

    def manhattan(self, etat):
        return abs(self.coords[0]-etat.coords[0])+abs(self.coords[1]-etat.coords[1])

    def colonnes(self, etat):
        return abs(self.coords[0]-etat.coords[0])

    def lignes(self, etat):
        return abs(self.coords[1]-etat.coords[1])
        

class pile:
    """Classe permettant de stocker les etats a explorer, tries et permettant le pop"""
    # modified
    def __init__(self, but): # constructeur
        self.pile_content = []
        self.but = but
        
    def fifo(self, ajout):
    # ajout: is a new point
    # the function will insert the new point to assure the order accending of f values
    # # modified
        ajout.maj(self.but)
        for idx in range(len(self.pile_content)):
            if self.pile_content[idx].f > ajout.f:
                self.pile_content.insert(idx, ajout)
                return None
        self.pile_content.append(ajout)

class lab:
    """Classe premettant de stocker et d'afficher le labyrinthe"""

    def __init__(self, depart, arrivee, largeur, hauteur):
        self.depart = depart
        self.arrivee = arrivee
        self.largeur = largeur
        self.hauteur = hauteur

    murs=[etat(coords=(2, 5)), 
          etat(coords=(3, 2)), 
          etat(coords=(3, 3)), 
          etat(coords=(3, 5)), 
          etat(coords=(3, 6)), 
          etat(coords=(3, 7)), 
          etat(coords=(3, 8)), 
          etat(coords=(3, 9)),
          etat(coords=(4, 3)), 
          etat(coords=(5, 3)), 
          etat(coords=(5, 5)), 
          etat(coords=(5, 6)), 
          etat(coords=(6, 3)), 
          etat(coords=(6, 5)), 
          etat(coords=(6, 6)), 
          etat(coords=(6, 8)),
          etat(coords=(7, 8)), 
          etat(coords=(8, 2)), 
          etat(coords=(8, 3)), 
          etat(coords=(8, 4)), 
          etat(coords=(8, 8)), 
          etat(coords=(9, 4)), 
          etat(coords=(9, 8)), 
          etat(coords=(10, 4))]

def astar(lab):
    etat_init = lab.depart
    etat_but = lab.arrivee

    # initialization
    visite = [etat_init.coords]
    pile_obj = pile(etat_but)

    # while init
    etat = copy.copy(etat_init)
    etat.maj(etat_but)
    dist = etat.h
    while dist > 0:
        for e_prime in etat.acc():
            if e_prime.coords not in visite:
                pile_obj.fifo(e_prime)
                visite.append(e_prime.coords)

        # update next while step
        etat = pile_obj.pile_content.pop(0); dist = etat.h


    #reconstructing path
    path = [etat.coords]; e_prec = etat.prec
    while e_prec.prec is not None:
        path.insert(0,e_prec.coords)
        e_prec = e_prec.prec

    return (path, visite)

#----------------------------------------------------#
# initialization game
priorite = 'NOSE' # si on veut des diags : ['NE', 'NO', 'SO', 'SE'] 
but = etat(coords=(9, 3), arrivee = etat(coords=(9, 3)))

initial = etat(coords=(2, 8), arrivee=but)
# initial.maj(but)
# but.maj(but)
print('entree:', initial)
print('sortie:', but)

labyrinthe=lab(initial, but, 11, 10)
# pile=pile()

#----------------------------------------------------#
# new: run astar
print('#-----------------------------------------#')

path, visite = astar(labyrinthe)
print("Winning Path:")
print(path)

print("Visited Notes:")
print(visite)

#----------------------------------------------------#
"""
# print the object to test
access = initial.acc()
print ("entree Access:")
for a in access:
    print(a)

depart = points_cardinaux().deplacements()
print ("deplacements ", depart)
"""

