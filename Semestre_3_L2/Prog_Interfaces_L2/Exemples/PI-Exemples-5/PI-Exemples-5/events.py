import sys
from PyQt5.QtWidgets import *

class Fenetre(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.setWindowTitle("Ma fenetre")

    def mousePressEvent(self, event):
        print("appui souris")

app = QApplication.instance() 
app = QApplication(sys.argv)
fen = Fenetre()
fen.show()
app.exec_()


