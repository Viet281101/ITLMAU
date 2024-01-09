from tkinter import *

app = Tk()

scrollbar = Scrollbar(app)
scrollbar.pack(side = RIGHT, fill = Y)

liste = Listbox(app,yscrollcommand=scrollbar.set)
for i in range(200):
   liste.insert(END, str(i) + " Bonjour!")

liste.pack(side = LEFT, fill = BOTH )
scrollbar.config(command = liste.yview )

app.mainloop()

