

initial=[0,0,0,0]
buts=[[1,1,1,1]]
trace=True

interdits=[[F,P,R,G] for F in [0,1] for P in [0,1] for R in [0,1]
               for G in [0,1] if P!=F and (P==G or R==P)]

if trace:
    print('interdits :', interdits)

def successeurs(etat):
    fermier=etat[0]
    destination=1-fermier
    fermier_seul=etat.copy()
    fermier_seul[0]=destination
    candidats=[fermier_seul]
    for indice in range(1,len(etat)):
        if etat[indice]==fermier:
            candidat=etat.copy()
            candidat[0]=destination
            candidat[indice]=destination
            candidats.append(candidat)
    if trace:
        print('successeurs de', etat, ':', [candidat for candidat in candidats if candidat not in interdits])
    return [candidat for candidat in candidats if candidat not in interdits]


successeurs([1,1,1,0])

