
/*
Exo1:
1) - Arbres binaire étiqueté
    - arbre equilibre (pour chaque noeud ses deux sous-arbre on la meme hauteur à 1prés)
    - arbre de recherche (pour chaque noeud ses descendant à gauche at des étiqueté strictement inferieurs
                            pour chaque noeud ses descendant à droit at des étiqueté strictement supérieurs)

2) Arbre A


Exo2:
1) la premier arbre
2)       -->    4
              /   \
            4       9
           / \       \
          2   6       10
         / \  |
        1  3  5
3)              

                x            -- Rotation droite y -->     x       -- Rotation gauche x -->      z  
              /   \                                     /   \                                 /   \
            A       y                                  A     z                               x     y
                   / \                                      / \                             / \   / \
                 z    p                                    B   y                           A   B  C  D
                / \                                           / \
               B   C                                         C   D
    

4)


Exo3:
              30
            /    \
          17      37
          0       2
        /  \     /  \
       N    N   33   40
                1     0
               / \   / \
             32   N  N  N


              30
            /    \
          17      33
          0       2
        /  \     /  \
       N    N   32   37
                0     1
               / \   / \
              N   N  N  40
                         0   


-->           33
               2
            /    \
          30      37
          1       1
        /  \     /  \
       17   32   N   40
        0    0        1
                     /  \
                    N    N 

*/
