from tkinter import *
from tkinter import ttk
from tkcalendar import DateEntry

fen = Tk()

fen.title("Inscription")
fen.geometry("350x400")
fen.resizable(False,False)

nom = StringVar()
contact = StringVar()
email=StringVar()
sexe=IntVar()
ville=StringVar()
message=StringVar()

Label(fen,width="300", text="Remplissez les champs suivants", bg="orange",fg="white").pack()

Label(fen, text="Nom * ").place(x=20,y=40)
Entry(fen, textvariable=nom).place(x=90,y=42)

Label(fen, text="Contact * ").place(x=20,y=80)
Entry(fen, textvariable=contact).place(x=90,y=82)

Label(fen, text="Email * ").place(x=20, y=120)
Entry(fen, textvariable=email).place(x=90, y=122)

Label(fen, text="Sexe * ").place(x=20, y=160)
Radiobutton(fen,text="Homme",variable=sexe,value=1).place(x=90,y=162)
Radiobutton(fen, text="Femme", variable=sexe, value=2).place(x=180, y=162)

Label(fen, text="Date de naissance * ").place(x=20, y=192)
cal = DateEntry(fen, width=12, background='ivory',
                    foreground='black', borderwidth=2, selectmode='day')
 
cal.place(x=160, y=192)
style = ttk.Style(fen)
style.theme_use('clam') #thème par défaut

Label(fen, text="Ville * ").place(x=20, y=220)

ville_choisie = ttk.Combobox(fen, width=20, textvariable=ville)
ville_choisie['values'] = (' Paris',
                              ' Bordeaux',
                              ' Lille',
                              ' Lyon',
                              ' Brest',
                              ' Grenoble',
                              ' Nice',
                              ' Strasbourg',
                              ' Toulouse',
                              ' Rennes')
ville_choisie.current()
ville_choisie.place(x=90,y=222)

Button(fen, text="Valider", width=10, height=1, bg="orange").place(x=105,y=300)

fen.mainloop()