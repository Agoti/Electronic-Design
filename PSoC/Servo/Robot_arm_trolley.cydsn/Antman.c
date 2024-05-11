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


int state = ANTMAN_STATUS_LOST;

void antman_init(){
    state = ANTMAN_STATUS_LOST;
}

void antman(int d1, int d2, int velocity){

    LCD_Position(1, 8);
    LCD_PrintInt32(state);

    if(state == ANTMAN_STATUS_LOST){
        go_forward(velocity);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATUS_ESCAPE;
        }
        else if (d2 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATUS_DISTANCE;
        }
    }
    else if (state == ANTMAN_STATUS_APPROACH){
        turn_right_precise(velocity, ANTMAN_ALPHA);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATUS_ESCAPE;
        }
        else if (d2 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATUS_DISTANCE;
        }
    }
    else if (state == ANTMAN_STATUS_DISTANCE){
        turn_left_precise(velocity, ANTMAN_BETA);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATUS_ESCAPE;
        }
        else if (d2 > ANTMAN_THRESHOLD + ANTMAN_HYSTERESIS){
            state = ANTMAN_STATUS_APPROACH;
        }
    }
    else if (state == ANTMAN_STATUS_ESCAPE){
        turn_left(velocity);
        if(d1 > ANTMAN_THRESHOLD + ANTMAN_HYSTERESIS){
            if (d2 > ANTMAN_THRESHOLD){
                state = ANTMAN_STATUS_APPROACH;
            }
            else{
                state = ANTMAN_STATUS_DISTANCE;
            }
        }
    }
    else{
        state = ANTMAN_STATUS_LOST;
    }

}

/* [] END OF FILE */
