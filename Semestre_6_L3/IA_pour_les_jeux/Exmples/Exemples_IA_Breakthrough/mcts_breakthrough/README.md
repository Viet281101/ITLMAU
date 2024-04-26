
# Projet Jeu Breakthrough -- MCTS

Viet NGUYEN -- 20006303

## Executer le jeu

Pour lancer le jeu, il suffit de faire `make` dans le dossier du jeu.

## Lancer le jeu

Pour lancer le jeu, il suffit de faire `./mctsplayer` dans le dossier du jeu.
Puis, tapper la commande `newgame 8 8` pour commencer le jeu.
La commande `showboard` affiche le plateau du jeu.

## Jouer

Après avoir joué, il suffit de taper la commande `showboard` pour voir le plateau du jeu.
La commande `play <L0C0L1C1>`, par exemple: `play 2h3g` -> il va déplacer le pion de la case 2h vers la case 3g:
   a b c d e f g h 
 8 @ @ @ @ @ @ @ @ 
 7 @ @ @ @ @ @ @ @ 
 6 . . . . . . . . 
 5 . . . . . . . . 
 4 . . . . . . . . 
 3 . . . . . . o . 
 2 o o o o o o o . 
 1 o o o o o o o o 

Pour jouer avec mcts : `mctsmove` ou `genmove`

## Quitter

Lorsque le jeu est fini, il suffit de taper la commande `quit` pour quitter le jeu.

