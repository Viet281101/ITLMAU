go:- var=[X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16], 
     var :: 1..9, mot([X1,X2],5), 
     mot([X3,X4,X5,X6],17),
     mot([X7,X8],6),
     mot([X9,X10],4),
     mot([X11,X12,X13,X14],10), 
     mot([X10,X14],3), 
     mot([X1,X4,X8,X11],11),
     mot([X2,X5],4),
     mot([X3,X7],14),
     mot([X6,X9,X13,X16],10),
     mot([X10,X14],3),
     mot([X12,X15],3),
     labeling(var), 
     writeln(var).
mot(L,somme):- somme(L), diff(L).


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
resoudre_somme([somme | sommations]) :- tout_distinct(sommations),somme(sommations, =, somme).

resoudre_sommes([]).
resoudre_sommes([X | Xs]) :- resoudre_somme(X), resoudre_sommes(Xs).

resoudre(tableau) :-
    term_variables(tableau, variables),
    lignes(tableau, [], lignes),
    change_pos(tableau, Ttableau),
    maplist(retourne, Ttableau, Rcolonne),
    lignes(Rcolonne, [], colonne),
    resoudre_sommes(lignes),
    resoudre_sommes(colonne),
    label(variables).

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
    format('~w~n', [tableau]).



///////////////////////////////////////

nbr(X) :- member(X, [1,2,3,4,5,6,7,8,9]).

diff([]).
diff([L|Ls]) :- not(member(L,Ls)), diff(Ls).

remplir([A,B,C,E,F,G,J,K,L,N,O,P]) :- nbr(A), nbr(B), nbr(C), nbr(E), nbr(F), 
    nbr(G), nbr(J), nbr(K), nbr(L), nbr(N), nbr(O), nbr(P), diff([A,B,C,E,F,G,J,K,L,N,O,P]).

somme([],0).
somme([Head|Tail], somme):-
    somme(Tail, somme1),
    somme is Head+somme1.

kakuro(var):-
    var=[A,B,C,E,F,G,J,K,L,N,O,P],
    var ins 1..9,
    mot([A,B,C],24), 
    mot([B,F,J,N],26),
    mot([C,G,K,O],15), 
    mot([E,F,G],11),
    mot([A,E],17),
    mot([J,K,L],22),
    mot([N,O,P],14),   
    mot([L,P],13),
    writeln(var).

mot(L,somme):-
    labeling([],L),
    diff(L),
    somme(L,somme).

tableau([
    [x   , 17/x, 26/x, 15/x, x   ],
    [x/24, A   , B   , C   , x   ],
    [x/11, E   , F   , G   , 13/x],
    [x   , x/22, J   , K   , L   ],
    [x   , x/14, N   , O   , P   ]
]).

kakuro :-
    tableau(tableau),
    remplir(tableau),
    somme(tableau),
    mot(tableau).