https://pythonpyqt.com/how-to-install-pyqt5-in-pycharm/

In pycharm terminal

	python -m pip install --upgrade pip

	pip install pyqt5 pyqt5-tools

Test :
	import sys    
	from PyQt5 import QtWidgets, QtCore  

	app = QtWidgets.QApplication(sys.argv)  
	widget = QtWidgets.QWidget()  
	widget.resize(400, 200)  
	widget.setWindowTitle("This is PyQt Widget example")  
	widget.show()        
	exit(app.exec_())

Settings/tools/externaltools : 
	create QTdesigner, program : pyqt5-tools.exe, arg : designer, working directory : $ProjectFileDir$

	create PyUIC, program : python.exe, arg : -m PyQt5.uic.pyuic $FileName$ -o $FileNameWithoutExtension$.py, working directory : $ProjectFileDir$

To create UI : tools/external/QTdesigner
	save as : .ui in project

To convert UI in python : right click on .ui external tools/PythonUIC

Test :
	from PyQt5 import QtWidgets # import PyQt5 widgets
	import sys

	# Create the application object
	app = QtWidgets.QApplication(sys.argv)

	# Create the form object
	first_window = QtWidgets.QWidget()

	# Set window size
	first_window.resize(400, 300)

	# Set the form title
	first_window.setWindowTitle("The first pyqt program")

	# Show form
	first_window.show()

	# Run the program
	sys.exit(app.exec())

