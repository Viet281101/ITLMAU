
# TP1 prodruire un fichier XML et un fichier XSL

## Problème n°1 - du non structuré au structuré... accessible pour l'humain

La langue est un contenu **non structuré a priori**, OR la machine a besoin de contenu structuré. Cette structure peut par-exemple prendre la forme de fichiers XML, correspondant à une structure hiérarchique enrichie de vos informations.

Problème : cela devient illisible pour un humain (voir les fichiers XML bruts)
=> on utilise donc des outils de mise en forme afin de retrouver l'accès à l'information, voire de l'enrichir. En l'occurrence on utilise le langage XSL.



En vous inspirant des exemples vus en cours, créez sur le sujet de votre choix :

- un **fichier XML** contenant des données organisées de manières hiérarchiques (au moins trois niveaux de profondeur), incluant des éléments contenant eux-même plusieurs éléments, et des attributs bien choisis.

- un **fichier XSL** contenant une feuille de style permettant la transformation au format HTML de votre fichier xml. Votre fichier XSL doit inclure les éléments vus dans les exemples montrés en cours : <<xsl:template>>, <<xsl:value-of>>, <<xsl:for-each>>, <<xsl:sort>>, <<xsl:choose>>. Vous devez utiliser au moins 2 fois l'élément <<xsl:template>>.


À noter :

    Vous pouvez ajouter du HTML directement dans votre fichier (si vous voulez faire des visualisations par exemple)

    Pour voir le résultat en sortie dans un fichier html, vous pouvez entrez la ligne de commande suivante (mac) : 
    xsltproc nom_de_fichier.xml nom_de_fichier.xsl -o nom_de_fichier.html
    (doc pour les curieux.ses : http://xmlsoft.org/xslt/xsltproc.html)

    Tous les étudiants doivent rendre le TP avant le 08/02 à 18h : 4 rendus seront tirés au sort la semaine prochaine pour être évalués et seront corrigés et commentés au début du TP de la semaine prochaine. Vous devez tous et toutes être prêt.es à répondre à des questions sur votre rendu qui montra être montré en cours.


Exemples du cours :

    transcription.xsl
    transcription.xml
    pokedex.xml
    pokedex.xsl

Liens : 

    https://www.w3schools.com/xml/xsl_intro.asp
    cas d'utilisation du langage XML chez Amazon

    Icône Dossier 