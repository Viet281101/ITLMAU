  
from tkinter import * 
   
coords = [[20,30], [120,30], [220, 30], [70,80], [170,80]] 
couleurs = ["red", "yellow", "blue", "green", "black"] 

app = Tk() 
cnv = Canvas(app, width =335, height =200, bg ="white") 
cnv.pack() 
btn = Button(app, text ="Quitter", command =app.quit) 
btn.pack(side = RIGHT) 

def creerAnneau(i):
  x1, y1 = coords[i][0], coords[i][1] 
  cnv.create_oval(x1, y1, x1+100, y1+100, width =2, outline =couleurs[i]) 

i = 0 
while i < 5: 
  creerAnneau(i)
  i = i + 1 
  
app.mainloop()