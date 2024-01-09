import sys
from PyQt5.QtWidgets import *

def appui_bouton():
    print("Appui sur le bouton")

app = QApplication.instance() 
app = QApplication(sys.argv)

mon_bouton = QPushButton("Mon bouton Qt")
mon_bouton.clicked.connect(appui_bouton)

mon_bouton.show()
app.exec_()

