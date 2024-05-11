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


int state = ANTMAN_STATE_LOST;

void antman_init(){
    state = ANTMAN_STATE_LOST;
}

void antman(int d1, int d2, int velocity){

    if(state == ANTMAN_STATE_LOST){
        go_forward(velocity);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATE_ESCAPE;
        }
        else if (d2 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATE_DISTANCE;
        }
    }
    else if (state == ANTMAN_STATE_APPROACH){
        turn_right_precise(velocity, ANTMAN_ALPHA);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATE_ESCAPE;
        }
        else if (d2 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATE_DISTANCE;
        }
    }
    else if (state == ANTMAN_STATE_DISTANCE){
        turn_left_precise(velocity, ANTMAN_BETA);
        if(d1 < ANTMAN_THRESHOLD){
            state = ANTMAN_STATE_ESCAPE;
        }
        else if (d2 > ANTMAN_THRESHOLD + ANTMAN_HYSTERESIS){
            state = ANTMAN_STATE_APPROACH;
        }
    }
    else if (state == ANTMAN_STATE_ESCAPE){
        turn_left(velocity);
        if(d1 > ANTMAN_THRESHOLD + ANTMAN_HYSTERESIS){
            if (d2 > ANTMAN_THRESHOLD){
                state = ANTMAN_STATE_APPROACH;
            }
            else{
                state = ANTMAN_STATE_DISTANCE;
            }
        }
    }
    else{
        state = ANTMAN_STATE_LOST;
    }

}

/* [] END OF FILE */
