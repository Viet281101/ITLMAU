/*Pour extraire les lignes du tableau*/
ex_lignes([], [], X, Y) :- maplist(reverse, X, Y).
ex_lignes([], Y, X, Z) :- not(Y = []), maplist(reverse, [Y | X], Z).
ex_lignes([X | Xs], ligne, acc, lignes) :- ground(X),
    (
        X = x ->
        ex_lignes(Xs, [], [ligne | acc], lignes)
    ;
    ex_lignes(Xs, [X], [ligne | acc], lignes)
    ).
ex_lignes([X | Xs], ligne, acc, lignes) :- var(X), ex_lignes(Xs, [X | ligne], acc, lignes).

/*Pour normaliser les lignes*/
changer_ligne([], X, Y) :- reverse(X, Y).
changer_ligne([X | Xs], Ys, Zs) :- ground(X), X = x/Y, changer_ligne(Xs, [Y | Ys], Zs).
changer_ligne([X | Xs], Ys, Zs) :-
    var(X),
    changer_ligne(Xs, [X | Ys], Zs).
changer_ligne(X, Y) :- changer_ligne(X, [], Y).

retourne([], Ys, Zs) :- reverse(Ys, Zs).
retourne([X | Xs], Ys, Zs) :-(var(X), ! ; X = x),retourne(Xs, [X | Ys], Zs).
retourne([X | Xs], Ys, Zs) :- ground(X),X = N/Y,retourne(Xs, [Y/N | Ys], Zs).
retourne(X, Y) :- retourne(X, [], Y).

mrg([], X, X).
mrg([X | Xs], Y, Z) :-mrg(Xs, [X | Y], Z).

changer([], X, X).
changer([E | Es], acc, res) :-
    (
        changer_ligne(E, NE) ->
        changer(Es, [NE | acc], res)
    ;
    changer(Es, acc, res)
    ).

lignes([], X, X).
lignes([ligne | lignes], acc, res) :-
    ex_lignes(ligne, [], [], extrait),
    (
        changer(extrait, [], change) ->
        (
            mrg(change, acc, Macc),
            lignes(lignes, Macc, res)
        )
    ;
    lignes(lignes, acc, res)
    ).

resoudre_somme([]).
resoudre_somme([somme | sommations]) :- distinct(sommations),somme(sommations, =, somme).

resoudre_sommes([]).
resoudre_sommes([X | Xs]) :- resoudre_somme(X), resoudre_sommes(Xs).

resoudre(tableau) :-
    term_variables(tableau, variables), lignes(tableau, [], lignes),
    change_pos(tableau, Ttableau), maplist(retourne, Ttableau, Rcolonne), lignes(Rcolonne, [], colonne), resoudre_sommes(lignes), resoudre_sommes(colonne), label(variables).

tableau([
    [x  , 6/x, 6/x, x  , x  , 3/x, 4/x],
    [x/4, A  , B  , x  , 6/4, C  , D  ],
    [x/7, E  , F  , 7/6, H  , J  , K  ],
    [x  , x/7, L  , M  , N  , 6/x, x  ],
    [x  , 6/x, 4/6, O  , P  , Q  , 7/x],
    [x/7, R  , S  , T  , x/6, U  , V  ],
    [x/5, W  , X  , x  , x/4, Y  , Z  ]
]).

kakuro :-
    tableau(tableau),
    resoudre(tableau),
    format('bingo', [tableau]).
