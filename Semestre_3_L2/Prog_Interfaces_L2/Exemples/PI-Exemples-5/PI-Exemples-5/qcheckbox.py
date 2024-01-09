import sys
from PyQt5.QtWidgets import *

def etat_change():
    print("action sur la case")
    
app = QApplication.instance() 
app = QApplication(sys.argv)

case = QCheckBox("Ma case à cocher")
case.stateChanged.connect(etat_change)

case.show()
app.exec_()

