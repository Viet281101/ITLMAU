from tkinter import * 
  
def conversionFar(event): 
  tF = float(champTC.get()) 
  varTF.set(str(tF*1.8 +32)) 
  
def conversionCel(event): 
  tC = float(champTF.get()) 
  varTC.set(str((tC-32)/1.8)) 

def clear():
  varTC.set("0.0")
  varTF.set("0.0")
  
app = Tk() 
  
Label(app, text='Temp. Celsius').grid(row =0, column =0, sticky=W) 
varTC =StringVar()	  
champTC = Entry(app, textvariable =varTC) 
champTC.bind("<Return>", conversionFar) 
champTC.grid(row =0, column =1) 
varTC.set("0.0") 
  
Label(app, text='Temp. Fahrenheit').grid(row =1, column =0, sticky=W)  
varTF =StringVar() 
champTF = Entry(app, textvariable =varTF) 
champTF.bind("<Return>", conversionCel) 
champTF.grid(row =1, column =1) 
varTF.set("0.0") 

Button(app, text= "Effacer", command=clear).grid(row = 2, column = 0, sticky=E)
Button(app, text= "Quitter", command=app.quit).grid(row = 2, column = 1)

app.mainloop()