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

#include "defs.h"
#include "param.h"

//全局舵机位置，记录舵机位置
int cur_pos_1 = INIT_1;
int cur_pos_2 = INIT_2;
int cur_pos_3 = INIT_3;
int cur_pos_4 = INIT_4;
int cur_pos_5 = INIT_5;

enum SINGLE_MOTOR_MOTION_CMD{
	M1_L, M1_R,
	M2_F, M2_B,
	M3_U, M3_D,
	M4_U, M4_D,
	DROP, GRAB,
	RESET_INIT,
	PAUSE
}Command;

#define MOVESTEP 15
#define ARM_SPEED 120

//单舵机运动单元
void m1_left_unit(){

	set_servo_limit(1, MIN_1, MAX_1);
    // set_servo_pos(1, MAX_1, ARM_SPEED);

	if(cur_pos_1 >= MIN_1 && cur_pos_1 <= MAX_1){
		int movestep = MOVESTEP;
		if(cur_pos_1 + movestep <= MAX_1){
			cur_pos_1 += movestep;
		}
		else{
			cur_pos_1 = MAX_1;
		}
		set_servo_pos(1, cur_pos_1, ARM_SPEED);
	}

	// CyDelay(100);
}

void m1_right_unit(){

	set_servo_limit(1, MIN_1, MAX_1);
    // set_servo_pos(1, MIN_1, ARM_SPEED);

	if(cur_pos_1 >= MIN_1 && cur_pos_1 <= MAX_1){
		int movestep = MOVESTEP;
		if(cur_pos_1 - movestep >= MIN_1){
			cur_pos_1 -= movestep;
		}
		else{
			cur_pos_1 = MIN_1;
		}
		set_servo_pos(1, cur_pos_1, ARM_SPEED);
	}

	// CyDelay(100);
}

void m2_forward_unit(){

	set_servo_limit(2, MIN_2, MAX_2);
    // set_servo_pos(2, MIN_2, ARM_SPEED);

	if(cur_pos_2 >= MIN_2 && cur_pos_2 <= MAX_2){
		int movestep = MOVESTEP;
		if(cur_pos_2 - movestep >= MIN_2){
			cur_pos_2 -= movestep;
		}
		else{
			cur_pos_2 = MIN_2;
		}
		set_servo_pos(2, cur_pos_2, ARM_SPEED);
	}

	// CyDelay(100);
}

void m2_backward_unit(){

	set_servo_limit(2, MIN_2, MAX_2);
    // set_servo_pos(2, MAX_2, ARM_SPEED);

	if(cur_pos_2 >= MIN_2 && cur_pos_2 <= MAX_2){
		int movestep = MOVESTEP;
		if(cur_pos_2 + movestep <= MAX_2){
			cur_pos_2 += movestep;
		}
		else{
			cur_pos_2 = MAX_2;
		}
		set_servo_pos(2, cur_pos_2, ARM_SPEED);
	}

	// CyDelay(100);
}

void m3_up_unit(){

    set_servo_limit(3, MIN_3, MAX_3);
	// set_servo_pos(1, MAX_3, ARM_SPEED);

	if(cur_pos_3 >= MIN_3 && cur_pos_3 <= MAX_3){
		int movestep = MOVESTEP;
		if(cur_pos_3 + movestep <= MAX_3){
			cur_pos_3 += movestep;
		}
		else{
			cur_pos_3 = MAX_3;
		}
		set_servo_pos(3, cur_pos_3, ARM_SPEED);
	}

	// CyDelay(100);
}

void m3_down_unit(){

    set_servo_limit(3, MIN_3, MAX_3);
	// set_servo_pos(3, MIN_3, ARM_SPEED);

	if(cur_pos_3 >= MIN_3 && cur_pos_3 <= MAX_3){
		int movestep = MOVESTEP;
		if(cur_pos_3 - movestep >= MIN_3){
			cur_pos_3 -= movestep;
		}
		else{
			cur_pos_3 = MIN_3;
		}
		set_servo_pos(3, cur_pos_3, ARM_SPEED);
	}

	// CyDelay(100);
}

void m4_up_unit(){

    set_servo_limit(4, MIN_4, MAX_4);
	// set_servo_pos(4, MAX_4, ARM_SPEED);

	if(cur_pos_4 >= MIN_4 && cur_pos_4 <= MAX_4){
		int movestep = MOVESTEP;
		if(cur_pos_4 + movestep <= MAX_4){
			cur_pos_4 += movestep;
		}
		else{
			cur_pos_4 = MAX_4;
		}
		set_servo_pos(4, cur_pos_4, ARM_SPEED);
	}

	// CyDelay(100);
}

