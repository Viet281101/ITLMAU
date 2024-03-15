# IDL 10 : Construction d'un HMM pour l'étiquetage morphosyntaxique automatique

# Exercice 0


```python
class HMM:
    def __init__(self, initial_prob, transition_prob, emission_prob):
        # Initialisation des probabilités
        self.initial_prob = initial_prob
        self.transition_prob = transition_prob
        self.emission_prob = emission_prob

    def initial(self, tag):
        # Retourne la probabilité initiale pour une étiquette
        return self.initial_prob.get(tag, 0.0)

    def transition(self, tag_p, tag_c):
        # Retourne la probabilité de transition d'une étiquette à une autre
        if tag_p in self.transition_prob and tag_c in self.transition_prob[tag_p]:
            return self.transition_prob[tag_p][tag_c]
        else:
            return 0.0

    def emission(self, tag, token):
        # Retourne la probabilité d'émission d'un token étant donné une étiquette
        if tag in self.emission_prob and token in self.emission_prob[tag]:
            return self.emission_prob[tag][token]
        else:
            return 0.0

```


```python
initial_prob = {'Noun': 0.3, 'Verb': 0.7}
transition_prob = {
    'Noun': {'Noun': 0.1, 'Verb': 0.9},
    'Verb': {'Noun': 0.8, 'Verb': 0.2},
}
emission_prob = {
    'Noun': {'cat': 0.5, 'dog': 0.5},
    'Verb': {'eats': 0.5, 'sleeps': 0.5},
}
```


```python
hmm = HMM(initial_prob, transition_prob, emission_prob)
```


```python
print(hmm.initial('Noun'))  # Devrait afficher 0.3
print(hmm.transition('Noun', 'Verb'))  # Devrait afficher 0.9
print(hmm.emission('Noun', 'cat'))  # Devrait afficher 0.5
```

    0.3
    0.9
    0.5


# Exercice 1 : écrire l'algorithme de décodage : l'algorithme de Viterbi


```python
exo1_initial = {"DET": 1.0}

exo1_transition = {
	"ADJ": {"NOUN": 1.0},
	"CLO": {"VERB": 1.0},
	"CLS": {"VERB": 1.0},
	"DET": {"NOUN": 0.8, "ADJ": 0.2},
	"NOUN": {"CLO": 0.5, "VERB": 0.5},
	"VERB": {"DET": 1.0}
}

exo1_emission = {
	"ADJ" : {"belle": 1.0},
	"DET" : {"le": 0.6, "la": 0.4},
	"NOUN": {"belle": 0.1, "porte": 0.8, "voile": 0.1},
	"VERB": {"porte": 0.6, "voile": 0.4},
	"CLO" : {"le": 1.0}
}
```


```python
exo1_hmm = HMM(exo1_initial, exo1_transition, exo1_emission)

assert exo1_hmm.initial("DET") == 1, exo1_hmm.initial("DET")
assert exo1_hmm.initial("ADJ") == 0, exo1_hmm.initial("ADJ")

assert exo1_hmm.transition("DET", "ADJ") == 0.2, exo1_hmm.transition("DET", "ADJ")
assert exo1_hmm.transition("DET", "NOUN") == 0.8, exo1_hmm.transition("DET", "NOUN")
assert exo1_hmm.transition("DET", "VERB") == 0.0, exo1_hmm.transition("DET", "VERB")

assert exo1_hmm.emission("DET", "le") == 0.6, exo1_hmm.emission("DET", "le")
assert exo1_hmm.emission("DET", "la") == 0.4, exo1_hmm.emission("DET", "la")
assert exo1_hmm.emission("DET", "les") == 0.0, exo1_hmm.emission("DET", "les")
```


```python
print("Probabilité initiale de 'DET':", exo1_hmm.initial("DET"))
print("Probabilité de transition de 'DET' vers 'ADJ':", exo1_hmm.transition("DET", "ADJ"))
print("Probabilité d'émission de 'le' sachant 'DET':", exo1_hmm.emission("DET", "le"))
```

    Probabilité initiale de 'DET': 1.0
    Probabilité de transition de 'DET' vers 'ADJ': 0.2
    Probabilité d'émission de 'le' sachant 'DET': 0.6


