


class Game():
    def __init__(self) -> None:
        ### button set number wagon
        self.plusImg = ImageTk.PhotoImage(Image.open(path_plus_icon).resize((20, 20)))
        self.minusImg = ImageTk.PhotoImage(Image.open(path_minus_icon).resize((20, 20)))

        self.minusBtn = tk.Button(self.canvas, image = self.plusImg, 
            relief = FLAT, command = self.setNbrWagon, width=30,
            highlightbackground=TEXT_PURPLE, bg=TEXT_PURPLE, bd = 0, 
            activebackground=TEXT_BLACK)
        self.minusBtn.image = self.plusImg
        self.minusBtn.place(x = 1125, y = 5)


    def setNbrWagon(self) -> None:
        global nb_wagons, canPlusWG
        if self.minusBtn.image == self.plusImg and canPlusWG:
            nb_wagons += 1; self.refreshTrain()
            canPlusWG = False
        elif self.minusBtn.image == self.minusImg and not canPlusWG:
            nb_wagons -= 1; self.refreshTrain()
            canPlusWG = True
        self.changeIconMinus()


    def changeIconMinus(self) -> None:
        if not canPlusWG: 
            self.minusBtn.config(image=self.minusImg)
            self.minusBtn.image = self.minusImg
        else: 
            self.minusBtn.config(image=self.plusImg)
            self.minusBtn.image = self.plusImg

    def refreshTrain(self) -> None:
        global canAnimate
        del self.frames
        if showFull: 
            self.nolookBtn.config(image=self.canlookImg)
            self.nolookBtn.image = self.canlookImg
            self.hideWagon()
        canAnimate = False
        self.setDefaultTrain()
        self.showTrainCarriages()
        self.showCaracterGame()

