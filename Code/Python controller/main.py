
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
        self.listangle = []
        self.listdist = []
        self.listanglerev = []
        self.listdistrev = []

        ## For UI
        self.listcmd = []
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

        # Autopage button
        self.ui.pb_home_auto.clicked.connect(self.home_order)
        self.ui.pb_start.clicked.connect(self.start_order)
        self.ui.pb_stop.clicked.connect(self.stop_order)

        # SemiAuto Button
        self.ui.pb_home_semi.clicked.connect(self.homeS_order)
        self.ui.pb_sendcmd.clicked.connect(self.sendcmd_order)
        self.ui.pb_jogf.clicked.connect(self.jogf_order)
        self.ui.pb_jogb.clicked.connect(self.jogb_order)

        # Manual
        ## Step Motors
        self.ui.pb_step_flclock.clicked.connect(self.step_flclock_order)
        self.ui.pb_step_flcounter.clicked.connect(self.step_flcounter_order)
        self.ui.pb_step_frclock.clicked.connect(self.step_frclock_order)
        self.ui.pb_step_frcounter.clicked.connect(self.step_frcounter_order)
        self.ui.pb_step_blclock.clicked.connect(self.step_blclock_order)
        self.ui.pb_step_blcounter.clicked.connect(self.step_blcounter_order)
        self.ui.pb_step_brclock.clicked.connect(self.step_brclock_order)
        self.ui.pb_step_brcounter.clicked.connect(self.step_brcounter_order)

        ## Servo Motors
        self.ui.pb_ser_flclock.clicked.connect(self.ser_flclock_order)
        self.ui.pb_ser_flcounter.clicked.connect(self.ser_flcounter_order)
        self.ui.pb_ser_frclock.clicked.connect(self.ser_frclock_order)
        self.ui.pb_ser_frcounter.clicked.connect(self.ser_frcounter_order)
        self.ui.pb_ser_blclock.clicked.connect(self.ser_blclock_order)
        self.ui.pb_ser_blcounter.clicked.connect(self.ser_blcounter_order)
        self.ui.pb_ser_brclock.clicked.connect(self.ser_brclock_order)
        self.ui.pb_ser_brcounter.clicked.connect(self.ser_brcounter_order)

        ## Magnets
        self.ui.cb_flmag.stateChanged.connect(self.flmag_order)
        self.ui.cb_frmag.stateChanged.connect(self.frmag_order)
        self.ui.cb_blmag.stateChanged.connect(self.blmag_order)
        self.ui.cb_brmag.stateChanged.connect(self.brmag_order)

        ## SHOW ==> MAIN WINDOW
        ########################################################################
        self.show()
        ## ==> END ##

    ## For UI
    def get_int(self, prompt):
        while True:
            try:
                answer = int(prompt)
                break
            except ValueError:
                return 0
        return 1
    def addcmd(self):
        dist = self.ui.distance_input.text()
        angle = self.ui.angle_input_auto.text()
        self.ui.distance_input.repaint()
        self.ui.angle_input_auto.repaint()
        self.ui.distance_input.clear()
        self.ui.angle_input_auto.clear()

        if self.get_int(dist) == 0 or self.get_int(angle) == 0:
            self.ui.label_state_auto.setText('Please enter an integer value')

        else:
            self.ui.label_state_auto.setText(" ")
            if self.counter < 6:
                self.listcmd.append("Cmd" + str(self.counter + 1) + "-> Dist: " + dist + " Angle: " + angle)
                self.listdist.append(dist)
                self.listangle.append(angle)
                self.counter += 1

            if self.counter == 1:
                self.ui.label_cmd1.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()
            elif self.counter == 2:
                self.ui.label_cmd2.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()
            elif self.counter == 3:
                self.ui.label_cmd3.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()
            elif self.counter == 4:
                self.ui.label_cmd4.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()

            elif self.counter == 5:
                self.ui.label_cmd5.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()

            elif self.counter == 6:
                self.ui.label_cmd6.setText(self.listcmd[self.counter-1])
                self.ui.distance_input.repaint()
                self.ui.label_state_auto.setText('List full')
                self.ui.label_state_auto.repaint()
                time.sleep(2)
                self.ui.label_state_auto.setText('Clear some command to add others.')
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
    # Automatic
    def home_order(self):
        self.ui.label_state_auto.setText('Homing...')
        self.ui.label_state_auto.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.HOME, 1)
        if answer == 0:
            self.ui.label_state_auto.setText('Homing completed!')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')
        else:
            self.ui.label_state_auto.setText('Homing failed, please try again')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')



        """
        print("send order SEMI_AUTO")
        self.comm.send_order(Order.SEMI_AUTO, 1)
        print("end")
        print("\n")
        print("send order SERVO 40 rad/s")
        self.comm.send_order_param(Order.SERVO, 40, 1)  # une séquence à chaque click + wait for finish
        print("end")
        """
    def start_order(self):
        self.ui.label_state_auto.setText('Starting command...')
        self.ui.label_state_auto.repaint()

        if self.ui.cb_reversecmd.isChecked() == True:
            print('in if')
            for i in range(self.counter):
                self.listdistrev.append(self.listdist[self.counter-1-i])
                self.listanglerev.append(self.listangle[self.counter-1-i])
            ## Send start order with both list rev
            # self.comm.send_order(Order.START, 1)
        else:
            ## Send start order with normal lists
            # self.comm.send_order(Order.START, 1)
            print('else')

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.START, 1)

        # Reset reverse lists
        for i in range(self.counter):
            self.listdistrev.pop()
            self.listanglerev.pop()

        if answer == 0:
            self.ui.label_state_auto.setText('Command completed!')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')
        else:
            self.ui.label_state_auto.setText('Command failed, please try again')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')
    def stop_order(self):
        self.ui.label_state_auto.setText('Stop command...')
        self.ui.label_state_auto.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.STOP, 1)
        if answer == 0:
            self.ui.label_state_auto.setText('Command stopped!')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')
        else:
            self.ui.label_state_auto.setText('Stop command failed, please try again')
            self.ui.label_state_auto.repaint()
            time.sleep(2)
            self.ui.label_state_auto.setText(' ')

    # SemiAutomatic
    def homeS_order(self):
        self.ui.label_state_semi.setText('Homing...')
        self.ui.label_state_semi.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.HOME, 1)
        if answer == 0:
            self.ui.label_state_semi.setText('Homing completed!')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
        else:
            self.ui.label_state_semi.setText('Homing failed, please try again')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
    def sendcmd_order(self):
        angle = self.ui.angle_input_semi.text()
        self.ui.angle_input_semi.repaint()
        self.ui.angle_input_semi.clear()

        self.ui.label_state_semi.setText('Sending angle of '+angle+' degree...')
        self.ui.label_state_semi.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order_param(Order.SEMI_AUTO, 1, angle)
        ## commande

        if answer == 0:
            self.ui.label_state_semi.setText('Command completed!')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
        else:
            self.ui.label_state_semi.setText('Command failed, please try again')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
    def jogf_order(self):
        self.ui.label_state_semi.setText('Jogging forward...')
        self.ui.label_state_semi.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.SEMI_AUTO, 1)

        if answer == 0:
            self.ui.label_state_semi.setText('Jogging forward completed!')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
        else:
            self.ui.label_state_semi.setText('Jogging forward failed, please try again')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
    def jogb_order(self):
        self.ui.label_state_semi.setText('Jogging backwards...')
        self.ui.label_state_semi.repaint()

        ## en attendant
        time.sleep(5)
        answer = 0
        # self.comm.send_order(Order.SEMI_AUTO, 1)

        if answer == 0:
            self.ui.label_state_semi.setText('Jogging backwards completed!')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')
        else:
            self.ui.label_state_semi.setText('Jogging backwards failed, please try again')
            self.ui.label_state_semi.repaint()
            time.sleep(2)
            self.ui.label_state_semi.setText(' ')

    # Manual
    def step_flclock_order(self):
        self.ui.pb_step_flclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_flclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_flclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_flcounter_order(self):
        self.ui.pb_step_flcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_flcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_flcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_frclock_order(self):
        self.ui.pb_step_frclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_frclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_frclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_frcounter_order(self):
        self.ui.pb_step_frcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_frcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_frcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_blclock_order(self):
        self.ui.pb_step_blclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_blclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_blclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_blcounter_order(self):
        self.ui.pb_step_blcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_blcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_blcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_brclock_order(self):
        self.ui.pb_step_brclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_brclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_brclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def step_brcounter_order(self):
        self.ui.pb_step_brcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_step_brcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_step_brcounter.setStyleSheet("background-color: rgb(255, 255, 255);")

    def ser_flclock_order(self):
        self.ui.pb_ser_flclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_flclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_flclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_flcounter_order(self):
        self.ui.pb_ser_flcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_flcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_flcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_frclock_order(self):
        self.ui.pb_ser_frclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_frclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_frclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_frcounter_order(self):
        self.ui.pb_ser_frcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_frcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_frcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_blclock_order(self):
        self.ui.pb_ser_blclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_blclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_blclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_blcounter_order(self):
        self.ui.pb_ser_blcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_blcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_blcounter.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_brclock_order(self):
        self.ui.pb_ser_brclock.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_brclock.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_brclock.setStyleSheet("background-color: rgb(255, 255, 255);")
    def ser_brcounter_order(self):
        self.ui.pb_ser_brcounter.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.ui.pb_ser_brcounter.repaint()
        time.sleep(2)
        ## send cmd
        # self.comm.send_order(Order.HOME, 1)
        self.ui.pb_ser_brcounter.setStyleSheet("background-color: rgb(255, 255, 255);")

    def flmag_order(self):
        if self.ui.cb_flmag.isChecked() == True:
            ## activater magnet
            print('magnet activated')
        else:
            ## desactiver magnet
            print('magnet desactivated')
    def frmag_order(self):
        if self.ui.cb_frmag.isChecked() == True:
            ## activater magnet
            print('magnet activated')
        else:
            ## desactiver magnet
            print('magnet desactivated')
    def blmag_order(self):
        if self.ui.cb_blmag.isChecked() == True:
            ## activater magnet
            print('magnet activated')
        else:
            ## desactiver magnet
            print('magnet desactivated')
    def brmag_order(self):
        if self.ui.cb_brmag.isChecked() == True:
            ## activater magnet
            print('magnet activated')
        else:
            ## desactiver magnet
            print('magnet desactivated')



if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())



