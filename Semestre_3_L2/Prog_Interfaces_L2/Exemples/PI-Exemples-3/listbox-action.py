from tkinter import *

fruits = ["Litchie", "Kiwi", "Orange", "Raisin", \
    "Banane", "Cerise"]
couleurs = ["pink", "lightgreen", "orange", \
    "purple", "yellow", "red"]
n = len(fruits)

app = Tk()

lbox = Listbox(app, width=8,height=8,\
    font="Verdana 30 bold",selectbackground="blue")
lbox.pack(padx=20,pady=20)

for item in fruits:
    lbox.insert(END, item)
    lbox.focus_set()
    pos = 1
    lbox.activate(pos)
    lbox.selection_set(pos)
for i in range(0, len(fruits), 2):
    lbox.itemconfigure(i, background="#f0f0ff")
for i in range(1, len(fruits), 2):
    lbox.itemconfigure(i, background="#fff")

def show(event):
    index= lbox.curselection()[0]
    cnv["bg"] = couleurs[index]
    
lbox.bind("<<ListboxSelect>>", show)

cnv = Canvas(app, width =200, height= 200, \
    bg="ivory")
cnv.pack(padx=5,pady=5,side=RIGHT)
cnv["bg"]=couleurs[pos]

app.mainloop()