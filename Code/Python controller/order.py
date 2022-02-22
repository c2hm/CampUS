
from enum import Enum
class Order(Enum):
    #NEEDS TO BE EXACT SAME LIST AS ARDUINO

    #ORDRE GÉNÉRAL
    HELLO = 0
    ALREADY_CONNECTED = 1
    ERROR = 2
    RECEIVED = 3
    FINISHED = 4

    HOME = 5
    START = 6
    STOP = 7
    SEMI_AUTO = 8
    SERVO = 9