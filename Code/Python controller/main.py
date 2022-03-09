
import sys
import platform
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import (QCoreApplication, QPropertyAnimation, QDate, QDateTime, QMetaObject, QObject, QPoint, QRect, QSize, QTime, QUrl, Qt, QEvent)
from PyQt5.QtGui import (QBrush, QColor, QConicalGradient, QCursor, QFont, QFontDatabase, QIcon, QKeySequence, QLinearGradient, QPalette, QPainter, QPixmap, QRadialGradient)
from PyQt5.QtWidgets import *
import communication
from order import Order
import time



# GUI FILE
from ui_main import Ui_MainWindow

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowModality(QtCore.Qt.ApplicationModal)

        ## For comm
        #self.comm = communication.Communication()
        self.listcmd = []
        self.listdist = []

        ## For UI
        self.listangle = []
        self.counter = 0

        ## PAGES
        ########################################################################

        # PAGE 1
        self.ui.btn_page_1.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.page_1))

        # PAGE 2
        self.ui.btn_page_2.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.page_2))

        # PAGE 3
        self.ui.btn_page_3.clicked.connect(lambda: self.ui.stackedWidget.setCurrentWidget(self.ui.page_3))

        # Add command button
        self.ui.pb_addcmd.clicked.connect(self.addcmd)

        # Clear command button
        self.ui.pb_clearcmd.clicked.connect(self.clearcmd)

        # Home button

        self.ui.pb_home_auto.clicked.connect(self.homeorder)

        ## SHOW ==> MAIN WINDOW
        ########################################################################
        self.show()
        ## ==> END ##

    ## For UI


    def addcmd(self):
        dist = self.ui.distance_input.text()
        angle = self.ui.angle_input_auto.text()

        if self.counter < 6:
            self.listcmd.append("Cmd" + str(self.counter + 1) + "-> Dist: " + dist + " Angle: " + angle)
            self.listdist.append(dist)
            self.listangle.append(angle)
            self.counter += 1

        if self.counter == 1:
            self.ui.label_cmd1.setText(self.listcmd[self.counter - 1])
        elif self.counter == 2:
            self.ui.label_cmd2.setText(self.listcmd[self.counter - 1])
        elif self.counter == 3:
            self.ui.label_cmd3.setText(self.listcmd[self.counter - 1])
        elif self.counter == 4:
            self.ui.label_cmd4.setText(self.listcmd[self.counter - 1])
        elif self.counter == 5:
            self.ui.label_cmd5.setText(self.listcmd[self.counter - 1])
        elif self.counter == 6:
            self.ui.label_cmd6.setText(self.listcmd[self.counter - 1])

    def clearcmd(self):

        if self.counter > 0:
            self.listcmd.pop()
            self.listdist.pop()
            self.listangle.pop()

        if self.counter == 1:
            self.ui.label_cmd1.setText(" ")
        elif self.counter == 2:
            self.ui.label_cmd2.setText(" ")
        elif self.counter == 3:
            self.ui.label_cmd3.setText(" ")
        elif self.counter == 4:
            self.ui.label_cmd4.setText(" ")
        elif self.counter == 5:
            self.ui.label_cmd5.setText(" ")
        elif self.counter == 6:
            self.ui.label_cmd6.setText(" ")

        if self.counter > 0:
            self.counter -= 1

    ## Orders
    def homeorder(self):
        self.ui.label_state_auto.setText('Homing...')
        self.ui.label_state_auto.repaint()
        time.sleep(5)
        # self.comm.send_order(Order.HOME, 1)
        if answer == 0:
            self.ui.label_state_auto.setText('Homing complete')
        else:
            self.ui.label_state_auto.setText('Homing failed')



        """
        print("send order SEMI_AUTO")
        self.comm.send_order(Order.SEMI_AUTO, 1)
        print("end")
        print("\n")
        print("send order SERVO 40 rad/s")
        self.comm.send_order_param(Order.SERVO, 40, 1)  # une séquence à chaque click + wait for finish
        print("end")
        """

    #def startorder(self):

    #def stoporder(self):





if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()

    sys.exit(app.exec_())



