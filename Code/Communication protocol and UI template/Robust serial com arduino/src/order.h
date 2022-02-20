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

  //ORDRE D'ACTIONS
  HOME = 4,
  SERVO = 5,
  STOP = 6,

  //ORDRE COMPLÉTÉ
  HOME_END = 7,
  SERVO_END = 8,
  STOP_END = 9,
  
};

typedef enum Order Order;

#endif
