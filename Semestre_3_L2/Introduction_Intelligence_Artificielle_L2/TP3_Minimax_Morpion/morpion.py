

import math
import time


class Morpion():
    def __init__(self):
    	# we will use a single list to rep 3x3 board
        self.board = self.makeBoard()

        # keep track of winner
        self.currentWin = None

    @staticmethod
    def makeBoard():
        return [' ' for _ in range(9)]

    def showBoard(self):
    	# getting the rows
        for row in [self.board[i*3:(i+1) * 3] for i in range(3)]:
            print('| ' + ' | '.join(row) + ' |')

    @staticmethod
    def showBoardNbr():
        #  0 | 1 | 2 etc (tells us what number corresponds to what box)
        number_board = [[str(i) for i in range(j*3, (j+1)*3)] for j in range(3)]
        for row in number_board:
            print('| ' + ' | '.join(row) + ' |')

    def showXO(self, square, letter):
    	### replace the empty place with letter X or O
        if self.board[square] == ' ':
            self.board[square] = letter
            if self.winner(square, letter):
                self.currentWin = letter
            return True
        return False

    def winner(self, square, letter):
        ### check the row
        row_ind = math.floor(square / 3)
        row = self.board[row_ind*3:(row_ind+1)*3]

        # print('row', row)
        if all([s == letter for s in row]):
            return True
        col_ind = square % 3
        column = [self.board[col_ind+i*3] for i in range(3)]

        ### check the column
        # print('col', column)
        if all([s == letter for s in column]):
            return True

        ### check the diagonal
        if square % 2 == 0:
            diagonal1 = [self.board[i] for i in [0, 4, 8]]

            # print('diag1', diagonal1)
            if all([s == letter for s in diagonal1]):
                return True
            diagonal2 = [self.board[i] for i in [2, 4, 6]]

            # print('diag2', diagonal2)
            if all([s == letter for s in diagonal2]):
                return True
        return False

    def emptyPlace(self):
        return ' ' in self.board

    def numEmptyPlace(self):
        return self.board.count(' ')

    def getPosibleAct(self):
		## Option 1:

		# moves = []
		# for (i, spot) in enumerate(self.board):
		# 	## ['x', 'x', 'o'] --> [(0, 'x'), (1, 'x'), (2, '0')]
		# 	if spot == ' ':
		# 		moves.append(i)
		# return moves


		## Option 2:
        return [i for i, x in enumerate(self.board) if x == " "]



def play(game, x_player, o_player, print_game=True):

	if print_game:
		game.showBoardNbr()

	letter = 'X'
	while game.emptyPlace():
		if letter == 'O':
			square = o_player.getAct(game)
		else:
			square = x_player.getAct(game)
		if game.showXO(square, letter):

			if print_game:
				print(letter + ' makes a move to square {}'.format(square))
				game.showBoard()
				print('')

			if game.currentWin:
				if print_game:
					print(letter + ' wins!')
				return letter  # ends the loop and exits the game
			letter = 'O' if letter == 'X' else 'X'  # switches player

		time.sleep(.8)

	if print_game:
		print('It\'s a draw!')


