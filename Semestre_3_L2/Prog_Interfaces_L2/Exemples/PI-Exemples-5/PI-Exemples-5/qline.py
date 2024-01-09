import sys
from PyQt5.QtWidgets import *

app = QApplication.instance() 
app = QApplication(sys.argv)

champ = QLineEdit("Tapez votre message")

champ.show()
app.exec_()

