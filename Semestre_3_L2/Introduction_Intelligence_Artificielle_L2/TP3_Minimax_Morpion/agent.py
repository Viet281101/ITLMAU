
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


class Agent(Player):
    def __init__(self, isFirst):
        super().__init__(isFirst)


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


    def maxVal(self, state:list) -> int:
        if self.termiTest(state):
            return self.utility(state)
        else:    
            v = -np.inf
            for a in self.getPosibleAct(state):
                nextState = copy.copy(state)
                nextState[a] = self.letter
                v = max(v, self.minVal(nextState))
            return v



    def minVal(self, state:list) -> int:
        if self.termiTest(state):
            return self.utility(state)
        else:
            v = np.inf
            for a in self.getPosibleAct(state):
                nextState = copy.copy(state)
                nextState[a] = self.oLetter
                v = min(v, self.maxVal(nextState))
            # print(v)
            return v


    def minMaxDecision(self, state:list) -> int:
        tmp = {}
        for a in self.getPosibleAct(state):
            nextState = copy.copy(state)
            nextState[a] = self.letter
            tmp[a] = self.minVal(nextState)
        print(tmp)
        res = [key for key, value in tmp.items() if value == max(tmp.values())]
        return res



#initState = [' ' for _ in range(9)]
initState = ['X', 'O', ' ',
                ' ', 'O', ' ',
                ' ', ' ', ' ',]

agent = Agent(True)

# agent.minMaxDecision(initState)
print(initState)
print(agent.minMaxDecision(initState))






