
import math
import random
import copy
import numpy as np


class Player():
    def __init__(self, isFirst:bool):
        if isFirst:
            self.letter = 'X'
            self.oLetter = 'O'
        else: 
            self.letter = 'O'
            self.oLetter = 'X'

    def getAct(self, game):
        pass


class HumanPlayer(Player):
    def __init__(self, isFirst):
        super().__init__(isFirst)

    def getAct(self, game):
        valid_square = False
        val = None
        while not valid_square:
            square = input(self.letter + '\'s turn. Input move (0-9): ')
            try:
                val = int(square)
                if val not in game.getPosibleAct():
                    raise ValueError
                valid_square = True
            except ValueError:
                print('Invalid square. Try again.')
        return val


class AgentMinimax(Player):
    def __init__(self, isFirst):
        super().__init__(isFirst)
        self.isFirst = isFirst
        self.memory = {}


    def nbAlign(self, state:list) -> int:
        pass

    ### function evaluation 
    def utility(self, stateTerminal:list) -> int:
        winCol = [[0, 3, 6], 
                    [1, 4, 7],
                    [2, 5, 8]]
        winRow = [[0, 1, 2], 
                    [3, 4, 5], 
                    [6, 7, 8]]
        winDiag = [[0, 4, 8],
                    [2, 4, 6]]

        winState = [*winCol, *winRow, *winDiag]

        res = 0
        for idx in winState :
            if all([stateTerminal[i] == self.letter for i in idx]):
                res = 1
                break

            if all([stateTerminal[i] == self.oLetter for i in idx]):
                res = -1
                break
        return res 


    def termiTest(self, state:list) -> bool:
        if (any([s == ' ' for s in state])):
            winLostState = self.utility(state)
            if winLostState == 0:
                resul = False
            else:
                resul = True
        else:
            resul = True
        return resul

    def getPosibleAct(self, state:list) -> list:
        return [i for i, x in enumerate(state) if x == ' ']
    
    def _updateState(self, state: list,action: int, letter:str):
        nextState = copy.copy(state)
        nextState[action] = letter
        return nextState

    def maxVal(self, state:list) -> int:
        key = str(state)  + ' max'
        self.memory[key] = []

        if self.termiTest(state):
            u = self.utility(state)
            self.memory[key].append( ("LEAF",u))
            return u
        else:    
            v = -np.inf
            for a in self.getPosibleAct(state):
                nextState = self._updateState(state,a, self.letter)
                tmp = self.minVal(nextState)
                self.memory[key].append( (a,tmp) )
                v = max(v, tmp)

            return v

    def minVal(self, state:list) -> int:
        key = str(state)  + ' min'
        self.memory[key] = []

        if self.termiTest(state):
            u = self.utility(state)
            self.memory[key].append( ("LEAF" ,u))
            return u
        else:
            v = np.inf
            for a in self.getPosibleAct(state):
                nextState = self._updateState(state,a, self.oLetter)
                tmp = self.maxVal(nextState)
                self.memory[key].append( (a,tmp) )
                v = min(v, tmp)
            return v

    def minMaxDecision(self, state:list, verbose = True) -> int:
        #to get the best next moves.
        tmp = {}
        for a in self.getPosibleAct(state):
            nextState = copy.copy(state)
            nextState[a] = self.letter
            tmp[a] = self.minVal(nextState)
        if verbose:
            print(tmp)
        
        res = [key for key, value in tmp.items() if value == max(tmp.values())]
        return res

    def think(self, state:list) -> int:
        self.maxVal(state)


class AgentAlphaBeta(AgentMinimax):

    def maxVal(self, state:list, alpha: list, beta: list) -> int:
        a = alpha[0]; b = beta[0]
        
        key = str(state)  + ' max'
        self.memory[key] = []        

        if self.termiTest(state):
            u = self.utility(state)
            self.memory[key].append( ("LEAF",u))
            return u
        else:    
            v = -np.inf
            for act in self.getPosibleAct(state):
                nextState = self._updateState(state,act, self.letter)
                tmp = self.minVal(nextState, alpha, beta)

                self.memory[key].append( (act , tmp, alpha[0], beta[0]) )
                v = max(v, tmp)
                # alpha beta pruning
                if v > b:
                    return v
                else:
                    #update alpha
                    alpha[0]  = max(a,v)
            return v

    def minVal(self, state:list, alpha: int, beta: int) -> int:
        a = alpha[0]; b = beta[0]
        key = str(state)  + ' min'
        self.memory[key] = []

        if self.termiTest(state):
            u = self.utility(state)
            self.memory[key].append( ("LEAF" ,u))
            return u
        else:
            v = np.inf
            for act in self.getPosibleAct(state):
                nextState = self._updateState(state,act, self.oLetter)
                tmp = self.maxVal(nextState, alpha, beta)
                
                self.memory[key].append( (act , tmp, alpha[0], beta[0]) )
                v = min(v, tmp)
                # alpha beta pruning
                if v < a:
                    return v
                else:
                    #update beta
                    beta[0]  = min(b,v)


            return v

    def minMaxDecision(self, state:list, verbose = True) -> int:
        pass

    def think(self, state:list) -> int:
            self.maxVal(state, [-np.inf], [np.inf])

class AgentAlphaBetaOrdering(AgentAlphaBeta):
    def __init__(self, isFirst):
        super().__init__(isFirst)
        self.MovePreference = [*[0,2,6,8],4,*[1,3,5,7]]

    def getPosibleAct(self, state:list) -> list:
        return [i for i in self.MovePreference if state[i] == ' ']

#initState = [' ' for _ in range(9)]
initState = ['X', 'O', ' ',
             ' ', ' ', ' ',
             ' ', ' ', ' ',]

agent = AgentMinimax(True)
#agent = AgentAlphaBeta(True)
#agent = AgentAlphaBetaOrdering(True)

#agent.minMaxDecision(initState)
agent.think(initState)


print('Initial State: ' + str(initState))
print("-"*60)

print("Minimax/AlphaBeta Algorithm")
print("Visited " + str(len(agent.memory)) + " states")
print("Visited States - [Tree Depth] state - player: list of (possible action, value, (alpha, beta)):")
print("")

empty0 = str(initState).count("' '")
for k, v in agent.memory.items():
    emptyk = k.count("' '")
    if emptyk ==6:
        print("")
    print(" "*(empty0 - emptyk)*3 + "|." + "."*(emptyk)*3,
          "[" + str(emptyk) + "]", 
          #k, ':', v
          k.replace("'"," ").replace(",","."), ':', v
         )

# Comments
# see screenshot for more details
# AgentMinimax: visites 653 states
# values:
#[(2, 0), (3, 1), (4, 1), (5, 0), (6, 1), (7, 0), (8, 0)]


# Naive AgentAlphabeta: Visites only 477 states (73%)
# values (2 last values are alpha, beta)
#[(2, 0, 1, 0), (3, 1, 0, 0), (4, 1, 1, 0), (5, 0, 1, 0), (6, 1, 1, 0), (7, 0, 1, 0), (8, 0, 1, 0)]

# The values of AgentAlphabeta are identical to Minimax

# AgentAlphaBetaOrdering: Visites only 369 states (~56%)
# values (2 last values are alpha, beta)
 #[(2, 0, 1, 0), (6, 1, 0, 0), (8, 0, 1, 0), (4, 1, 1, 0), (3, 1, 1, 0), (5, 0, 1, 0), (7, 0, 1, 0)]
 
 