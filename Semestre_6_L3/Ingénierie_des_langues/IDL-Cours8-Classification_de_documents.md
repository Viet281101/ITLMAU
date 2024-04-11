# idl_15 Similarité entre documents - représentation vectorielle

:::info
Objectif : calculer un taux de similarité entre deux documents
:::

- “À quel point ces deux textes se ressemblent-ils ?”
- “À quel point parlent-ils de la même chose ?”
- “À quel point décrivent-ils des objets semblables ?”

![introduction_représentation_sémantique_page-0002](https://hackmd.io/_uploads/BkKjN-n1C.jpg)
![introduction_représentation_sémantique_page-0003](https://hackmd.io/_uploads/B1g-T4Z2kA.jpg)
![introduction_représentation_sémantique_page-0004](https://hackmd.io/_uploads/Sybb6NWhJ0.jpg)

![Capture d’écran du 2024-04-04 13-04-01](https://hackmd.io/_uploads/r1GNt-2yA.png)


![introduction_représentation_sémantique_page-0005](https://hackmd.io/_uploads/SklZp4-nJC.jpg)


![introduction_représentation_sémantique_page-0006](https://hackmd.io/_uploads/r1lbp4WnyR.jpg)
![introduction_représentation_sémantique_page-0007](https://hackmd.io/_uploads/r1xWpVW2kA.jpg)
![introduction_représentation_sémantique_page-0008](https://hackmd.io/_uploads/BkeZpVW2kA.jpg)
![introduction_représentation_sémantique_page-0009](https://hackmd.io/_uploads/B1ZT4-hkC.jpg)

:question: Votre opinion sur ces systèmes ?


![introduction_représentation_sémantique_page-0011](https://hackmd.io/_uploads/H1b-TNW3J0.jpg)
![introduction_représentation_sémantique_page-0012](https://hackmd.io/_uploads/rygTV-n10.jpg)
![introduction_représentation_sémantique_page-0013](https://hackmd.io/_uploads/HJ-ZpVZnJR.jpg)
![introduction_représentation_sémantique_page-0014](https://hackmd.io/_uploads/BJWpNW3JR.jpg)
![introduction_représentation_sémantique_page-0015](https://hackmd.io/_uploads/Bkm-6V-21R.jpg)
![introduction_représentation_sémantique_page-0016](https://hackmd.io/_uploads/rkbpV-hJC.jpg)
![introduction_représentation_sémantique_page-0017](https://hackmd.io/_uploads/r1WpEZ3y0.jpg)
![introduction_représentation_sémantique_page-0018](https://hackmd.io/_uploads/S17-pEZ3kA.jpg)

![introduction_représentation_sémantique_page-0020](https://hackmd.io/_uploads/r1G-6VZnkC.jpg)
![introduction_représentation_sémantique_page-0021](https://hackmd.io/_uploads/HJMb6Vb2J0.jpg)
![introduction_représentation_sémantique_page-0022](https://hackmd.io/_uploads/HJWpNZn10.jpg)
![introduction_représentation_sémantique_page-0023](https://hackmd.io/_uploads/HkEbTNbnyR.jpg)
![introduction_représentation_sémantique_page-0024](https://hackmd.io/_uploads/r1zbpNWn1A.jpg)
![introduction_représentation_sémantique_page-0025](https://hackmd.io/_uploads/BJW-pE-2kC.jpg)
![introduction_représentation_sémantique_page-0026](https://hackmd.io/_uploads/HymbpVZhyC.jpg)
![introduction_représentation_sémantique_page-0027](https://hackmd.io/_uploads/SJQZaV-3J0.jpg)

![introduction_représentation_sémantique_page-0028](https://hackmd.io/_uploads/B1WZpNZ3J0.jpg)


![introduction_représentation_sémantique_page-0029](https://hackmd.io/_uploads/H1b6VW3JC.jpg)
### La similarité de Jaccard 
Intersection over Union : 

![image](https://hackmd.io/_uploads/rkRVAAjkR.png =300x)
([source](https://pyimagesearch.com/2016/11/07/intersection-over-union-iou-for-object-detection/))

Exemple :
texte 1 = ”Lundi j’ai cours de bases de données, mardi de programmation, jeudi de sémantique : je n’ai plus le temps pour faire du sport.”
texte 2 = “Qu’est-ce que la programmation ? La programmation est une discipline qui demande temps concentration et vigilance.”
texte 3 = ”Le karaté est un art martial qui demande respect discipline concentration et connaissance de soi.”

![image](https://hackmd.io/_uploads/SJpJkkn1R.png)

- plus les textes ont des mots en commun, plus l'union est faible et l'intersection importante.

similarite Jaccard(texte 1, texte 2) = $2/28$ = 0.07
similarite Jaccard(texte 1, texte 3) = $1/33$ = 0.03
similarite Jaccard(texte 2, texte 3) = $6/20$ = 0.30

:question: Quelles sont les limites de cette méthode ?

:::spoiler
2 limites principales : 
- sensibilité à la taille des documents (deux petits documents peuvent avoir une distance très faible)
- ne prend pas en compte la fréquence des mots eux-mêmes dans un document : 2 documents qui ont 1 mot en commun auront la même distance que ce mot apparaîsse 1 fois dans chaque document ou 100 fois
:::

![introduction_représentation_sémantique_page-0030](https://hackmd.io/_uploads/Hk-WpN-3kC.jpg)

Représentation vectorielle 
![image](https://hackmd.io/_uploads/HkIHPghyC.png)


![introduction_représentation_sémantique_page-0031](https://hackmd.io/_uploads/rk7Z6NZ2JC.jpg)

![introduction_représentation_sémantique_page-0032](https://hackmd.io/_uploads/HkM-pV-nJR.jpg)

![introduction_représentation_sémantique_page-0033](https://hackmd.io/_uploads/HJX-TNW2JC.jpg)
![introduction_représentation_sémantique_page-0034](https://hackmd.io/_uploads/Hk-ba4-2yA.jpg)
![introduction_représentation_sémantique_page-0035](https://hackmd.io/_uploads/ryzWp4bhyR.jpg)
![introduction_représentation_sémantique_page-0036](https://hackmd.io/_uploads/SJlWpEW3JA.jpg)
![introduction_représentation_sémantique_page-0037](https://hackmd.io/_uploads/SJ4-pEb2JR.jpg)
![introduction_représentation_sémantique_page-0040](https://hackmd.io/_uploads/SJ-WaEW31R.jpg)




## TF/IDF
Hypothèses linguistiques sous-jacentes :
- Tous les mots n’ont pas la même importance dans un texte (plus un mot est fréquent plus il est important ?)
- Les mots les moins fréquents à l’échelle du corpus sont plus discriminants.

TF : Term Frequency (d'autant plus élevé que le terme est fréquent)
IDF : Inverse Document Frequency (d'autant plus élevé que le terme est présent dans *peu de textes*)
ex : classer des personnalités par biographies
- quels sont les mots qui vont avoir un TF fort ?
- quels sont les mots qui vont avoir un IDF faible ?


Exemple : 
“0 = Simple example with Cats and Mouse ”
“1 = Another simple example with dogs and cats ”
”2 = Another simple example with mouse and cheese ”
Pour chaque phrase, on calcule TF et IDF **pour l’ensemble des mots du corpus**
⇒ on obtient des vecteurs ==de même taille== pour tous les documents (ici, des phrases)

![image](https://hackmd.io/_uploads/B1alwgh10.png)

