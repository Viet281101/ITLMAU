import sys
from PyQt5.QtWidgets import *

app = QApplication.instance() 
app = QApplication(sys.argv)

fen = QWidget()
fen.setWindowTitle("Ma fenêtre")
fen.resize(400,400)
fen.move(300,150)

fen.show()
app.exec_()

