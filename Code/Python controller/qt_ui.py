# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'qt_ui.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(309, 254)
        self.Button_1 = QtWidgets.QPushButton(Dialog)
        self.Button_1.setGeometry(QtCore.QRect(110, 130, 101, 41))
        self.Button_1.setObjectName("Button_1")
        self.label_1 = QtWidgets.QLabel(Dialog)
        self.label_1.setGeometry(QtCore.QRect(50, 30, 51, 31))
        self.label_1.setObjectName("label_1")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(50, 90, 47, 13))
        self.label_2.setObjectName("label_2")
        self.num_1 = QtWidgets.QLineEdit(Dialog)
        self.num_1.setGeometry(QtCore.QRect(130, 40, 113, 20))
        self.num_1.setText("")
        self.num_1.setObjectName("num_1")
        self.num_2 = QtWidgets.QLineEdit(Dialog)
        self.num_2.setGeometry(QtCore.QRect(130, 80, 113, 20))
        self.num_2.setText("")
        self.num_2.setObjectName("num_2")
        self.result = QtWidgets.QLabel(Dialog)
        self.result.setGeometry(QtCore.QRect(130, 180, 81, 41))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.result.setFont(font)
        self.result.setObjectName("result")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.Button_1.setText(_translate("Dialog", "Add numbers"))
        self.label_1.setText(_translate("Dialog", "Num #1"))
        self.label_2.setText(_translate("Dialog", "Num #2"))
        self.result.setText(_translate("Dialog", "Result"))
