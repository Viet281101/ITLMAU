  
from tkinter import * 
from PIL import ImageTk, Image
   
coords = [[20,30], [120,30], [220, 30], [70,80], [170,80]] 
couleurs = ["red", "yellow", "blue", "green", "black"] 

def anneau(i): 
  x1, y1 = coords[i][0], coords[i][1] 
  cnv.create_oval(x1, y1, x1+100, y1 +100, width =2, outline =couleurs[i]) 
  
def a1(): 
  anneau(0) 
  
def a2(): 
  anneau(1) 
  
def a3(): 
  anneau(2) 
  
def a4(): 
  anneau(3) 
  
def a5(): 
  anneau(4) 
   
app = Tk() 
cnv = Canvas(app, width =335, height =200, bg ="white") 
cnv.pack() 

btn = Button(app, text ="Quitter", command =app.quit) 
btn.pack(side = RIGHT) 

red = Image.open("red.png").resize((20,20))
red = ImageTk.PhotoImage(red)
Button(app, image=red, command = a1).pack(side =LEFT)	  
yellow = Image.open("yellow.png").resize((20,20))
yellow = ImageTk.PhotoImage(yellow)
Button(app, image=yellow, command = a2).pack(side =LEFT)	  
blue = Image.open("blue.png").resize((20,20))
blue = ImageTk.PhotoImage(blue)
Button(app, image=blue, command = a3).pack(side =LEFT)	  
green = Image.open("green.png").resize((20,20))
green = ImageTk.PhotoImage(green)
Button(app, image=green, command = a4).pack(side =LEFT)	  
black = Image.open("black.png").resize((20,20))
black = ImageTk.PhotoImage(black)
Button(app, image=black, command = a5).pack(side =LEFT)	  

app.mainloop()