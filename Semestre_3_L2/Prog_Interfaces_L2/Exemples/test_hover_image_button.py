
from tkinter import *
from PIL import Image, ImageTk

# def onEnter(event):
#     global img
#     img = ImageTk.PhotoImage(Image.open(r'red.png'))
#     btn.config(image=img)

# def onLeave(event):
#     global img
#     img = ImageTk.PhotoImage(Image.open(r'blue.png'))
#     btn.config(image=img)
    

root = Tk()
# img = ImageTk.PhotoImage(Image.open(r'blue.png')) 

# btn = Button(root, image=img, bd = 0, highlightthickness=0)
# btn.pack()

# btn.bind('<Enter>',  onEnter)
# btn.bind('<Leave>',  onLeave)



img1 = 'blue.png'
img2 = 'red.png'

class Btn(Button):

    def __init__(self, root, img1, img2, *args, **kwargs):       
        super().__init__(root, *args, **kwargs)

        self.img = ImageTk.PhotoImage(Image.open(img1))
        self.img2 = ImageTk.PhotoImage(Image.open(img2))

        self['image'] = self.img
        
        self.bind('<Enter>', self.enter)
        self.bind('<Leave>', self.leave)
        
    def enter(self, event):
        self.config(image=self.img2)

    def leave(self, event):
        self.config(image=self.img)


btn = Btn(root, img1=img1, img2=img2)
btn.pack()


root.mainloop()

