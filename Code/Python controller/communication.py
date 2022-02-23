import time
import serial
#pip install pyserial
from robust_serial import write_order, write_i8, write_i16, read_i8, read_order
from order import Order

class Communication(object):
    def __init__(self):

        try:
            self.s = serial.Serial(port='COM4', baudrate=115200, timeout=0.1)
        except Exception as e:
            raise e
        is_connected = False
        # Initialize communication with Arduino
        while not is_connected:
            print("Waiting for arduino...")
            write_order(self.s, Order.HELLO)
            bytes_array = bytearray(self.s.read(1))
            if not bytes_array:
                time.sleep(2)
                continue
            byte = bytes_array[0]
            if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
                is_connected = True

        print("Connected to Arduino")

        self.timeout = 3
        self.wait_between_read = 0.1

    """
    Defenitions
    """
    #for automatic mode : order : auto, param
    def send_order_list(self, list_order, list_param, wait_to_finish = 0):

        #envoi seulement list, doit attendre order start
        return 0


    def send_order_param(self, order, param, wait_to_finish = 0):

        if self.send_order(order) == 1:
            return 1 #error
        if self.send_param(param) == 1:
            return 1 #error

        if wait_to_finish == 1:
            if self.wait_for_finish() == 1:
                return 1

        return 0


    def send_order(self, order, wait_to_finish = 0):
        # send order and wait for ack
        write_order(self.s, order)

        if self.wait_for_ack() == 1:
            return 1

        if wait_to_finish == 1:
            if self.wait_for_finish() == 1:
                return 1

        return 0


    def send_param(self, param):

        # send order and wait for ack

        write_i8(self.s, param)

        if self.wait_for_ack() == 1:
            return 1

        return 0


    def wait_for_ack(self):
        start_time = time.time()
        while self.s.inWaiting() < 1:
            print("waiting for ack")
            time.sleep(self.wait_between_read)
            if time.time() - start_time > self.timeout:
                return 1 #error

        order = read_order(self.s)

        if order is not Order.RECEIVED:
            return 1

        return 0

    def wait_for_finish(self):
        while self.s.inWaiting() < 1:
            print("waiting for finish")
            time.sleep(self.wait_between_read)

        order = read_order(self.s)

        if order is not Order.FINISHED:
            return 1

        return 0


