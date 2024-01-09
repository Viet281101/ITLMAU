# by Viet NGUYEN 20006303


import random
import copy
from abc import ABC, abstractmethod

#Abstract Class
class AI(ABC):
    def __init__(self, name:str):
        self.name = name
        self.stateMemory = [[False, False, False, False]]
        self.strategy =  None
        self.complexity = None
        print("Agent " + self.name + " will play the game!")

    def getValideAct(self, state:list) -> list:
        lst = []
        # valide action 0 -> human passes wihout any thing
        actionTmp = copy.copy(state); actionTmp[0] = not actionTmp[0]
        lst.append(actionTmp)

        # find who are with human at the state
        thingsWithHuman = [i for i in range(1, 4) if state[i] == state[0]]
        # valide action : human pass with a thing 
        for i in thingsWithHuman:
            actionTmp = copy.copy(state)
            actionTmp[0] = not actionTmp[0]
            actionTmp[i] = not actionTmp[i]
            lst.append(actionTmp)

        return lst
        

    def getPosibleAct(self, lstActions: list) -> list:
        res = copy.copy(lstActions)
        
        for action in lstActions:
            actionTmp = dict(zip(['F', 'P', 'R', 'G'], action))
            
            if (actionTmp['P'] == actionTmp['G']) and (actionTmp['P'] != actionTmp['F']):
                res.remove(action)
                continue
            if (actionTmp['P'] == actionTmp['R']) and (actionTmp['P'] != actionTmp['F']):
                res.remove(action)
        
        # the agent cannot play an historical action 
        for action in self.stateMemory:
            if action in res:
                res.remove(action)        
        return res


    @abstractmethod
    def think(self, state: list):
        self.strategy = None

    @abstractmethod
    def play(self, state: list, graph:dict) -> list:
        pass


        
class AgentRandom(AI):
    def think(self, state: list) -> list:
        return None

    def play(self, state:list) -> list:
        valideActs = self.getValideAct(state)
        posActs = self.getPosibleAct(valideActs)

        if len(posActs) == 0:
            self.agentStatus = "Failed"
            print("Give up ! No posible solution !")
            action = 0
        else :                                    
            
            action = random.choice(posActs)

            self.stateMemory.append(action)
        if len(posActs) > 1:
            print("posAct :" + str(posActs))
            print("action :" + str(action))
        else:
            print("posAct/action :" + str(posActs))

        return action


class AgentBFS(AI):

    # rechLarg()
    def think(self, state: list, verbose = True) -> list:
        self.complexity = 0
        res = None
        
        # F = FileDEtats()
        # ajouter(e,F)
        graph = [(state, [state])]
        visited = []
        
        # tant que F non-vide
        while len(graph) > 0:
            # x = retirer un etat 
            node, path = graph.pop(0)
            visited.append(node)
            
            # y = filsSuivant(x)
            posActs = self.getPosibleAct(self.getValideAct(node))
            for action in posActs:
                self.complexity += 1 
                # the selected action is the next state of the environment
                if not all(action):
                    if action not in visited:
                        graph.append((action, path + [action]))
                else:
                    #if win
                    res = path + [action]

        self.strategy = res
        
        if verbose:
            print("Agent " + self.name + " starts thinking...")
            print("Agent's complexity: " + str(self.complexity))
            print("The game can be solved in " + str(len(self.strategy)-1) + " steps.")

    def play(self, state:list) -> list:
        if self.strategy is None:
            raise ValueError("The agent did not think about the game")
        else:
            idx = self.strategy.index(state)
            return(self.strategy[idx+1])
            

class AgentDFS(AI):
    # rechProf()
    def think(self, state: list, verbose = True) -> list:
        self.complexity = 0
        res = None
        # F = FileDEtats()
        # ajouter(e,F)
        graph = [(state, [state])]
        visited = []
        # tant que F non-vide
        while len(graph) > 0:
            # x = retirer un etat 
            node, path = graph.pop(0)
            visited.append(node)
            
            # y = filsSuivant(x)
            posActs = self.getPosibleAct(self.getValideAct(node))
            for action in posActs:
                self.complexity += 1 
                # the selected action is the next state of the environment
                if not all(action):
                    if action not in visited:
                        # Since we insert the first child to the first position in list, it will be the target for the next round search, resulting in a "recherche en profondeur" 
                        # it's an alternative to the recursive solution that we see in the course.
                        graph.insert(0, (action, path + [action]))
                else:
                    #if win
                    res = path + [action]

        self.strategy = res
        
        if verbose:
            print("Agent " + self.name + " starts thinking...")
            print("Agent " + self.name + " finishes thinking!")
            print("Agent's complexity: " + str(self.complexity))
            print("The game can be solved in " + str(len(self.strategy)-1) + " steps.")

    def play(self, state:list) -> list:
        if self.strategy is None:
            raise ValueError("The agent did not think about the game")
        else:
            idx = self.strategy.index(state)
            return(self.strategy[idx+1])

class AgentDFS2(AgentDFS):
    # algo vu dans le cour
    def think(self, state: list, verbose = True) -> list:
        self.complexity = 0
        self.visited = []
        self.strategy = self.rechProf(state,[state])

        if verbose:
            print("Agent " + self.name + " starts thinking...")
            print("Agent " + self.name + " finishes thinking!")
            print("Agent's complexity: " + str(self.complexity))
            print("The game can be solved in " + str(len(self.strategy)-1) + " steps.")

    def rechProf(self,state: list, path: list) -> list:

        posActs = self.getPosibleAct(self.getValideAct(state))
        self.visited.append(state)
        
        for action in posActs:
            self.complexity += 1 
            if not all(action):
                if action not in self.visited:
                # the selected action is the next state of the environment
                    path.append(action)
                    path = self.rechProf(action,path)
            else:
                path.append(action)
                break

            if all(path[-1]):
                break
        return(path)

