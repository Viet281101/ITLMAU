from random import randrange
from turtle import Turtle, Screen
from math import pi, atan2, degrees

DIRECTIONS = ['N', 'NNE', 'NE', 'ENE', 'E', 'ESE', 'SE', 'SSE', 'S', 'SSW', 'SW', 'WSW', 'W', 'WNW', 'NW', 'NNW']

BUCKET = 360.0 / len(DIRECTIONS)

X, Y = 0, 1

SIZE = 500

def onclick_handler(x, y):
    # Draw random vector

    yertle.reset()
    yertle.hideturtle()
    yertle.penup()

    start = (randrange(-SIZE//2, SIZE//2), randrange(-SIZE//2, SIZE//2))
    end = (randrange(-SIZE//2, SIZE//2), randrange(-SIZE//2, SIZE//2))

    yertle.goto(start)
    yertle.dot()
    yertle.showturtle()
    yertle.pendown()
    yertle.setheading(yertle.towards(end))
    yertle.goto(end)

    # Compute vector direction

    x, y = end[X] - start[X], end[Y] - start[Y]

    angle = round(degrees(atan2(y, -x) - pi / 2), 10) % 360.0

    direction = DIRECTIONS[round(angle / BUCKET) % len(DIRECTIONS)]

    screen.title("{} degress is {}".format(round(angle, 2), direction))

yertle = Turtle()

screen = Screen()
screen.mode('logo')
screen.setup(SIZE, SIZE)
screen.onclick(onclick_handler)

onclick_handler(0, 0)

screen.mainloop()