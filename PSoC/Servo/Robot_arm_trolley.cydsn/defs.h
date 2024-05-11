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
void SetServoLimit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit);
void SetServoPosition(unsigned char id, unsigned short int position, unsigned short int velocity);
void SetServoVelocity(unsigned char id, signed short int velocity);

void set_servo_limit(unsigned char id, unsigned short int cw_limit, unsigned short int ccw_limit);
void set_servo_pos(unsigned char id, unsigned short int position, unsigned short int velocity);
void set_servo_velocity(unsigned char id, signed short int velocity);

// Driving.c
void servos_motormode();
void go_forward(signed short int velocity);
void stop();
void turn_left(signed short int velocity);
void turn_right(signed short int velocity);
void turn_left_precise(signed short int velocity, float alpha);
void turn_right_precise(signed short int velocity, float alpha);
void reverse_turn_left(signed short int velocity);
void reverse_turn_right(signed short int velocity);

// Ranging.c
long long calculate_millimeter(uint32 cnt);
void ranging_init();

void RangingTimeoutInt1();
void ranging_init1();
void trigger1();
void startcount1();
uint32 endcount1();
int get_millimeter1();

void RangingTimeoutInt2();
void ranging_init2();
void trigger2();
void startcount2();
uint32 endcount2();
int get_millimeter2();

// Antman.c
void antman_init();
void antman(int d1, int d2, int velocity);

// Robot_arm.c
//单舵机运动单元
void m1_left_unit();
void m1_right_unit();
void m2_forward_unit();
void m2_backward_unit();
void m3_up_unit();
void m3_down_unit();
void m4_up_unit();
void m4_down_unit();

//optional 组合运动单元
void forward_move_unit();
void backward_move_unit();
void upward_move_unit();
void downward_move_unit();
void left_move_unit();
void right_move_unit();
void drop();
void grab();
void reset_init_pos();
void simu_fetch();
void pause();
void steering_engine_controller();


/* [] END OF FILE */
