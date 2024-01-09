import numpy as np

def printState(state:list) -> np.array:
    res = np.array(state).reshape((3,3))
    print(res)
    
    
input =    ['X', 'O', 'X', 'O', 'X', 'X', 'O', ' ', ' ']
printState(input)

"""
def changeList(l:list):
    l[0] = 1
    
l = ['a','b','c']
print(l)
changeList(l)
print(l)
"""