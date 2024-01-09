

from tkinter import *

def reorganizeButtons(event):
    # if the widths of the buttons exceed width of frame, stack vertically
    # else stack horizontally
    if button1.winfo_width()+button2.winfo_width()>frame.winfo_width():
        button1.grid(row=0,column=0, sticky=NSEW)
        button2.grid(row=1,column=0,sticky=NSEW)
    else:
        button1.grid(row=0,column=0,sticky=NSEW)
        button2.grid(row=0,column=1,sticky=NSEW)
    frame.update_idletasks()
    print ()
    print ("button1 width: ", button1.winfo_width())
    print ("button2 width: ", button2.winfo_width())
    print ("frame width: ", frame.winfo_width())

def main():
    global root
    global frame
    global button1
    global button2
    root = Tk()
    root.maxsize(200,200) # sets a limit on how big the frame can be
    root.title("Resize to Reorganize Buttons")

    frame=Frame(root)
    frame.grid(row=0, column=0, sticky=NSEW)
    root.columnconfigure(0,weight=1)
    root.rowconfigure(0,weight=1)

    button1=Button(frame, text="---Button1---")
    button2=Button(frame, text="---Button2---")

    root.bind("<Configure>", reorganizeButtons)

    root.mainloop()

# main()


#Create an instance of tkinter frame
win= Tk()

#Set the geometry of frame
win.geometry("650x250")

#Get the current screen width and height
screen_width = win.winfo_screenwidth()
screen_height = win.winfo_screenheight()

#Print the screen size
print("Screen width:", screen_width)
print("Screen height:", screen_height)

win.mainloop()


