import sys
from PyQt5.QtWidgets import *

app = QApplication.instance() 
app = QApplication(sys.argv)

mon_label = QLabel("Mon widget QLabel")

mon_label.show()
app.exec_()