void m4_down_unit(){

    set_servo_limit(4, MIN_4, MAX_4);
	// set_servo_pos(4, MIN_4, ARM_SPEED);

	if(cur_pos_4 >= MIN_4 && cur_pos_4 <= MAX_4){
		int movestep = MOVESTEP;
		if(cur_pos_4 - movestep >= MIN_4){
			cur_pos_4 -= movestep;
		}
		else{
			cur_pos_4 = MIN_4;
		}
		set_servo_pos(4, cur_pos_4, ARM_SPEED);
	}

	// CyDelay(100);
}

//optional 组合运动单元
void forward_move_unit(){

}

void backward_move_unit(){

}

void upward_move_unit(){

}

void downward_move_unit(){

}

void left_move_unit(){

}

void right_move_unit(){

}

void drop(){
	set_servo_limit(5, MIN_5, MAX_5);
	cur_pos_5 = MAX_5;
	set_servo_pos(5, cur_pos_5, 150);
	CyDelay(1000);
}

void grab(){
	set_servo_limit(5, MIN_5, MAX_5);
	cur_pos_5 = MIN_5;
	set_servo_pos(5, cur_pos_5, 150);
	CyDelay(1000);
}

void reset_init_pos(){
	//位置初始化 or 复位操作
	//首先移动到安全位置
	set_servo_limit(1, MIN_1, MAX_1);
	set_servo_limit(2, MIN_2, MAX_2);
	set_servo_limit(3, MIN_3, MAX_3);
	set_servo_limit(4, MIN_4, MAX_4);
	set_servo_limit(5, MIN_5, MAX_5);

	set_servo_pos(4,440,100);
	CyDelay(500);
	set_servo_pos(3,1022,150);
	CyDelay(500);
	set_servo_pos(2,250,150);
	CyDelay(500);

	//然后进行缓慢复位操作
	set_servo_pos(1,INIT_1,150);
	CyDelay(200);
	set_servo_pos(2,INIT_2,150);
	CyDelay(200);
	set_servo_pos(3,INIT_3,150);
	CyDelay(200);
	set_servo_pos(4,INIT_4,150);
	CyDelay(200);
	set_servo_pos(5,INIT_5,150);
	//set_servo_pos(6,INIT_6,100);
	CyDelay(2000);

	cur_pos_1 = INIT_1;
	cur_pos_2 = INIT_2;
	cur_pos_3 = INIT_3;
	cur_pos_4 = INIT_4;
	cur_pos_5 = INIT_5;
}

void simu_fetch(){
	for(int i = 0;i < 20;i++){
		m4_up_unit();
		m1_left_unit();
	}

	for(int i = 0;i < 20;i++){
		m4_up_unit();
		m2_forward_unit();
	}
	for(int i = 0;i < 40;i++){
		m4_up_unit();
	}
	for(int i = 0;i < 20;i++){
		m3_down_unit();
		m4_up_unit();
		m2_forward_unit();
	}

	drop();
	CyDelay(5000);
	grab();

	CyDelay(5000);

	reset_init_pos();
}

void pause(){
	set_servo_limit(1, 0, 0);
	set_servo_limit(2, 0, 0);
	set_servo_limit(3, 0, 0);
	set_servo_limit(4, 0, 0);
	set_servo_limit(5, 0, 0);
    set_servo_velocity(1, 0);
	set_servo_velocity(2, 0);
	set_servo_velocity(3, 0);
	set_servo_velocity(4, 0);
	set_servo_velocity(5, 0);
}

//基于单舵机运动单元的控制器
void steering_engine_controller(){
	//reset, initialize first
	reset_init_pos();

	//控制器主循环，死循环
	while(1){

		if(Command == M1_L){
			while(Command == M1_L){
				m1_left_unit();
			}
			continue;
		}

		if(Command == M1_R){
			while(Command == M1_R){
				m1_right_unit();
			}
			continue;
		}

		if(Command == M2_F){
			while(Command == M2_F){
				m2_forward_unit();
			}
			continue;
		}

		if(Command == M2_B){
			while(Command == M2_B){
				m2_backward_unit();
			}
			continue;
		}

		if(Command == M3_U){
			while(Command == M3_U){
				// m3_upward_unit();
			}
			continue;
		}

		if(Command == M3_D){
			while(Command == M3_D){
				// m3_downward_unit();
			}
			continue;
		}

		if(Command == M4_U){
			while(Command == M4_U){
				// m4_upward_unit();
			}
			continue;
		}

		if(Command == M4_D){
			while(Command == M4_D){
				// m4_downward_unit();
			}
			continue;
		}

		if(Command == DROP){
			drop();
			continue;
		}

		if(Command == GRAB){
			grab();
			continue;
		}

		if(Command == RESET_INIT){
			// reset();
			continue;
		}
		if(Command == PAUSE){
			pause();
			continue;
		}
	}
}



/* [] END OF FILE */
