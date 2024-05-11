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

#include <project.h>
#include "defs.h"
#include "param.h"

// Function to set all servos to motor mode
void servos_motormode(){
    SetServoLimit(ID_MOTOR_LB, 0, 0);
    SetServoLimit(ID_MOTOR_LF, 0, 0);
    SetServoLimit(ID_MOTOR_RB, 0, 0);
    SetServoLimit(ID_MOTOR_RF, 0, 0);
}

// Function to make the robot go forward with a given velocity
void go_forward(signed short int velocity){
    SetServoVelocity(ID_MOTOR_LB, V_LB(velocity));
    SetServoVelocity(ID_MOTOR_LF, V_LF(velocity));
    SetServoVelocity(ID_MOTOR_RB, V_RB(velocity));
    SetServoVelocity(ID_MOTOR_RF, V_RF(velocity));
}

// Function to stop the robot
void stop(){
    go_forward(0);
}

// Function to make the robot turn left with a given velocity
void turn_left(signed short int velocity){
    turn_left_precise(velocity, -1);
}

// Function to make the robot turn right with a given velocity
void turn_right(signed short int velocity){
    turn_right_precise(velocity, -1);
}

// Function to make the robot turn left with a given velocity and precision
void turn_left_precise(signed short int velocity, float alpha){
    SetServoVelocity(ID_MOTOR_LB, alpha * V_LB(velocity));
    SetServoVelocity(ID_MOTOR_LF, alpha * V_LF(velocity));
    SetServoVelocity(ID_MOTOR_RB, V_RB(velocity));
    SetServoVelocity(ID_MOTOR_RF, V_RF(velocity));
}

// Function to make the robot turn right with a given velocity and precision
void turn_right_precise(signed short int velocity, float alpha){
    SetServoVelocity(ID_MOTOR_LB, V_LB(velocity));
    SetServoVelocity(ID_MOTOR_LF, V_LF(velocity));
    SetServoVelocity(ID_MOTOR_RB, alpha * V_RB(velocity));
    SetServoVelocity(ID_MOTOR_RF, alpha * V_RF(velocity));
}

void reverse_turn_left(signed short int velocity){
    turn_left_precise(-velocity, 0);
}

// Function to make the robot turn right with a given velocity
void reverse_turn_right(signed short int velocity){
    turn_right_precise(-velocity, 0);
}


/* [] END OF FILE */
