# by Viet NGUYEN 20006303


class Game:
	def __init__(self):
		# river bank A & B
		# objective: passing all actors from A to B
		self.gameOver = False
		self.exit = False
		# postion: 
		# --- False = in bank A
		# --- True = in bank B
		
		# init position:
		# [F, P, R, G] = [False, False, False, False] 
		# initially, all actors are in bank A
		self.actors = ['F', 'P', 'R', 'G']
		print("Actors' position: " + str(self.actors))
		self.states = [[False, False, False, False]]
		self.currentAction = None

	#----------------------------------#
	# input function
	# convert string to bool:
	def strToBool(self, l: list)-> list:
		res = [None]*len(l)

		for i,s in enumerate(l):
			if (s == "True") or (s == "T") or (s == "t"):
				res[i] = True

			if (s == "False") or (s == "F") or (s == "f"):
				res[i] = False
		return res


	def strToList(self, s:str) -> list:
		if s[0] == '[' and s[-1] == ']':
			if s[1] == '[' and s[-2] == ']':
				res = None
			else:
				res = self.strToBool(s[1:-1].replace(" ","").split(','))

		else:
			res = None
			print("Input a list !")

		return res


	def inputAction(self):
		self.currentAction = None
		while self.currentAction is None:
			self.currentAction = self.strToList(str(input("Input action : ")))
		
	def _validateTypeAction(self, action) -> bool:
		res = True
		if action != 0:
			if not isinstance(action, list): 
				res = False
			else:
				if len(action) != 4:	
					res = False
				if any([not isinstance(a,bool) for a in action]):
					res = False
		return(res)

	#----------------------------------#
	# environement function

	def validate(self, action: list) -> bool:
		res = False; humanValide = False; animalSlot = 0
		if not self._validateTypeAction(action):
			print("Invalid action type")
			self.inputAction()
		else:
			# human always move
			humanValide = action[0] != self.states[-1][0]
			
			if humanValide:
				# total number of animals' moves can be only 0 or 1
				animalSlot = sum([action[i] != self.states[-1][i] for i in range(1, 4)])
				res = animalSlot < 2
			else:
				res = False
		
		return( (res, humanValide, animalSlot) )
	
	# def reset(self):
	# 	self.gameOver = False
	# 	self.exit = False
	# 	self.actors = ['F', 'P', 'R', 'G']
	# 	self.states = [[False, False, False, False]]
	# 	self.currentAction = None

	def _printStates(self):
		for s in self.states:
			print(s)

	def checkGameOver(self):
		lastState = dict(zip(self.actors, self.states[-1]))

		if (lastState['P'] == lastState['G']) and (lastState['P'] != lastState['F']):
			self.gameOver = True; self.exit = True 
			print("GAME OVER ! The Chicken is eating the grain !")

		if (lastState['P'] == lastState['R']) and (lastState['P'] != lastState['F']):
			self.gameOver = True; self.exit = True 
			print("GAME OVER ! The Fox is eating the chicken !")

	

	def checkWin(self):
		if all(self.states[-1]):
			print("You win after " + str(len(self.states)-1) + " steps")
			self.exit = True			

	def update(self, action = None):
		if action is None:
			action = self.currentAction
		elif (action == 0):
			print("You gave up the game after " + str(len(self.states)) + " steps !")
			self.gameOver = True
			self.exit = True

		else:

			isValide, isHUmanValide, animalSlot = self.validate(action)

			if isValide:
				self.states.append(action)
				self.checkGameOver()
			elif not isHUmanValide:
				print("Invalid human action! Human is not moving!")
				self.inputAction()
			else:
				print("Invalid animal action! Number of animals moving: " + str(animalSlot))
				self.inputAction()
				
			self.checkWin()