### a. Calculez, pour chaque étiquette E, la probabilité de "la" sachant E.


```python
def initials(hmm, token):
    initial_probs = {}
    for tag in hmm.emission_prob:
        prob = hmm.initial(tag) * hmm.emission(tag, token)
        initial_probs[tag] = {'probabilité': prob, 'depuis': None}
    return initial_probs

assert initials(exo1_hmm, "la") == {
    'ADJ': {'probabilité': 0.0, 'depuis': None},
    'CLO': {'probabilité': 0.0, 'depuis': None},
    'DET': {'probabilité': 0.4, 'depuis': None},
    'NOUN': {'probabilité': 0.0, 'depuis': None},
    'VERB': {'probabilité': 0.0, 'depuis': None}
}, initials(exo1_hmm, "la")
```


```python
resultat_initials = initials(exo1_hmm, "la")

print(resultat_initials)
```

    {'ADJ': {'probabilité': 0.0, 'depuis': None}, 'DET': {'probabilité': 0.4, 'depuis': None}, 'NOUN': {'probabilité': 0.0, 'depuis': None}, 'VERB': {'probabilité': 0.0, 'depuis': None}, 'CLO': {'probabilité': 0.0, 'depuis': None}}


### b. Calculez la meilleure transition vers l'étiquette `ADJ`


```python
def best_transition_to(hmm, probas_preced, etiquette, token):
    meilleure_prob = 0
    meilleure_etiquette = None
    for etiqu_prec, val in probas_preced.items():

        prob_transition = hmm.transition(etiqu_prec, etiquette)

        prob_totale = prob_transition * val['probabilité']

        if prob_totale > meilleure_prob:
            meilleure_prob = prob_totale
            meilleure_etiquette = etiqu_prec
    meilleure_prob *= hmm.emission(etiquette, token)
    return {'probabilité': meilleure_prob, 'depuis': meilleure_etiquette}

avant = initials(exo1_hmm, "la")
assert (
    best_transition_to(exo1_hmm, avant, "ADJ", "belle") == {'probabilité': 0.08000000000000002, 'depuis': 'DET'}
), best_transition_to(exo1_hmm, avant, "ADJ", "belle")
```


```python
resultat_transition = best_transition_to(exo1_hmm, avant, "ADJ", "belle")

print(resultat_transition)
```

    {'probabilité': 0.08000000000000002, 'depuis': 'DET'}


### c. Calculez la meilleure transition vers toutes les étiquettes


```python
def best_transitions(hmm, probas_preced, token):
    meilleures_transitions = {}
    for etiquette in hmm.emission_prob:
        meilleure_prob = 0
        meilleure_etiquette_prec = None
        for etiqu_prec, val in probas_preced.items():
            prob_transition = hmm.transition(etiqu_prec, etiquette)
            prob_totale = prob_transition * val['probabilité']
            if prob_totale > meilleure_prob:
                meilleure_prob = prob_totale
                meilleure_etiquette_prec = etiqu_prec

        meilleure_prob *= hmm.emission(etiquette, token)
        meilleures_transitions[etiquette] = {'probabilité': meilleure_prob, 'depuis': meilleure_etiquette_prec}
    return meilleures_transitions

avant = initials(exo1_hmm, "la")
assert best_transitions(exo1_hmm, avant, "belle") == {
    'ADJ': {'probabilité': 0.08000000000000002, 'depuis': 'DET'},
    'CLO': {'probabilité': 0.0, 'depuis': None},
    'DET': {'probabilité': 0.0, 'depuis': None},
    'NOUN': {'probabilité': 0.03200000000000001, 'depuis': 'DET'},
    'VERB': {'probabilité': 0.0, 'depuis': None}
}, best_transitions(exo1_hmm, avant, "belle")
```


```python
resultats_transitions = best_transitions(exo1_hmm, avant, "belle")

print(resultats_transitions)
```

    {'ADJ': {'probabilité': 0.08000000000000002, 'depuis': 'DET'}, 'DET': {'probabilité': 0.0, 'depuis': None}, 'NOUN': {'probabilité': 0.03200000000000001, 'depuis': 'DET'}, 'VERB': {'probabilité': 0.0, 'depuis': None}, 'CLO': {'probabilité': 0.0, 'depuis': None}}


