
import sys
from PyQt5.QtWidgets import *

app = QApplication.instance() 
app = QApplication(sys.argv)

fen = QWidget()
fen.show()
app.exec_()

