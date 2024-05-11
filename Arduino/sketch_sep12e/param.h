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
#define ID_MOTOR_LF 8
#define ID_MOTOR_LB 6
#define ID_MOTOR_RF 9
#define ID_MOTOR_RB 7

// Motor Directions
#define DIR_LF 1
#define DIR_LB 1
#define DIR_RF -1
#define DIR_RB -1

// Calibration Factors
#define ERR_LB 1
#define ERR_LF 1
#define ERR_RF 1.09
#define ERR_RB 1.09

// Calculate Motor Speeds
#define V_LB(x) ((x) * DIR_LB * ERR_LB)
#define V_LF(x) ((x) * DIR_LF * ERR_LF)
#define V_RB(x) ((x) * DIR_RB * ERR_RB)
#define V_RF(x) ((x) * DIR_RF * ERR_RF)

// Ranging.c
#define SOUND_SPEED 343    // Speed of sound in m/s
#define RANGING_CLOCK_FREQ 1000000  // Ranging clock frequency in Hz
#define RANGING_TRIGGER 50 // Trigger duration in microseconds
#define RANGING_TIMEOUT 5000

// Define pin numbers for Arduino
#define RANGING_T1_PIN 6  // Trigger pin for probe 1
#define RANGING_R1_PIN 7  // Echo pin for probe 1
#define RANGING_T2_PIN 8  // Trigger pin for probe 2
#define RANGING_R2_PIN 9  // Echo pin for probe 2

// Antman.c
#define ANTMAN_ALPHA 0
#define ANTMAN_BETA 0
#define ANTMAN_THRESHOLD 0x60
#define ANTMAN_HYSTERESIS 0x10

#define ANTMAN_STATE_LOST 0
#define ANTMAN_STATE_APPROACH 1
#define ANTMAN_STATE_DISTANCE 2
#define ANTMAN_STATE_ESCAPE 3

// robot_arm.c

#define INIT_1 770
#define INIT_2 500
#define INIT_3 900
#define INIT_4 170
#define INIT_5 750
//#define INIT_6 565

#define MIN_1 0
#define MIN_2 150
#define MIN_3 900
#define MIN_4 80
#define MIN_5 550
//#define MIN_6 565

#define MAX_1 1023
#define MAX_2 500
#define MAX_3 1023
#define MAX_4 800
#define MAX_5 750
//#define MAX_6 620

#define MOVESTEP 20
#define ARM_SPEED 135
#define SET_LIMIT_DELAY 0

// led & buzzer

#define LED_RED 11
#define LED_YELLOW 12
#define LED_WHITE 13
#define BUZZER 10

#define LED_RED_MASK (1 << 0)
#define LED_YELLOW_MASK (1 << 1)
#define LED_WHITE_MASK (1 << 2)

#define BUZZER_FREQ 1000
#define LED_YELLOW_THRESHOLD 500

// main.c
#define ANG2MS(t) (((t) * 1000 / 45) * 1.2)     // Angle degrees to delay milliseconds
#define L_INT_MAX 0x7FFFFFFF                    // Maximum integer value
#define LCD_CLEAR "                "            // To clear one line of the LCD screen
#define INTERVAL 100
#define SPEED 1000
#define DIST_THRESHOLD 0x50


/* [] END OF FILE */
