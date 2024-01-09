from tkinter import *

app=Tk()
mon_texte="""Je suis un texte long 
qui souhaiterait être centré 
sur plusieurs lignes."""
annonce=Label(app, height=5, width=50, \
    text=mon_texte, justify=CENTER, \
        bg="ivory")
annonce.pack()
app.mainloop()