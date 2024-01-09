# from tkinter import *
# from tkinter import ttk
# from calendar import month_name

# fen = Tk()
# fen.geometry('200x200')
# fen.resizable(False, False)

# label = ttk.Label(text="Choisissez un mois:")
# label.pack(fill=X, padx=5, pady=5)

# mois = StringVar()
# liste_mois = ttk.Combobox(fen, textvariable=mois)
# liste_mois['values'] = [month_name[m] for m in range(1, 13)]
# liste_mois['state'] = 'readonly'
# liste_mois.pack(fill=X, padx=5, pady=5)

# fen.mainloop()








# import tkinter as tk
# from tkinter import ttk
# my_w = tk.Tk()
# my_w.geometry("300x150")  # Size of the window 
# my_w.title("www.plus2net.com")  # Adding a title
# def my_upd1():
#     cb1.set('Apr') # update selection to Apr
#     l1.config(text=cb1.get()+':'+ str(cb1.current())) # value & index

# months=['Jan','Feb','Mar','Apr','May','Jun']
# cb1 = ttk.Combobox(my_w, values=months,width=7)
# cb1.grid(row=1,column=1,padx=10,pady=20)

# b1=tk.Button(my_w,text="set('Apr')", command=lambda: my_upd1())
# b1.grid(row=1,column=2)

# l1=tk.Label(my_w,text='Month')
# l1.grid(row=1,column=3)
# print(cb1.get())
# my_w.mainloop()  # Keep the window open











import tkinter as tk
from tkinter import ttk
from tkinter.messagebox import showinfo
from calendar import month_name

root = tk.Tk()

# config the root window
root.geometry('300x200')
root.resizable(False, False)
root.title('Combobox Widget')

# label
label = ttk.Label(text="Please select a month:")
label.pack(fill=tk.X, padx=5, pady=5)

# create a combobox
selected_month = tk.StringVar()
month_cb = ttk.Combobox(root, textvariable=selected_month)

# get first 3 letters of every month name
month_cb['values'] = [month_name[m][0:3] for m in range(1, 13)]

# prevent typing a value
month_cb['state'] = 'readonly'

# place the widget
month_cb.pack(fill=tk.X, padx=5, pady=5)


# bind the selected value changes
def month_changed(event):
    """ handle the month changed event """
    showinfo(
        title='Result',
        message=f'You selected {selected_month.get()}!'
    )

month_cb.bind('<<ComboboxSelected>>', month_changed)

root.mainloop()


