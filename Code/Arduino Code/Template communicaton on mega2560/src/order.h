#ifndef ORDER_H
#define ORDER_H

// Define the orders that can be sent and received
enum Order {

  // DOIT ÊTRE EXACTEMENT LA MÊME LIST/ORDRE QUE DANS LE PROG PYTHON

  //ORDRE GÉNÉRAL
    HELLO = 0,
    ALREADY_CONNECTED = 1,
    ERROR = 2,
    RECEIVED = 3,
    FINISHED = 4,

    HOME = 5,
    START = 6,
    STOP = 7,
    SEMI_AUTO = 8,
    SERVO = 9
  
  
};

typedef enum Order Order;

#endif
