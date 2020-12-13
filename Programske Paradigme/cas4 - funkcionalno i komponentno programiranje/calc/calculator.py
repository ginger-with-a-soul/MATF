from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox, QFileDialog
import ui
import sys
import os

class CalculatorClass(ui.Ui_MainWindow, QtWidgets.QMainWindow):
	def __init__(self):
		super(CalculatorClass, self).__init__()
		self.setupUi(self)
		
		self.oneButton.clicked.connect(self.inputEdit('1'))
		self.twoButton.clicked.connect(self.inputEdit('2'))


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    calculator = CalculatorClass()
    calculator.show()
    sys.exit(app.exec_())