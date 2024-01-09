

import tkinter as tk
import tkinter.ttk as ttk

root = tk.Tk()

def work():
    if progressbar['value'] == 0:
        but1['state'] = 'disabled'
    if progressbar['value'] >= progressbar['maximum']:
        root.bell()
        but1['state'] = 'normal'
        progressbar['value'] = 0
        return
    progressbar['value'] += 1
    root.after(100, work)

progressbar = ttk.Progressbar(root, length=200, maximum=10, value=0)
progressbar.grid(row=1)

but1 = ttk.Button(root, text='Start', command=work)
but1.grid(row=2)

root.mainloop()
