#include "defs.h"
#include "param.h"
#include <SoftwareSerial.h>

// Define DEBUG if you want to enable debug code
// #define DEBUG

SoftwareSerial mySerial1(2, 3);
SoftwareSerial mySerial2(4, 5);

char operation_char;
int d1, d2;

void setup()
{

  // Initialize communication
  mySerial1.begin(115200);
  mySerial2.begin(115200);
  Serial.begin(115200);

  // Initialize hardware components
  ranging_init();
  led_buzzer_init();
  servos_motormode();
  stop();
  reset_init_pos();
  antman_init();
  motor_init();
}

void loop()
{

#ifdef DEBUG

  // Debug code goes here

#endif

#ifndef DEBUG

  // Get distance readings from sensors
  d1 = get_millimeter1();
  d2 = get_millimeter2();

  // Send distance readings over Serial1
  mySerial1.print(d1);
  mySerial1.print("mm ");
  mySerial1.print(d2);
  mySerial1.println("mm ");

  // Listen for commands from Serial1
  mySerial1.listen();
  if (mySerial1.available())
  {
    operation_char = mySerial1.read();
    switch (operation_char)
    {
    case 'w':
      if (!(d1 < DIST_THRESHOLD || d2 < DIST_THRESHOLD))
        go_forward(SPEED);
      break;
    case 'a':
      if (!(d2 < DIST_THRESHOLD))
        turn_left(SPEED);
      break;
    case 's':
      go_forward(-SPEED);
      break;
    case 'd':
      if (!(d1 < DIST_THRESHOLD))
        turn_right(SPEED);
      break;
    case 'q':
      if (!(d2 < DIST_THRESHOLD))
        turn_left_precise(SPEED, 0);
      break;
    case 'e':
      if (!(d1 < DIST_THRESHOLD))
        turn_right_precise(SPEED, 0);
      break;
    case 'z':
      reverse_turn_left(SPEED);
      break;
    case 'c':
      reverse_turn_right(SPEED);
      break;
    case '1':
      m1_left_unit();
      break;
    case '2':
      m1_right_unit();
      break;
    case '3':
      m2_forward_unit();
      break;
    case '4':
      m2_backward_unit();
      break;
    case '5':
      m3_up_unit();
      break;
    case '6':
      m3_down_unit();
      break;
    case '7':
      m4_up_unit();
      break;
    case '8':
      m4_down_unit();
      break;
    case '9':
      grab();
      break;
    case '0':
      drop();
      break;
    case '-':
      reset_init_pos();
      break;
    case '+':
      pause();
      break;
    case ' ':
      stop();
      break;
    case 'f':
      buzzer_buzz(BUZZER_FREQ);
      break;
    case 'g':
      buzzer_mute();
      break;

    default:
      stop();
      // pause();
    }
  }
  else
  {
    stop();
    // pause();
  }

  delay(INTERVAL);
#endif
}
