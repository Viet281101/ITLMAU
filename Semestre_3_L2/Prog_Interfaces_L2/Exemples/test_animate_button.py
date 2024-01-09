

#!/usr/bin/env python

""" "Animate" a Tkinter button

    Make the button look like it's been pressed when the user
    hits the key associated with the button.

    See http://stackoverflow.com/q/31900552/4014959

    Written by PM 2Ring 2015.08.09
"""

import tkinter as tk

maxbutton = 5
maxkey = str(maxbutton)

def button_cb(ch):
    print('Button ' + ch + ' pressed')

def onKeyPress(event):
    ch = event.char
    if '1' <= ch <= maxkey:
        #Retrieve this button from the dict
        b = buttons[ch]

        #Simulate pushing the button
        b.config(relief=tk.SUNKEN)
        button_cb(ch)

        #Let it pop back up after 200 milliseconds
        b.after(200, lambda: b.config(relief=tk.RAISED))

root = tk.Tk()
root.title("Key / Button Demo")

#A dict to save the buttons in. The dict keys are the button texts.
buttons = {}

#Make some buttons
for i in range(1, maxbutton + 1):
    s = str(i)
    b = tk.Button(root, text=s, command=lambda ch=s: button_cb(ch))
    b.pack(side=tk.LEFT)

    #Save this button in the dict
    buttons[s] = b

root.bind('<KeyPress>', onKeyPress)

root.mainloop()


