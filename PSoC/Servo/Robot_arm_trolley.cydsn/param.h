/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// Servo.c
#define WAITING_TIME 2

// Driving.c

// Servo IDs
#define ID_MOTOR_LF 1
#define ID_MOTOR_LB 6
#define ID_MOTOR_RF 3
#define ID_MOTOR_RB 7

// Motor Directions
#define DIR_LF 1
#define DIR_LB 1
#define DIR_RF -1
#define DIR_RB -1

// Calibration Factors
#define ERR_LB 1
#define ERR_LF 1
#define ERR_RF 1.08
#define ERR_RB 1.08

// Calculate Motor Speeds
#define V_LB(x) ((x) * DIR_LB * ERR_LB)
#define V_LF(x) ((x) * DIR_LF * ERR_LF)
#define V_RB(x) ((x) * DIR_RB * ERR_RB)
#define V_RF(x) ((x) * DIR_RF * ERR_RF)

// Ranging.c
#define RANGING_TRIGGER 50              // Trigger pulse width
#define SOUND_SPEED 340                 // Sound speed in m/s
#define RANGING_CLOCK_FREQ 12000000     // Timer clock frequency in Hz

// Antman.c
#define ANTMAN_ALPHA 0.7
#define ANTMAN_BETA -1
#define ANTMAN_THRESHOLD 0x500
#define ANTMAN_HYSTERESIS 0x50

#define ANTMAN_STATUS_LOST 0
#define ANTMAN_STATUS_APPROACH 1
#define ANTMAN_STATUS_DISTANCE 2
#define ANTMAN_STATUS_ESCAPE 3

// robot_arm.c

#define INIT_1 570
#define INIT_2 300
#define INIT_3 900
#define INIT_4 170
#define INIT_5 600
//#define INIT_6 565

#define MIN_1 0
#define MIN_2 0
#define MIN_3 900
#define MIN_4 80
#define MIN_5 600
//#define MIN_6 565

#define MAX_1 1023
#define MAX_2 400
#define MAX_3 1023
#define MAX_4 800
#define MAX_5 800
//#define MAX_6 620

// main.c
#define ANG2MS(t) (((t) * 1000 / 45) * 1.2)     // Angle degrees to delay milliseconds
#define L_INT_MAX 0x7FFFFFFF                    // Maximum integer value
#define LCD_CLEAR "                "            // To clear one line of the LCD screen
#define INTERVAL 100
#define SPEED 1000


/* [] END OF FILE */