### d. Construire la matrice de Viterbi


```python
def viterbi_matrix(hmm, words):
    viterbi = [initials(hmm, words[0])]

    for word in words[1:]:
        current_probs = best_transitions(hmm, viterbi[-1], word)
        viterbi.append(current_probs)

    return viterbi
```


```python
def non_zeroes(d):
    return {tag: value for tag, value in d.items() if value["probabilité"] != 0}
```


```python
words = ["la", "belle", "porte", "le", "voile"]
```


```python
matrix = viterbi_matrix(exo1_hmm, words)

assert non_zeroes(matrix[0]) == {'DET': {'probabilité': 0.4, 'depuis': None}}, non_zeroes(matrix[0])
assert non_zeroes(matrix[1]) == {'ADJ': {'probabilité': 0.08000000000000002, 'depuis': 'DET'}, 'NOUN': {'probabilité': 0.03200000000000001, 'depuis': 'DET'}}, non_zeroes(matrix[1])
assert non_zeroes(matrix[2]) == {'NOUN': {'probabilité': 0.06400000000000002, 'depuis': 'ADJ'}, 'VERB': {'probabilité': 0.009600000000000003, 'depuis': 'NOUN'}}, non_zeroes(matrix[2])
assert non_zeroes(matrix[3]) == {'CLO': {'probabilité': 0.03200000000000001, 'depuis': 'NOUN'}, 'DET': {'probabilité': 0.005760000000000001, 'depuis': 'VERB'}}, non_zeroes(matrix[3])
assert non_zeroes(matrix[4]) == {'NOUN': {'probabilité': 0.00046080000000000014, 'depuis': 'DET'}, 'VERB': {'probabilité': 0.012800000000000004, 'depuis': 'CLO'}}, non_zeroes(matrix[4])
```


```python
for i, word_probs in enumerate(matrix):
    print(f"Mot '{words[i]}':")
    for tag, info in non_zeroes(word_probs).items():
        print(f"  {tag}: Probabilité = {info['probabilité']}, Depuis = {info['depuis']}")
    print()
```

    Mot 'la':
      DET: Probabilité = 0.4, Depuis = None
    
    Mot 'belle':
      ADJ: Probabilité = 0.08000000000000002, Depuis = DET
      NOUN: Probabilité = 0.03200000000000001, Depuis = DET
    
    Mot 'porte':
      NOUN: Probabilité = 0.06400000000000002, Depuis = ADJ
      VERB: Probabilité = 0.009600000000000003, Depuis = NOUN
    
    Mot 'le':
      DET: Probabilité = 0.005760000000000001, Depuis = VERB
      CLO: Probabilité = 0.03200000000000001, Depuis = NOUN
    
    Mot 'voile':
      NOUN: Probabilité = 0.00046080000000000014, Depuis = DET
      VERB: Probabilité = 0.012800000000000004, Depuis = CLO
    


### e. Reconstruire la séquence


```python
def viterbi(hmm, sentence):
    matrix = viterbi_matrix(hmm, sentence)

    last_word_probs = matrix[-1]
    max_prob = 0
    max_tag = None
    for tag, info in last_word_probs.items():
        if info["probabilité"] > max_prob:
            max_prob = info["probabilité"]
            max_tag = tag

    sequence = [max_tag]
    for i in range(len(sentence) - 2, -1, -1):
        sequence.insert(0, matrix[i + 1][sequence[0]]['depuis'])

    return sequence, max_prob

tags, prob = viterbi(exo1_hmm, ["la", "belle", "porte", "le", "voile"])
assert tags == ['DET', 'ADJ', 'NOUN', 'CLO', 'VERB'], tags
assert prob == 0.012800000000000004, prob
```


```python
tags, prob = viterbi(exo1_hmm, ["la", "belle", "porte", "le", "voile"])

print("Séquence d'étiquettes la plus probable :", tags)
print("Probabilité de cette séquence :", prob)
```

    Séquence d'étiquettes la plus probable : ['DET', 'ADJ', 'NOUN', 'CLO', 'VERB']
    Probabilité de cette séquence : 0.012800000000000004




