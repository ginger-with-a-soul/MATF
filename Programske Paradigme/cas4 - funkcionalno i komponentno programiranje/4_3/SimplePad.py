from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox, QFileDialog
import ui
import sys
import os

class SimplePadClass(ui.Ui_MainWindow, QtWidgets.QMainWindow):

	def __init__(self):
		super(SimplePadClass, self).__init__()
		self.setupUi(self)

		self.path = None

		self.actionNew_File.triggered.connect(lambda: self.createMe())
		self.actionOpen_File.triggered.connect(lambda: self.openMe())
		self.actionSave.triggered.connect(lambda: self.saveMe())

	def __title(self):
		if self.path is not None:
			self.setWindowTitle(os.path.basename(self.path) + ' - SimplePad')
		else:
			self.setWindowTitle('untitled - SimplePad')

	def __dialog(self, msg):
		box = QMessageBox(self)
		box.setText(msg)
		box.show()
	
	def __save_util(self, path):
		data = self.editor.toPlainText()

		try:
			with open(path, 'w') as file:
				file.write(data)
		except Exception as err:
			self.__dialog(str(err))
		else:
			self.path = path
			self.__title()
	
	def openMe(self):
		path, _ = QFileDialog.getOpenFileName(self, "Open file", "", "All files (*.*);")

		if path:
			try:
				with open(path, 'r') as file:
					data = file.read()
			except Exception as err:
				self.__dialog(str(err))
			else:
				self.path = path
				self.editor.setPlainText(data)
				self.__title()
	
	def saveMe(self):
		if self.path is None:
			return self.saveAsMe()
		self.__save_util(self.path)

	def saveAsMe(self):
		path, _ = QFileDialog.getSaveFileName(self, "Save file", "", "All files (*.*);")

		if not path:
			return
		self.__save_util(path)




if __name__ == "__main__":
	app = QtWidgets.QApplication(sys.argv)
	simplePad = SimplePadClass()
	simplePad.show()
	sys.exit(app.exec_())