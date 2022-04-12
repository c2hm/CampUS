#if defined(ARDUINO_OpenCR) // When using official ROBOTIS board with DXL circuit.
  // For OpenCR, there is a DXL Power Enable pin, so you must initialize and control it.
  #define DXL_SERIAL   Serial3
  #define DEBUG_SERIAL Serial
  const uint8_t DXL_DIR_PIN = 84; // OpenCR Board's DIR PIN.
#endif

#define FRONT_LEFT_SERVO 0
#define FRONT_RIGHT_SERVO 1
#define REAR_LEFT_SERVO 2
#define REAR_RIGHT_SERVO 3

#define FRONT_LEFT_SERVO_HOME 71
#define FRONT_RIGHT_SERVO_HOME 117
#define REAR_LEFT_SERVO_HOME 126
#define REAR_RIGHT_SERVO_HOME 74

#define PIN_FRONT_LEFT_SERVO_PWM 6
#define PIN_FRONT_RIGHT_SERVO_PWM 3
#define PIN_REAR_LEFT_SERVO_PWM 9
#define PIN_REAR_RIGHT_SERVO_PWM 5

//Movement modes
#define WAIT_MODE 0
#define EXTENSION_MODE 1
#define RETRACTION_MODE 2
uint8_t mode = WAIT_MODE;
using namespace ControlTableItem;

Servo servo_test = Servo();

#define DXL_ID_REAR_LEFT 3
#define DXL_ID_REAR_RIGHT 23
#define DXL_ID_FRONT_LEFT 9
#define DXL_ID_FRONT_RIGHT 22

#define FRONT_LEFT_RETRACTED 2416
#define FRONT_RIGHT_RETRACTED 2802
#define REAR_LEFT_RETRACTED 3140
#define REAR_RIGHT_RETRACTED 1064

#define FRONT_LEFT_EXTENDED 288
#define FRONT_RIGHT_EXTENDED 620
#define REAR_LEFT_EXTENDED 827
#define REAR_RIGHT_EXTENDED 3574

#define FRONT_LEFT_RAISED 3209
#define FRONT_RIGHT_RAISED 1661
#define REAR_LEFT_RAISED 1807
#define REAR_RIGHT_RAISED 2363

#define PIN_FL_ELECTRO 12
#define PIN_FR_ELECTRO 13
#define PIN_RL_ELECTRO 10
#define PIN_RR_ELECTRO 11

#define RETRACTED 0
#define EXTENDED 1
#define RAISED 2

int angle = 0;
int angleToAdd = 10;

int nbTurnsFrontLeft;
int nbTurnsFrontRight;
int nbTurnsRearLeft;
int nbTurnsRearRight;
int frontLeftMode;
int frontRightMode;
int rearLeftMode;
int rearRightMode;
int objectif;
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Servo servomotors[4] = {};
