

from tkinter import *

root = Tk()

display = Label(root,text="Starting")
displayState = 1
display.pack()

def change():
    global displayState, display

    if displayState == 1:
        display.config(text="I just changed")

    elif displayState == 2:
        display.config(text="I changed again")

    elif displayState == 3:
        display.config(text="I changed once more")

    displayState += 1

button = Button(root,text="Press me",command=change)
button.pack()

root.mainloop()
