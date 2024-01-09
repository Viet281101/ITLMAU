# by Viet NGUYEN 20006303


from environement import Game
from agent import *

def testRandom():
	env = Game()
	agentR = AgentRandom("nva")

	agentR.think(env.states[-1])
	print("Start Playing:")
	while not env.exit:
		# print("Sample action = [True, False, True, False] or [T, F, T, F]")
		# env.inputAction()
		
		action = agentR.play(env.states[-1])
		env.update(action)
		# env._printStates()
		

def testBFS():
	env = Game()
	agentB = AgentBFS("nva")
	agentB.think(env.states[-1])
	print("Step to win (des etat visite):", agentB.strategy)

	print("Start Playing:")
	while not env.exit:
		action = agentB.play(env.states[-1])
		env.update(action)

def testDFS():
	env = Game()
	agentD = AgentDFS("nva")
	agentD.think(env.states[-1])
	print("Step to win (des etat visite):", agentD.strategy)

	print("Start Playing:")
	while not env.exit:
		action = agentD.play(env.states[-1])
		env.update(action)

def testDFS2():
	env = Game()
	agentD2 = AgentDFS2("nva")
	agentD2.think(env.states[-1])
	print("Step to win (des etat visite):", agentD2.strategy)
	agentD2.strategy

	print("Start Playing:")
	while not env.exit:
		action = agentD2.play(env.states[-1])
		env.update(action)


if __name__ == '__main__':
	print(" Test random search (recherche aleatoire): ")
	for i in range(3):
		testRandom()

	print("-------------------------------------------------------")
	print(" Test BFS (recherche largeur): ")
	testBFS()
	
	print("-------------------------------------------------------")
	print(" Test DFS (recherche profondeur) - Normal Tree: ")
	testDFS()
	
	print("-------------------------------------------------------")
	print(" Test DFS2 - recursive: ")
	testDFS2()
