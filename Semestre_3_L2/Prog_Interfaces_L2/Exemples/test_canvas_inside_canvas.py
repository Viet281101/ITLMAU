
from tkinter import *
from PIL import Image, ImageTk

class MainWindow(Frame):
    def __init__(self):
        super().__init__()
        self.pack(expand=Y,fill=BOTH)

        outercanvas = Canvas(self, width=200, height=100, bg='#00ffff')
        outercanvas.pack(expand=Y,fill=BOTH)

        innercanvas = Canvas(outercanvas, width=100, height=500)
        outercanvas.create_window(0, 0, anchor=NW, window=innercanvas)

        innercanvas.create_text(10, 10, anchor=NW, text="Hello")
        img = Image.open('red.png')
        
        imgRed = ImageTk.PhotoImage(img)
        innercanvas.create_image(10, 10, anchor=NW, image=imgRed)

root = MainWindow()
root.mainloop()
