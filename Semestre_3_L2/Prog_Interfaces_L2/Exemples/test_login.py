



import tkinter as tk

class SampleApp(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self._frame = None
        self.switch_frame(Register)

    def switch_frame(self, frame_class):
        """Destroys current frame and replaces it with a new one."""
        new_frame = frame_class(self)
        if self._frame is not None:
            self._frame.destroy()
        self._frame = new_frame
        self.geometry('925x600+'+self.screen()+'+20')
        self._frame.pack()

    def screen(self):
        screen_width = self.winfo_screenwidth()
        posX = (screen_width //2) - (925//2) 
        return str(posX)

class Register(tk.Frame):
    def __init__(self, master):
        tk.Frame.__init__(self, master)
        tk.Label(self, text="This is the register Page").pack(side="top", fill="x", pady=10)
        tk.Button(self, text="Login",
                  command=lambda: master.switch_frame(Login)).pack()

class Login(tk.Frame):
    def __init__(self, master):
        tk.Frame.__init__(self, master)
        tk.Label(self, text="Login Page").pack(side="top", fill="x", pady=10)
        self.usuario = tk.Entry(self)
        self.usuario.insert(-1, 'User')
        self.usuario.config(foreground='gray')
        self.usuario.pack(side="top", fill="x", padx=10, ipady=3)

        
        self.password = tk.Entry(self)
        self.password.insert(-1, "Password")
        self.password.config(foreground='gray')
        self.password.pack(side="top", fill="x", pady=10, padx=10, ipady=3)

        tk.Button(self, text="Return to register",
                  command=lambda: master.switch_frame(Register)).pack()
        tk.Button(self, text="Login",
                  command=lambda: print("not implemented yet")).pack()



if __name__ == "__main__":
    app = SampleApp()
    app.mainloop()


