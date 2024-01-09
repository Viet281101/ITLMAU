# Import the required libraries
from tkinter import *
from PIL import Image, ImageTk

# Create an instance of tkinter frame
win = Tk()

# Set the size of the tkinter window
win.geometry("700x350")

# Define a Canvas widget
canvas = Canvas(win, width=600, height=400, bg="white")
canvas.pack(pady=20)

# Add Images to Canvas widget
x = 250
y = 120
image = ImageTk.PhotoImage(Image.open('red.png'))
img = canvas.create_image(x, y, anchor=NW, image=image)

def left(e):
   global x, y
   x -= 0.9
   canvas.coords(img, x, y)

def right(e):
   global x, y
   x += 0.9
   canvas.coords(img, x, y)

def up(e):
   global x, y
   y -= 0.9
   canvas.coords(img, x, y)

def down(e):
   global x, y
   y += 0.9
   canvas.coords(img, x, y)

# Bind the move function
win.bind("<Left>", left)
win.bind("<Right>", right)
win.bind("<Up>", up)
win.bind("<Down>", down)

win.mainloop()