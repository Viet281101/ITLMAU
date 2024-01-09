
from agent import *
from morpion import *
import morpion as mp


def main():
	game = Morpion()

	x_player = Agent('X')
	o_player = Agent('O')

	mp.play(game, x_player, o_player, print_game=True)


if __name__ == '__main__':
	main()

