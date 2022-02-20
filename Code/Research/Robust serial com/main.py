from __future__ import print_function, division, absolute_import

import time
import serial

from robust_serial import write_order, Order, write_i8, write_i16, read_i8, read_order

if __name__ == '__main__':
    try:
        arduino = serial.Serial(port='COM4', baudrate=115200, timeout=0.1)
    except Exception as e:
        raise e

    is_connected = False
    # Initialize communication with Arduino
    while not is_connected:
        print("Waiting for arduino...")
        write_order(arduino, Order.HELLO)
        bytes_array = bytearray(arduino.read(1))
        if not bytes_array:
            time.sleep(2)
            continue
        byte = bytes_array[0]
        if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
            is_connected = True

    print("Connected to Arduino")

    servo_angle = 56

    # Equivalent to write_i8(arduino, Order.MOTOR.value)
    write_order(arduino, Order.SERVO)
    write_i8(arduino, servo_angle)


    while arduino.inWaiting() < 1:
        print("waiting for ack")
        time.sleep(0.1)

    order = read_order(arduino)
    print(order)

    if order is Order.RECEIVED:
        while arduino.inWaiting() < 1:
            print("waiting for task")
            time.sleep(0.1)

        order = read_order(arduino)
        print(order)
        if order is Order.SERVO_END:
            print("Task successful")





