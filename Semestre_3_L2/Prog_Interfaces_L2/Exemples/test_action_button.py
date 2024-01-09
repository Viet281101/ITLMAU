
class ActionBtn(Button):
    def __init__(self, window : Tk, player, target, direction, imgBtn):
        super().__init__(window, width=50, height=50, 
            highlightbackground=bg_color, bg=bg_color, 
            bd = 0, activebackground=TEXT_PURPLE, cursor='target')
        self.fenetre = window
        self.target = target
        self.imgBtn = imgBtn
        self.image = ImageTk.PhotoImage(Image.open(imgBtn).resize((50, 50)))
        self.config(image = self.image)
        self.player = player
        self.direction = direction
    
        if self.direction == "right":
            self.config(command=self.goRight)
        elif self.direction == "left":
            self.config(command=self.goLeft)
        elif self.direction == "up":
            self.config(command=self.goUp)
        elif self.direction == "attack":
            self.config(command=self.attack)
    
    def goRight(self) -> None:
        pass

    def goLeft(self) -> None:
        pass

    def goUp(self) -> None:
        pass

    def attack(self) -> None:
        pass
